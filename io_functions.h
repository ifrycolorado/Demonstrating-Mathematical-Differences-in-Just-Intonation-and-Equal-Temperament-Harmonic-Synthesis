#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include "Array.hpp"

string prompt_user_for_filename();
int get_user_input_key(Array<string>& keyArray);
void get_user_input_characteristics(unsigned int& duration, double& amplitude);
bool open_file(ifstream &inFile, string filename);
void reinterpretWrite(ofstream &outFile, int value, int size);

#endif