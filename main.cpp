#include <iostream>
#include <valarray>
#include "rnnoise/include/rnnoise-nu.h"
#include "resampling/resampling.h"

#define FRAME_SIZE 480

int main() {
    int i, ci;
    int first = 1;
    int channels;
    float x[FRAME_SIZE];
    short *tmp;
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
//    sts = malloc(channels * sizeof(DenoiseState *));

    sts = new DenoiseState*[channels];
    if (!sts) {
        perror("malloc");
        return 1;
    }
//    tmp = malloc(channels * FRAME_SIZE * sizeof(short));
    tmp = new short[channels * FRAME_SIZE];

    if (!tmp) {
        perror("malloc");
        return 1;
    }
    for (i = 0; i < channels; i++) {
        sts[i] = rnnoise_create(model);
        rnnoise_set_param(sts[i], RNNOISE_PARAM_MAX_ATTENUATION, max_attenuation);
        rnnoise_set_param(sts[i], RNNOISE_PARAM_SAMPLE_RATE, sample_rate);
    }


    f1 = fopen("ambientNoiseMixed.raw", "rb");
    fout = fopen("out.raw", "wb");

    while (1) {
        fread(tmp, sizeof(short), channels * FRAME_SIZE, f1);
        if (feof(f1)) break;
        // set up input and output pointers


        for (ci = 0; ci < channels; ci++) {

            for (i = 0; i < FRAME_SIZE; i++) x[i] = tmp[i * channels + ci];
            rnnoise_process_frame(sts[ci], x, x);
            for (i = 0; i < FRAME_SIZE; i++) tmp[i * channels + ci] = x[i];
        }

        if (!first) fwrite(tmp, sizeof(short), channels * FRAME_SIZE, fout);
        first = 0;
    }
    for (i = 0; i < channels; i++)
        rnnoise_destroy(sts[i]);


    free(tmp);
    free(sts);
    fclose(f1);
    fclose(fout);
}
