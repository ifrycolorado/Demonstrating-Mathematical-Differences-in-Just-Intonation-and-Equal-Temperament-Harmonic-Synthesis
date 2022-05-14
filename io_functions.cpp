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
 * Includes general I/O functions to accept user commands
 */

#include "io_functions.h"
#include "Array.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/**
 * @brief gets inputs from user without allowing them to commit an error
 */
int get_user_input_key(Array<string>& keyArray) {

    int userChoice;
    
    cout << "How many steps above or below A would you like to go?" << endl; 
    cout << "(Add or substract 12 to value to make it an octave higher or lower)" << endl; 
    cout << "** WARNING: going too high (greater than 15) or too low (less than -15) will make it difficult to hear **" << endl << endl; 
    // Input validation loop demonstrated in class
    while (true) {

        for(int i = 0; i < keyArray.sizeGetter(); i++) {
            cout << i << ": " << keyArray.get(i) << endl; 
        }

        cout << endl << "Choice: "; 
        cin >> userChoice;
        cout << endl; 
        if (!cin.fail()) {break;}; 
        cerr << "Error encounted. Please enter a valid number.\n\n";
        cin.clear();

        char badChar;
        do {badChar = cin.get();} while (badChar != '\n');
            }

    return userChoice;
}

/**
 * @brief prompts user for a filename
 * @returns string of desired filename
 */
string prompt_user_for_filename() {

    // initalize string
    string user_string;

    // ask for name
    cout << "Howdy! Please enter a file name: ";
    cin >> user_string;
    cout << endl;

    return user_string;
}

/**
 * @brief gets inputs from user without allowing them to commit an error
 */
void get_user_input_characteristics(unsigned int& duration, double& amplitude) {

    cout << "\nHow long would you like the example to be (in seconds)?" << endl;
    cout << "** WARNING: Please be reasonable in length, not more than 20 seconds **" << endl; 
    // Input validation loop demonstrated in class
    while (true) {

        cout << endl << "Choice: "; 
        cin >> duration;
        cout << endl; 
        if (!cin.fail() && duration <= 20) {break;}; 
        cerr << "Error encounted. Please enter a valid number.\n\n";
        cin.clear();

        char badChar;
        do {badChar = cin.get();} while (badChar != '\n');
            }
    
    cout << "--------------------------------" << endl; 

    cout << "\nWhat would you like the amplitude to be?" << endl; 
    cout << "** WARNING: Amplitude scales rapidly, not more than 1 **" << endl; 
    cout << "(0.5 is recommended)" << endl; 
     while (true) {

        cout << endl << "Choice: "; 
        cin >> amplitude;
        cout << endl; 
        if (!cin.fail() && amplitude <= 1) {break;}; 
        cerr << "Error encounted. Please enter a valid number.\n\n";
        cin.clear();

        char badChar;
        do {badChar = cin.get();} while (badChar != '\n');
            }
    cout << "--------------------------------" << endl; 
}

/**
 * @brief opens file 
 * @param inFile input file stream 
 * @param filename name of file
 * @return boolean reflecting ability to open file 
 */
bool open_file(ifstream &inFile, string filename) {
    inFile.open(filename);

    cout << "Opening " << filename << "..." << endl; 

    // check for failure
    if (!inFile.fail()) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief writes to outFile with specific bit depth requirements
 * @param outFile ofstream
 * @param value value to decompose
 * @param size size after decomposition
 */
void reinterpretWrite(ofstream &outFile, int value, int size) {
    outFile.write(reinterpret_cast<const char*> (&value), size); 
}