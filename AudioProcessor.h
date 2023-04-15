//
// Created by Khubaib on 4/5/2023.
//

#ifndef FINALCODE_AUDIOPROCESSOR_H
#define FINALCODE_AUDIOPROCESSOR_H

#include "rnnoise/include/rnnoise.h"
#include "resampling/resampling.h"

#define FRAME_SIZE 480

class AudioProcessor {
public:
    // Constructor that initializes member variables
    AudioProcessor(int samplerate, int channels, int outputFrequency);

    // Virtual destructor to ensure proper cleanup of resources
    virtual ~AudioProcessor();

    // Main processing function that takes an input buffer and returns an output buffer
    short *process(short *input);

    // Function that returns the size of the output buffer
    int getOutputBufferSize();

    // Function that returns the number of channels
    int getChannels() const {
        return this->channels_for_resampler;
    }

    // Function that returns the frame size
    int getFrameSize() const {
        return static_cast<int>((10.0 / 1000.0) * sample_rate);;
    }

private:
    // Private member variables and helper functions
    int channels;
    float x[FRAME_SIZE];
    short *outtmp;
    int sample_rate;
    RNNModel *model = nullptr;
    DenoiseState **sts;
    float max_attenuation;
    int outputBufferSize = -1;
    int outputFreq;

    // for resampler
    coder::array<double, 1U> in;
    coder::array<double, 1U> out;

    //for input resampler
    coder::array<double, 1U> originalIn;
    coder::array<double, 1U> originalOut;


    // Function that converts stereo audio to mono
    short *convertStereoToMono(const short *input);

    // Function that converts mono audio to stereo
    short *convertMonoToStereo(const short *input);

    // Number of channels for resampling
    int channels_for_resampler;

    // Temporary buffer for stereo output
    short *outtmpStereo;
};

#endif //FINALCODE_AUDIOPROCESSOR_H
