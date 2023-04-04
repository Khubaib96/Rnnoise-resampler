#include <iostream>
#include <valarray>
#include "rnnoise/include/rnnoise.h"
#include "resampling/resampling.h"

#define FRAME_SIZE 480

int main() {
    int i, ci;
    int first = 1;
    int channels;
    float x[FRAME_SIZE];
    short *tmp;
    short *outtmp;
    int sample_rate;
    RNNModel *model = NULL;
    DenoiseState **sts;
    FILE *f1, *fout;
    float max_attenuation;

//    if (argc < 4) {
//        fprintf(stderr, "usage: %s <sample rate> <chann els> <max attenuation dB> [model]\n", argv[0]);
//        return 1;
//    }

    sample_rate = atoi("48000");
    if (sample_rate <= 0) sample_rate = 48000;
    channels = atoi("1");
    if (channels < 1) channels = 1;
    max_attenuation = pow(10, -atof("20") / 10);
    model = rnnoise_get_model("sh");
    if (!model) {
        fprintf(stderr, "Model not found!\n");
        return 1;
    }

    sts = new DenoiseState *[channels];
    if (!sts) {
        perror("malloc");
        return 1;
    }
    tmp = new short[channels * FRAME_SIZE];
    outtmp = new short[channels * 160];

    if (!tmp) {
        perror("malloc");
        return 1;
    }
    for (i = 0; i < channels; i++) {
        sts[i] = rnnoise_create(model);
        rnnoise_set_param(sts[i], RNNOISE_PARAM_MAX_ATTENUATION, max_attenuation);
        rnnoise_set_param(sts[i], RNNOISE_PARAM_SAMPLE_RATE, sample_rate);
    }


    f1 = fopen("../ambientNoiseMixed.raw", "rb");
    fout = fopen("../out.raw", "wb");

    while (true) {
        fread(tmp, sizeof(short), channels * FRAME_SIZE, f1);
        if (feof(f1)) break;
        // set up input and output pointers

        //setting up arrays for resampling
        coder::array<double, 1U> in;// dimension 1`d array or 2-d array
        coder::array<double, 1U> out;

        in.set_size(480);
        out.set_size(160);

        for (ci = 0; ci < channels; ci++) {

            for (i = 0; i < FRAME_SIZE; i++) x[i] = tmp[i * channels + ci];
            rnnoise_process_frame(sts[ci], x, x);
            for (int idx0 = 0; idx0 < in.size(0); idx0++) {
                in[idx0] = x[idx0];
            }
            resampling(in, 16000.0, 48000.0, out);
            for (i = 0; i < 160; i++) outtmp[i * channels + ci] = out[i];
        }

        if (!first) fwrite(outtmp, sizeof(short), channels * 160, fout);
        first = 0;
    }
    for (i = 0; i < channels; i++)
        rnnoise_destroy(sts[i]);


    free(tmp);
    free(sts);
    fclose(f1);
    fclose(fout);
}
