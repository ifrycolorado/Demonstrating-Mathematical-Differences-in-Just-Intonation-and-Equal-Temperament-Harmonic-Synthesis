#ifndef SYNTH_WAVE_H
#define SYNTH_WAVE_H

#include "Wave.h"
#include "SineWave.h"
#include <vector>

class SynthWave : public Wave {
    public: 
        SynthWave(); 
        ~SynthWave(); 
        SynthWave(const int sample, const unsigned int duration,
                    const int bitDepth);  
        bool generate(std::vector<SineWave*> sineWavesVector);
        void write(ofstream& outFile); 
        int mpValueArrSize();

    protected:
        Array<int>* mpValueArr; 
};

#endif