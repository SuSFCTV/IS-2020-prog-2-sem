//
// Created by misha on 12.03.2021.
//
#include "polynomial.h"


Polynomial::Polynomial(){
    koef = new int[1]{0};
    deg = new int[1]{0};
    size = 1;
}

Polynomial::Polynomial(int min, int max, int *koef) {
    int s = max - min + 1;
    deg = new int[s];
    int t = min;
    for (int i = 0; i < s; i++){
        deg[i] = t;
        t++;
    }
    size = s;
}

Polynomial::Polynomial(const Polynomial &other){ //Copy
    deg = other.deg;
    koef = new int[size + 1];
    for (int i = 0; i < size; i++){
        koef[i] = other.koef[i];
    }
}

Polynomial::~Polynomial(){
    delete[] koef;
}

int Polynomial::GetDeg(){
    return deg[size];
}

Polynomial &Polynomial::operator [] (int i){
    if(i<=size)
        return koef[i];
    else
        return 0.0;
};
