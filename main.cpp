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
 * In mathematical music theory, there are two general tuning systems:
    equal temperament and just intonation. Equal temperament relies on equal intervals between
    octaves using the square root of 2 as an equalizing ratio, while just intonation uses the
    mathematical ratio between intervals for optimal resonance (e.g. a perfect fifth is 3:2, a perfect
    major third is 5:4). I plan to use harmonic synthesis techniques to combine two discrete sinusoidal waveforms
    into a single audio file for both the equal temperament and just intonation models, while also
    printing some values of the sine wave to mathematically demonstrate the difference. 
 */

#include "io_functions.h"
#include "Array.hpp"
#include "Wave.h"
#include "SineWave.h"
#include "SynthWave.h"

#include <fstream>
#include <string>
#include <vector> 
#include <cmath>

using namespace std; 

int main() {

    // globally referenced variables

    /* A note about A_ROOT: 
        yes, means any other root note besides A is calculated from 
        the equal temperament distance from A.
        However, there is no other way to easily and consistently achieve
        a starting note frequency. 
    */
    const double A_ROOT = 440; 
    unsigned int globalDuration = 0; 
    int globalSteps;
    double globalAmplitude = 0; 
    string temp; // used in file reading
    const double ET_SQRT_4 = pow(2, ((double) (4.0)/ (double) (12.0))); // ET for major third
    const double ET_SQRT_7 = pow(2, ((double) (7.0)/ (double) (12.0))); // ET for minor third

    // vectors for SineWaves
    vector<SineWave*> JIVector; // holds all for Just Intonation for run
    vector<SineWave*> ETVector; // holds all Equal Temperament for run
    vector<SineWave*> bothVector; // holds all waves for run

    // -------- INITIALIZATION -------

    ifstream keyFile; // reads in data from KeyData.txt
    Array<string> keyArray(12); // holds note values referenced throughout program

    if(open_file(keyFile, "KeyData.txt")) { // reads in notes to keyArray
        for(int i = 0; i < keyArray.sizeGetter(); i++) {
            keyFile >> temp;
            keyArray.set(i, temp); 
        }
        cout << endl; 
    } else {
        cout << "Could not find KeyData.txt\nEnding now" << endl; 
        keyFile.close(); 
        return -1; 
    }

    // -------- GETTING USER INPUT -------
    ofstream JIFile, ETFile, bothFile;
    JIFile.open("Just_Intonation.wav", ios::binary); 
    ETFile.open("Equal_Temperament.wav", ios::binary);
    bothFile.open("Both_Styles.wav", ios::binary); 

    globalSteps = get_user_input_key(keyArray); // set how many semitones from A the root note is
    cout << "--------------------------------" << endl; 
    get_user_input_characteristics(globalDuration, globalAmplitude); // sets duration and amplitude

    const double GIVEN_ROOT = A_ROOT * pow(2,(double) (globalSteps)/(12.0)); // calculates root note 

    // -------- GENERATING SINE WAVES AND ADDING TO VECTORS -------

    int adjustedAccessNote = globalSteps; // adjusts steps to access keyArray
    if (globalSteps < 0) {
        adjustedAccessNote = globalSteps + 12; 
    }

    /* A note about initializing the waves:
        The sample rate (44100) and bit depth (16) are constant, 
        but only for ease of use for the UI. Since I want to make sure
        my evaluators can use and understand this program, I made it 
        impossible to mess with the sample rate and bit depth. 
        Furthermore, the intervals between notes could be changed. 
        However, I don't trust computer science evaluators to understand
        what different intervals should sound like. 
    */
    SineWave sineRoot(GIVEN_ROOT, globalAmplitude, 44100, globalDuration, 16, (adjustedAccessNote % 12)); // ROOT 
    SineWave sineJI3(GIVEN_ROOT*1.25, globalAmplitude, 44100, globalDuration, 16, ((adjustedAccessNote+4) % 12)); // JI 3rd
    SineWave sineJI5(GIVEN_ROOT*1.5, globalAmplitude, 44100, globalDuration, 16, ((adjustedAccessNote+7) % 12)); // JI 5th
    SineWave sineET3(GIVEN_ROOT*(ET_SQRT_4), globalAmplitude, 44100, globalDuration, 16, ((adjustedAccessNote+4) % 12)); // ET 3rd
    SineWave sineET5(GIVEN_ROOT*(ET_SQRT_7), globalAmplitude, 44100, globalDuration, 16, ((adjustedAccessNote+7) % 12)); // ET 5th

    // create synth wave outlines
    SynthWave synthJI(44100, globalDuration, 16); // Synthesis for JI
    SynthWave synthET(44100, globalDuration, 16); // Synthesis for ET
    SynthWave synthBoth(44100, globalDuration, 16); // Synthesis for Both

    // Just Intonation vector pushes
    JIVector.push_back(&sineRoot);
    JIVector.push_back(&sineJI3);
    JIVector.push_back(&sineJI5);

    // Equal Temperament vector pushes
    ETVector.push_back(&sineRoot);
    ETVector.push_back(&sineJI3);
    ETVector.push_back(&sineJI5);

    // Both Styles vector pushes
    bothVector.push_back(&sineRoot);
    bothVector.push_back(&sineJI3);
    bothVector.push_back(&sineET3);
    bothVector.push_back(&sineJI5);
    bothVector.push_back(&sineET5);

    // generate each of the sine waves
    for (int i = 0; i < bothVector.size(); i++) {
        bothVector.at(i)->generate(); 
    }

    cout << "For a numerical reference, here's first 10 values each wave." << endl; 
    cout << "441000 different values are generated each second, so these small differences manifest large changes." << endl << endl; 
    cout << "Notice how the fifths are relatively close, but the thirds vary quite widely" << endl << endl; 

    // some console I/O to demonstrate the numerical difference
    getline(keyFile, temp);
    for(int i = 0; i < bothVector.size(); i++) {
        getline(keyFile, temp);
        cout << temp << ": (" << keyArray.get(bothVector.at(i)->noteGetter()) << " is " << bothVector.at(i)->freqGetter() << " Hz) " << endl;
        for(int j = 0; j < 10; j++) {
            cout << bothVector.at(i)->mpValueArrAtPoint(j) << fixed << " ";
        } cout << endl << endl; 
    }

    // generate the syntehsis waves
    if (!synthBoth.generate(bothVector)) {
        cout << "Something happened! Quitting now" << endl;
        return 0; 
    }

    if (!synthET.generate(ETVector)) {
        cout << "Something happened! Quitting now" << endl;
        return 0; 
    }

    if (!synthJI.generate(JIVector)) {
        cout << "Something happened! Quitting now" << endl;
        return 0; 
    }

    // some explanation console output
    cout << "SYNTEHSIS COMPLETED!" << endl << endl; 
    cout << "Please look in this program's directory for three .wav files:" << endl; 
    cout << "   Both_Styles.wav\n   Equal_Temperament.wav\n   Just_Intonation.wav" << endl; 
    cout << "\nListening to Equal_Temperament.wav and Just_Intonation.wav, you might not hear a difference." << endl; 
    cout << "However, the Both_Styles.wav includes both the Equal Temperament and Just Intonation tuning systems." << endl; 
    cout << "You can hear a \"wobble\", which indicates dissonance." << endl; 

    cout << endl << "The wobble proves this program works." << endl << endl; 
    cout << "(Technically, the Equal Temperament has a wobble, but it's difficult to hear)" << endl << endl; 

    // write it to the files
    synthBoth.write(bothFile);
    synthJI.write(JIFile);
    synthET.write(ETFile); 
    
    // close and clean
    bothFile.close();
    JIFile.close();
    ETFile.close(); 
    keyFile.close(); 

    // vectors will automatically deconstruct the Waves

    return 0; 
}