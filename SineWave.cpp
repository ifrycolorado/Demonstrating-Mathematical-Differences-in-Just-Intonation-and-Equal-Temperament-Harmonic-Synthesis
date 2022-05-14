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
 * Implements Wave class as a characteristic SineWave with its own frequency and tone.
 */

#include "Wave.h"
#include "SineWave.h"
#include <cmath>
#include "Array.hpp"
#include <fstream>
#include "io_functions.h"

#include <iostream> 

using namespace std; 

const float MY_PI = 3.14159265358979323846264338327950288;

/**
 * @brief general constructor that adheres to file info and creates a characteristic tone
 * @param freq frequency
 * @param amp amplitude
 * @param sample sample rate (usually 44100)
 * @param duration length in seconds
 * @param bitDepth bit depth (usually 16)
 * @param note steps above A in keyArray  
 */

SineWave::SineWave(const double freq, const double amp, 
                    const int sample, const unsigned int duration,
                    const int bitDepth, const int note) {
    
    mFrequency = freq; 
    mAmplitude = amp; 
    mSampleRate = sample; 
    mDuration = duration;
    mBitDepth = bitDepth;
    mNote = note; 

    mTone = 2 * MY_PI * mFrequency / mSampleRate; // tone of wave

    mpValueArr = new Array<float>(mDuration*mSampleRate);
}

// mpValueArr has its own desructor
SineWave::~SineWave() {
    delete mpValueArr;
}

void SineWave::generate() {
    double currAngle = 0;
    // float maxAmp = pow(2, mBitDepth - 1) - 1;
    for (int i = 0; i < (mDuration * mSampleRate); i++) {

        double currSample = mAmplitude*sin(currAngle); // collect value
        // int intSample = static_cast<int> (currSample * maxAmp); // cast as int
        // cout << "CURR SAMPLE IN SINE WAVE: " << currSample << endl; 
        mpValueArr->set(i, currSample); // set to array
        currAngle += mTone; // iterate characteristic tone
    }
}

bool operator==(const SineWave& LHS, const SineWave& RHS) {
    if (LHS.sampleRateGetter() == RHS.sampleRateGetter() &&
        LHS.durationGetter() == RHS.durationGetter() &&
        LHS.bitDepthGetter() == RHS.bitDepthGetter()) {
            return true; 
    } else {
        return false; 
    }
}

float SineWave::mpValueArrAtPoint(const int POINT) {
    return mpValueArr->get(POINT);
}

float SineWave::ampGetter()const {
    return mAmplitude;
}

float SineWave::freqGetter()const {
    return mFrequency;
}

int SineWave::noteGetter()const {
    return mNote; 
}

void SineWave::noteSetter(const int newNote) {
    mNote = newNote;
}

int SineWave::mpValueArrSize() {
    return mpValueArr->sizeGetter(); 
}

void SineWave::write(std::ofstream& outFile) {

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
        cout << "WRITING THIS TO FILE: " << intSample << endl; 
 
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