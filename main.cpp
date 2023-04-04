#include <iostream>
#include "AudioProcessor.h"

#define FRAME_SIZE 480

int main() {
    AudioProcessor *audioProcessor = new AudioProcessor(48000, 1, 16000, 48000);
    int first = 1;
    FILE *f1, *fout;
    f1 = fopen("../ambientNoiseMixed.raw", "rb");
    fout = fopen("../out.raw", "wb");
    short *tmp = new short[FRAME_SIZE];
    short *out;
    while (true) {
        fread(tmp, sizeof(short), 1 * FRAME_SIZE, f1);
        if (feof(f1)) break;
        // set up input and output pointers

        out = audioProcessor->process(tmp);


        if (!first) fwrite(out, sizeof(short), 1 * audioProcessor->getOutputBufferSize(), fout);
        first = 0;
    }

    audioProcessor->~AudioProcessor();
    free(tmp);
    fclose(f1);
    fclose(fout);
}
