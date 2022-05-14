#ifndef SINE_WAVE_H
#define SINE_WAVE_H

#include "Array.hpp"
#include "Wave.h"
#include <string>

class SineWave : public Wave {

    public:
        SineWave(const double freq, const double amp, 
                    const int sample, const unsigned int duration,
                    const int bitDepth, const int note);  
        ~SineWave(); 
        friend bool operator==(const SineWave& LHS, const SineWave& RHS);
        void generate(); 
        void write(ofstream& outFile); 
        int mpValueArrSize(); 

        float mpValueArrAtPoint(const int POINT);
        float ampGetter()const; 
        float freqGetter()const; 
        int noteGetter()const;

        void noteSetter(const int newNote);

    protected: 
        float mTone; 
        float mFrequency; 
        float mAmplitude;
        int mNote;

    private:
        // values of wave
        Array<float>* mpValueArr;

};

#endif