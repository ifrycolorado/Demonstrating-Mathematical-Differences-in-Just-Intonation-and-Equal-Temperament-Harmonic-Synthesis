#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

using namespace std;

template<typename T>
class Array {

    private: 
        unsigned int mSize;
        T *mpArr;

    public: 

        // big three
        Array(); 
        Array(const int SIZE); 
        ~Array(); 
        Array &operator=(const Array&OTHER);

        // position functions
        void set(const int POS, const T VAL); 
        T get(const int POS)const; 
        int find(const T VAL)const; 

        // getters and setters
        void sizeSetter(const int SIZE); // unused
        unsigned int sizeGetter()const; 

        // format functions
        void printArr(const int CAP)const;
        friend ostream& operator<<(ostream &os, Array<T>*& ARRAY);

};

template<typename T>
Array<T>::Array() {
    mSize = 0;
    mpArr = new T[0];
}

template<typename T>
Array<T>::Array(const int SIZE) {
    mSize = SIZE;
    mpArr = new T[SIZE];
}

template<typename T> 
Array<T>::~Array() {
    mSize = 0;
    delete[] mpArr;
    mpArr = nullptr;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& OTHER) {
    
    delete[] mpArr; // delete current array

    this->mSize = OTHER.mSize(); 
    mpArr = new T[mSize];
    
    for(int i = 0; i < mSize; i++) {
        mpArr[i] = OTHER[i];
    }
}

template<typename T>
void Array<T>::set(const int POS, const T VAL) {
    if (POS >= 0 && POS < mSize) {
        mpArr[POS] = VAL;
    }
}

template<typename T>
T Array<T>::get(const int POS)const {
    if (POS >= 0 && POS < mSize) {
        return mpArr[POS];
    } else {
        return T();
    }
}

template<typename T> 
int Array<T>::find(const T VAL)const {

    for (int i = 0; i < mSize; i++) {
        if (this->at(i) == VAL) {
            return i;
        }
    }
    return -1;
}

template<typename T> 
unsigned int Array<T>::sizeGetter()const {
    return mSize; 
}

template<typename T> 
ostream& operator<< (ostream &os, Array<T>*& ARRAY) {
    for(int i = 0; i < ARRAY->sizeGetter(); i++) {
        os << ARRAY->get(i) << " ";
    } os << endl; 
    return os; 
}

template<typename T> 
void Array<T>::printArr(const int CAP)const {
    int max = 0;
    if (CAP <= 0) {max = this->sizeGetter();}
    else {max = CAP;};

    for(int i = 0; i < max; i++) {
        T temp = this->get(i); 
        cout << temp << " ";
    } 
}

#endif 