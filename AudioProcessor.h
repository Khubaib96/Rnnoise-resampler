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
    AudioProcessor(int samplerate, int channels, int outputFrequency);

    virtual ~AudioProcessor();

    short *process(const short *input);

    int getOutputBufferSize();

    int getChannels() const
    {
        return this->channels;
    }

    int getFrameSize() const
    {
        return static_cast<int>((10.0 / 1000.0) * sample_rate);;
    }

private:
    // Private member variables and helper functions
    int channels;
    float x[FRAME_SIZE];
    short *outtmp;
    int sample_rate;
    RNNModel *model = NULL;
    DenoiseState **sts;
    float max_attenuation;
    int outputBufferSize = -1;

    // for resampler
    coder::array<double, 1U> in;
    coder::array<double, 1U> out;

    //for input resampler
    coder::array<double, 1U> originalIn;
    coder::array<double, 1U> originalOut;

    int outputFreq;
    int inputFreq;
};

#endif //FINALCODE_AUDIOPROCESSOR_H
