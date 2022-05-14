#ifndef I_WAVE_H
#define I_WAVE_H

#include "Array.hpp"
#include <fstream>

class Wave {

    public: 
        virtual int mpValueArrSize() = 0;
        virtual void write(ofstream& outFile) = 0; 
        virtual ~Wave() = 0; 

        Wave(); 
        
        int sampleRateGetter()const; 
        float bitDepthGetter()const; 
        float durationGetter()const; 

    protected: 
        // characterisics of wave
        int mSampleRate;
        int mBitDepth;
        unsigned int mDuration;
};

#endif