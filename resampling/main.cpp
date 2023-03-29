//
// File: main.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 29-Mar-2023 00:01:09
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include <iostream>
#include <cmath>
#include "main.h"
#include "resampling.h"
#include "resampling_terminate.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "AudioFile.h"

using namespace std;

int main() {

    AudioFile<float> audioFile;


    audioFile.load("../test.wav");
    int sampleRate = audioFile.getSampleRate();
    int bitDepth = audioFile.getBitDepth();
    int numSamples = audioFile.getNumSamplesPerChannel();

    int samplesToAdd = numSamples - (round(numSamples / 441.0) * 441);

    int numSamplesAdded = numSamples + samplesToAdd;
    audioFile.printSummary();
    int channel = 0;
    float *wav_file_data = new float[numSamplesAdded];
    for (int i = 0; i < numSamplesAdded; i++) {
        float currentSample = audioFile.samples[channel][i]; //
        if (i < numSamples) {
            wav_file_data[i] = (float) currentSample;
        } else {
            wav_file_data[i] = 0.0f;
        }
    }

    coder::array<double, 1U> test;// dimension 1`d array or 2-d array
    coder::array<double, 1U> out;

    int chunks = numSamplesAdded / 441;

    test.set_size(numSamplesAdded);
    out.set_size(numSamplesAdded * (16000.0 / 44100.0));

    // Loop over the array to initialize each element.
    for (int idx0 = 0; idx0 < test.size(0); idx0++) {
        test[idx0] = wav_file_data[idx0];
    }

    std::cout << "Passing data to processing function. . . ." << std::endl;

    for (int chunk = 0; chunk < chunks; chunk++) {
        coder::array<double, 1U> input;
        coder::array<double, 1U> output;
        input.set_size(441);
        for (int idx0 = 0; idx0 < 441; idx0++) {
            input[idx0] = test[(chunk * 441) + idx0];

        }
        resampling(input, 16000.0, 44100.0, output);
        for (int idx0 = 0; idx0 < output.size(0); idx0++) {
//                cout << output.size(0) << endl;
            out[(chunk * output.size(0)) + idx0] = output[idx0];
        }
    }

    std::cout << "Data has been processed!!!" << std::endl;
    AudioFile<float>::AudioBuffer buffer;
    buffer.resize(1);
    buffer[0].resize(out.size(0));
    for (int idx0 = 0; idx0 < out.size(0); idx0++) {
        buffer[0][idx0] = out[idx0];
    }

    //print the details of out data
    audioFile.setSampleRate(16000);
    audioFile.setAudioBuffer(buffer);

    audioFile.save("../output.wav");
    std::cout << "Processed data has been saved to wav file!" << std::endl;


    return 0;
}

