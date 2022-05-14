#include "Wave.h"
#include "io_functions.h"

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
 * Outlines general parameters of a wave. 
 */

using namespace std;

// general constructor that is used by all waves
Wave::Wave() {
    mBitDepth = 0;
    mSampleRate = 0; 
    mDuration = 0; 
}

Wave::~Wave() {};

int Wave::sampleRateGetter()const {
    return this->mSampleRate;
}

float Wave::bitDepthGetter()const {
    return this->mBitDepth;
}

float Wave::durationGetter()const {
    return this->mDuration; 
}