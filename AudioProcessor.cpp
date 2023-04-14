#include <valarray>
#include <memory>
#include "AudioProcessor.h"

// Constructor for the AudioProcessor class
AudioProcessor::AudioProcessor(int samplerate, int channels, int outputFrequency) {
    // Initialize member variables
    this->sample_rate = samplerate;
    this->channels = channels;
    this->max_attenuation = pow(10, 20 / 10);
    this->model = rnnoise_get_model("sh");
    this->sts = new DenoiseState *[channels];
    this->outputFreq = outputFrequency;
    // Calculate output buffer size based on input and output frequency
    double ratio = static_cast<double>(this->outputFreq) / static_cast<double>(48000);
    this->outputBufferSize = (int) (std::ceil(ratio * FRAME_SIZE));
    this->outtmp = new short[channels * this->outputBufferSize];
    // Initialize RNNoise states for each channel
    for (int i = 0; i < channels; i++) {
        this->sts[i] = rnnoise_create(this->model);
        rnnoise_set_param(this->sts[i], RNNOISE_PARAM_MAX_ATTENUATION, this->max_attenuation);
        rnnoise_set_param(this->sts[i], RNNOISE_PARAM_SAMPLE_RATE, this->sample_rate);
    }

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
    for (int i = 0; i < channels; i++) {
        rnnoise_destroy(sts[i]);
    }
    // Free memory allocated for RNNoise state array
    free(sts);
    // Free memory allocated for output buffer
    free(outtmp);
    // Destroy input and output buffers
    in.clear();
    out.clear();
    // Destroy input and output buffers for resampling
    originalIn.clear();
    originalOut.clear();
}

// Process audio using RNNoise and resampling
short *AudioProcessor::process(const short *input) {

    // Process each channel of the audio
    for (int ci = 0; ci < this->channels; ci++) {
        // Resample audio to 48000Hz
        for (int idx0 = 0; idx0 < this->originalIn.size(0); idx0++) {
            this->originalIn[idx0] = input[idx0 * this->channels + ci];
        }
        resampling(this->originalIn, 48000.0, static_cast<double>(this->sample_rate), this->originalOut);
        // Copy resampled audio to RNNoise input buffer
        for (int i = 0; i < FRAME_SIZE; i++) {
            this->x[i] = this->originalOut[i * this->channels + ci];
        }
        // Apply RNNoise denoising algorithm to input buffer
        rnnoise_process_frame(this->sts[ci], this->x, this->x);
        // Copy denoised audio to input buffer
        for (int idx0 = 0; idx0 < this->in.size(0); idx0++) {
            this->in[idx0] = this->x[idx0];
        }
        // Resample audio to desired output frequency
        resampling(this->in, static_cast<double>(this->outputFreq), 48000.0, this->out);
        // Copy resampled audio to temporary output buffer
        for (int i = 0; i < this->outputBufferSize; i++) {
            this->outtmp[i * this->channels + ci] = this->out[i];
        }
    }

    // Return pointer to temporary output buffer
    return this->outtmp;
}

int AudioProcessor::getOutputBufferSize() {
    if (this->outputBufferSize == -1) {
        return -1;
    }
    return this->outputBufferSize;
}
