# Audio Processing Application
This is a C++ application for audio processing using the RNNoise denoising algorithm and resampling.


# Usage
To use the audio processing application, follow these steps:

Create an instance of the AudioProcessor class with the desired parameters.
Open the input audio file for reading and the output audio file for writing.
Read input audio in chunks and process it using the process method of the AudioProcessor class.
Write the output audio to the output file.
Here's an example usage of the audio processing application:

```cpp
int main() {
    // Create an instance of the AudioProcessor class with desired parameters
    AudioProcessor *audioProcessor = new AudioProcessor(48000, 1, 16000, 48000);
    int first = 1;
    FILE *f1, *fout;
    // Open input and output files for reading and writing, respectively
    f1 = fopen("../ambientNoiseMixed.raw", "rb");
    fout = fopen("../out.raw", "wb");
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
```
