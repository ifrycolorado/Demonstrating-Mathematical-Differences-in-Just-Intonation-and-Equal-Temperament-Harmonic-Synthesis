/* CSCI 261: Final Project - 
            An implementation of harmonic synthesis to demonstrate the mathematical 
            and audial difference between just intonation and equal temperament

 *
 * Author: Isaac Fry
 * Resources used:
 *     Writing .wav files in C++: https://www.youtube.com/watch?v=qqjvB_VxMRM 
 *           [goes through process and formatting techniques for .wav files, which is highly specific]
 *     Demonstration of mathematical viability: https://www.electronics-tutorials.ws/accircuits/harmonics.html
 *           [relates harmonic synthesis to Electrical Engineering, which is math-heavy]
 *     Music Stack Exchange on Just Intonation and Equal Temperament: https://music.stackexchange.com/questions/31509/difference-between-equal-temperament-and-just-intonation
 *           [goes into extensive detail about Just Intonation and Equal Temperament]
 * 
 * Implements Wave class to allow multiple SineWaves to be conglomerated together
 */

#include <cmath>
#include "Array.hpp"
#include <fstream>
#include "io_functions.h"
#include "SynthWave.h"
#include "Wave.h"
#include <vector>

#include <iostream> 

using namespace std; 

SynthWave::SynthWave(
                    const int sample, const unsigned int duration,
                    const int bitDepth) {

    mSampleRate = sample; 
    mDuration = duration;
    mBitDepth = bitDepth;

    // array of ints to be used in bit depth writing
    mpValueArr = new Array<int>(mDuration*mSampleRate); 
}

SynthWave::~SynthWave() {
    delete mpValueArr;
}

/**
 * @brief adds all values of SineWave arrays into object's array
 * @param sineWavesVector vector containing all SineWaves to be combined
 */

bool SynthWave::generate(vector<SineWave*> sineWavesVector) {

    for(int i = 1; i < 2; i++) {
        // checks to make sure all Waves can be combined well
        if (!(*sineWavesVector.at(i) == *sineWavesVector.at(0)) ) { 
            return false;
        }
    }

    unsigned int swvSize = sineWavesVector.size(); // const size of vector
    float maxAmp = (pow(2, mBitDepth - 1) - 1); // max amplitude

    for (int i = 0; i < (mDuration * mSampleRate); i++) { // cycling through all samples
        float currSample = 0; // initialize sampple
        for (int j = 0; j < swvSize; j++) { // cycling through all waves at sample point
            currSample += (sineWavesVector.at(j)->mpValueArrAtPoint(i)); 
        }
        currSample = currSample / swvSize; // normalize amplitude
        int intSample = static_cast<int> (currSample * maxAmp); // cast as int
        mpValueArr->set(i, intSample);
    }

    return true; 
}

/**
 * @brief write wave to a file
 * @param outFile ofstream
 * @result formatted mpValueArr to .wav file 
*/ 
void SynthWave::write(std::ofstream& outFile) {

    // ----- HEADER CHUNK -----
    outFile << "RIFF"; // standard
    outFile << "----"; // size of file, 4 bytes
    outFile << "WAVE"; // standard

    // ----- FORMAT CHUNK ----- 
    outFile << "fmt "; // format, 4 bytes
    reinterpretWrite(outFile, 16, 4); // convert Size of Chunk 16 into 4 bytes
    reinterpretWrite(outFile, 1, 2); // Compression Code
    reinterpretWrite(outFile, 1, 2); // Number of Channels
    reinterpretWrite(outFile, mSampleRate, 4); // Sample Rate
    reinterpretWrite(outFile, mSampleRate * mBitDepth / 8, 4); // Byte Rate
    reinterpretWrite(outFile, mBitDepth / 8, 2); // Block Align
    reinterpretWrite(outFile, mBitDepth, 2); // Bit Depth

    // ----- DATA CHUNK ----- 
    outFile << "data";
    outFile << "----";

    int preAudioPosition = outFile.tellp(); // current position of pointer in stream

    for(int i = 0; i < mpValueArr->sizeGetter(); i++) { 
        int intSample = mpValueArr->get(i);
 
        // normal writing can't account for bit depth
        // here, we convert our sample into a constant character pointer
        // this allows granular control over the sample writing
        // &intSample exposes address of integer
        // the remaining two bits will leave only the value
        outFile.write(reinterpret_cast<char*> (&intSample), 2);
    }
    int postAudioPosition = outFile.tellp(); // current position of pointer
        
    outFile.seekp(preAudioPosition - 4); // seeking to header chunk after "data"
    reinterpretWrite(outFile, postAudioPosition - preAudioPosition, 4); // rewrite header chunk

    outFile.seekp(4, ios::beg); // seek to beginning
    reinterpretWrite(outFile, postAudioPosition-8, 4); // edit after RIFF
}

int SynthWave::mpValueArrSize() {
    return mpValueArr->sizeGetter(); 
}