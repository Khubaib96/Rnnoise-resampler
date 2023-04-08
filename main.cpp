#include <iostream>
#include "AudioProcessor.h"

#define FRAME_SIZE 480

// Main function for the audio processing application
int main() {
    // Create an instance of the AudioProcessor class with desired parameters
    AudioProcessor *audioProcessor = new AudioProcessor(48000, 1, 16000, 48000);
    int first = 1;
    FILE *f1, *fout;
    // Open input and output files for reading and writing, respectively
    f1 = fopen("ambientNoiseMixed.raw", "rb");
    if (f1 == NULL) {
        printf("Error: File ../ambientNoiseMixed.raw could not be opened\n");
        return 1;
    }

    fout = fopen("out.raw", "wb");
    if (fout == NULL) {
        printf("Error: File ../out.raw could not be opened\n");
        return 1;
    }
    // Allocate memory for temporary input buffer
    short *tmp = new short[FRAME_SIZE];
    short *out;
    // Read input audio in chunks and process it using the AudioProcessor
    while (true) {
        fread(tmp, sizeof(short), 1 * FRAME_SIZE, f1);
        if (feof(f1)) break;
        out = audioProcessor->process(tmp);
        // Write output audio to output file
        if (!first) fwrite(out, sizeof(short), 1 * audioProcessor->getOutputBufferSize(), fout);
        first = 0;
    }

    // Free memory and close files
    audioProcessor->~AudioProcessor();
    free(tmp);
    fclose(f1);
    fclose(fout);
}
