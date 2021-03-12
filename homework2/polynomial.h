//
// Created by misha on 11.03.2021.
//

#ifndef HOMEWORK2_POLYNOMIAL_H
#define HOMEWORK2_POLYNOMIAL_H

class Polynomial {
private:
    int size;
    int *koef{};
    int *deg{};
public:
Polynomial();

Polynomial(int min , int max , int *koef);

Polynomial(const Polynomial &other);

~Polynomial();


int GetDeg();

Polynomial &operator [] (int i);

};





#endif //HOMEWORK2_POLYNOMIAL_H
