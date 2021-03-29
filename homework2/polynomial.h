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
    int* deg{};
    int* koef{};
    int size{};
    int min_d;
    int max_d;
public:
    Polynomial();
    Polynomial(int min, int max, int* odd);
    Polynomial(const Polynomial &p);

    ~Polynomial();
    void resize_koef(int t_size, int bias);
    Polynomial &operator=(const Polynomial &p);
    bool operator==(const Polynomial &rhs);
    bool operator!=(const Polynomial &rhs);

    friend Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs);
    friend Polynomial operator-(const Polynomial &p);
    friend Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs);

    //friend Polynomial operator+=(const Polynomial &lhs, const Polynomial &rhs);
    Polynomial operator+=(const Polynomial &rhs);
    friend Polynomial operator-=(Polynomial &lhs, const Polynomial &rhs);

    friend Polynomial operator*(const Polynomial &p, int number);
    friend Polynomial operator*(int number, const Polynomial &p);
    friend Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs);
    friend Polynomial operator/(const Polynomial &p, int number);

    friend Polynomial operator*=(Polynomial &lhs, const Polynomial &rhs);
    friend Polynomial operator/=(Polynomial &p, int number);

    friend std::stringstream &operator<< (std::stringstream &out, const Polynomial &p);
    friend Polynomial &operator>> (std::stringstream &in, Polynomial &p);

    int &operator[](int i) ;
    int operator[](int number) const;

    double get(double number);
};





#endif //HOMEWORK2_POLYNOMIAL_H
