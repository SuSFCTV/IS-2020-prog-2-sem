//
// Created by misha on 11.03.2021.
//

#ifndef HOMEWORK2_POLYNOMIAL_H
#define HOMEWORK2_POLYNOMIAL_H

#include "vector"
#include "cmath"
#include "sstream"


using namespace std;

class Polynomial {
private:
    int* deg;
    int* koef;
    //todo int, new
    int* size;
public:
    Polynomial();
    Polynomial(int min, int max, int* odd);
    Polynomial(const Polynomial &p);

    ~Polynomial();

    Polynomial &operator=(const Polynomial &p);
    friend bool operator==(const Polynomial &lhs, const Polynomial &rhs);
    friend bool operator!=(const Polynomial &lhs, const Polynomial &rhs);

    friend Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs);
    friend Polynomial operator-(const Polynomial &p);
    friend Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs);

    friend Polynomial operator+=(Polynomial &lhs, const Polynomial &rhs);
    friend Polynomial operator-=(Polynomial &lhs, const Polynomial &rhs);

    friend Polynomial operator*(const Polynomial &p, int number);
    friend Polynomial operator*(int number, const Polynomial &p);
    friend Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs);
    friend Polynomial operator/(const Polynomial &p, int number);

    friend Polynomial operator*=(Polynomial &lhs, const Polynomial &rhs);
    friend Polynomial operator/=(Polynomial &p, int number);

    friend std::stringstream &operator<< (std::stringstream &out, const Polynomial &p);
    friend Polynomial &operator>> (std::stringstream &in, Polynomial &p);

    int &operator[](int i);
    int &operator[](int number) const;

    double &get(double number);
};





#endif //HOMEWORK2_POLYNOMIAL_H
