#include <valarray>
#include <memory>
#include "AudioProcessor.h"

// Constructor for the AudioProcessor class
AudioProcessor::AudioProcessor(int samplerate, int channels, int outputFrequency) {
    // Initialize member variables
    this->sample_rate = samplerate;
    this->channels = (channels >= 2) ? channels - 1 : channels;
    this->channels_for_resampler = channels;
    this->max_attenuation = pow(10.0, -(8.0 / 10.0));
    this->model = rnnoise_get_model("sh");
    this->outputFreq = outputFrequency;

    // Allocate memory for RNNoise state array
    this->sts = new DenoiseState *[this->channels];

    // Initialize RNNoise states for each channel
    for (int i = 0; i < this->channels; i++) {
        this->sts[i] = rnnoise_create(this->model);
        rnnoise_set_param(this->sts[i], RNNOISE_PARAM_MAX_ATTENUATION, this->max_attenuation);
        rnnoise_set_param(this->sts[i], RNNOISE_PARAM_SAMPLE_RATE, this->sample_rate);
    }

    // Calculate output buffer size based on input and output frequency
    double ratio = static_cast<double>(outputFrequency) / static_cast<double>(48000);
    this->outputBufferSize = static_cast<int>(std::ceil(ratio * FRAME_SIZE));

    // Allocate memory for output buffers
    this->outtmp = new short[this->channels * this->outputBufferSize];
    this->outtmpStereo = new short[this->channels_for_resampler * this->outputBufferSize];

    // Initialize input and output buffers
    this->in.set_size(FRAME_SIZE);
    this->out.set_size(outputBufferSize);

    // Initialize input and output buffers for resampling
    this->originalIn.set_size(static_cast<int>(0.01 * samplerate));
    this->originalOut.set_size(480);
}

// Destructor for the AudioProcessor class
AudioProcessor::~AudioProcessor() {
    // Free memory allocated for RNNoise states
    for (int i = 0; i < this->channels; i++) {
        rnnoise_destroy(sts[i]);
    }

    // Free memory allocated for RNNoise state array and output buffers
    delete[] sts;
    delete[] outtmp;
    delete[] outtmpStereo;

    // Clear input and output buffers
    in.clear();
    out.clear();

    // Clear input and output buffers for resampling
    originalIn.clear();
    originalOut.clear();
}

// Process audio using RNNoise and resampling
short *AudioProcessor::process(short *input) {
    // Convert stereo audio to mono if necessary
    if (this->channels_for_resampler == 2) {
        input = convertStereoToMono((short *) input);
    }

    // Process each channel of the audio
    for (int channel_index = 0; channel_index < this->channels; channel_index++) {
        // Resample audio to 48000Hz
        for (int sample_index = 0; sample_index < this->originalIn.size(0); sample_index++) {
            // Get sample value for this channel from input buffer
            this->originalIn[sample_index] = input[sample_index * this->channels + channel_index];
        }
        // Resample the audio from its current sample rate to 48000Hz
        resampling(this->originalIn, 48000.0, static_cast<double>(this->sample_rate), this->originalOut);

        // Copy resampled audio to RNNoise input buffer
        for (int i = 0; i < FRAME_SIZE; i++) {
            this->x[i] = this->originalOut[i * this->channels + channel_index];
        }

        // Apply RNNoise denoising algorithm to input buffer
        rnnoise_process_frame(this->sts[channel_index], this->x, this->x);

        // Copy denoised audio to input buffer
        for (int sample_index = 0; sample_index < this->in.size(0); sample_index++) {
            this->in[sample_index] = this->x[sample_index];
        }

        // Resample audio to desired output frequency
        resampling(this->in, static_cast<double>(this->outputFreq), 48000.0, this->out);

        // Copy resampled audio to temporary output buffer
        for (int sample_index = 0; sample_index < this->outputBufferSize; sample_index++) {
            this->outtmp[sample_index * this->channels + channel_index] = this->out[sample_index];
        }
    }

    // Convert mono audio to stereo if necessary
    if (this->channels_for_resampler == 2) {
        this->outtmpStereo = convertMonoToStereo(this->outtmp);
        return this->outtmpStereo;
    }

    // Return pointer to temporary output buffer
    return this->outtmp;
}


// This function returns the size of the output buffer.
// If the output buffer size has not been set, the function returns -1.
int AudioProcessor::getOutputBufferSize() {
    if (this->outputBufferSize == -1) {
        return -1;
    }
    return this->outputBufferSize;
}

// This function converts stereo audio to mono.
// It takes an input buffer and returns an output buffer.
// It assumes that the output buffer size has already been set.
short *AudioProcessor::convertStereoToMono(const short *input) {
    // Allocate memory for the output buffer
    short *output = new short[outputBufferSize];

    // Process input samples in blocks of 8
    for (int i = 0; i < outputBufferSize; i += 8) {
        // Compute the average of the left and right channels
        for (int j = 0; j < 8; j++) {
            output[i + j] = (input[(i * 2) + (j * 2)] + input[(i * 2) + (j * 2) + 1]) / 2;
        }
    }

    return output;
}

// This function converts mono audio to stereo.
// It takes an input buffer and returns an output buffer.
// It assumes that the output buffer size has already been set.
short *AudioProcessor::convertMonoToStereo(const short *input) {
    // Allocate memory for the output buffer
    short *output = new short[outputBufferSize * 2];

    // Process input samples in blocks of 8
    for (int i = 0; i < outputBufferSize; i += 8) {
        // Duplicate each sample to obtain stereo audio
        for (int j = 0; j < 8; j++) {
            output[(i * 2) + (j * 2)] = input[i + j];
            output[(i * 2) + (j * 2) + 1] = input[i + j];
        }
    }

    return output;
}

