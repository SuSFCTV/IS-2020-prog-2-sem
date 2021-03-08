//
// Created by misha on 08.03.2021.
//
#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include "geometry.h"

using namespace std;


Point::Point(int x, int y) : c_x(x), c_y(y) {}

int Point::getX() const {
    return c_x;
}

int Point::getY() const {
    return c_y;
}

Point::Point(const Point &other) {
    c_x = other.c_x;
    c_y = other.c_y;
}

Point::~Point() = default;

double Point::distance(const Point &p_1, const Point &p_2) {
    double ans;
    ans = sqrt(pow(p_1.getX() - p_2.getX(), 2) + pow(p_1.getY() - p_2.getY(), 2));
    return ans;
}

Point &Point::operator=(const Point &other) = default;


PolygonalChain::PolygonalChain() {
    poly_number = 0;
}

PolygonalChain::PolygonalChain(int number, Point chain[]) {
    poly_number = number;
    for (int i = 0; i < poly_number; i++) {
        poly_chain.push_back(chain[i]);
    }
}

int PolygonalChain::getN() const {
    return poly_number;
}

Point PolygonalChain::getPoint(int number) const {
    return poly_chain[number];
}

PolygonalChain::PolygonalChain(const PolygonalChain &other) : Point(other) {
    poly_number = other.poly_number;
    poly_chain = other.poly_chain;
}

double PolygonalChain::perimeter() const {
    double ans = 0;
    for (int i = 0; i < getN() - 1; i++) {
        ans += distance(getPoint(i), getPoint(i + 1));
    }
    return ans;
}

PolygonalChain &PolygonalChain::operator=(const PolygonalChain &other) = default;


ClosedPolygonalChain::ClosedPolygonalChain() : PolygonalChain() {};

ClosedPolygonalChain::ClosedPolygonalChain(int n, Point *chain) : PolygonalChain(n, chain) {}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain &other) = default;

double ClosedPolygonalChain::perimeter() const {
    double ans = PolygonalChain::perimeter();
    ans += distance(getPoint(0), getPoint(getN() - 1));
    return ans;
}

ClosedPolygonalChain &ClosedPolygonalChain::operator=(const ClosedPolygonalChain &other) = default;


Polygon::Polygon() : ClosedPolygonalChain() {};

Polygon::Polygon(int n, Point *chain) : ClosedPolygonalChain(n, chain) {};

Polygon::Polygon(const Polygon &other) = default;

double Polygon::area() const {
    double first = 0, second = 0, a;
    for (int i = 0; i < getN() - 1; i++) {
        first += this->getPoint(i).getX() * this->getPoint(i + 1).getY();
    }
    first += this->getPoint(getN() - 1).getX() * this->getPoint(0).getY();

    for (int i = 0; i < getN() - 1; i++) {
        second += this->getPoint(i).getY() * this->getPoint(i + 1).getX();
    }
    second += this->getPoint(getN() - 1).getY() * this->getPoint(0).getX();

    a = abs(first - second) / 2;

    return a;
}

Polygon &Polygon::operator=(const Polygon &other) = default;


Triangle::Triangle() : Polygon() {};

Triangle::Triangle(int n, Point *chain) : Polygon(n, chain) {};

Triangle::Triangle(const Triangle &other) = default;

bool Triangle::hasRightAngle() const {
    double a = pow(getPoint(0).getX() - getPoint(1).getX(), 2) + pow(getPoint(0).getY() - getPoint(1).getY(), 2);
    double b = pow(getPoint(1).getX() - getPoint(2).getX(), 2) + pow(getPoint(1).getY() - getPoint(2).getY(), 2);
    double c = pow(getPoint(2).getX() - getPoint(0).getX(), 2) + pow(getPoint(2).getY() - getPoint(0).getY(), 2);

    return ((a + b == c) || (a + c == b) || (b + c == a));

}

Triangle &Triangle::operator=(const Triangle &other) = default;


Trapezoid::Trapezoid() : Polygon() {};

Trapezoid::Trapezoid(int n, Point *chain) : Polygon(n, chain) {};

Trapezoid::Trapezoid(const Trapezoid &other) = default;

double Trapezoid::height() const {
    double side_1, side_2, side_3, side_4, ans;

    side_1 = distance(getPoint(0), getPoint(3));
    side_2 = distance(getPoint(1), getPoint(2));
    side_3 = distance(getPoint(0), getPoint(1));
    side_4 = distance(getPoint(2), getPoint(3));

    ans = sqrt(pow(side_3, 2) - pow(((pow(side_1 - side_2, 2) +
                                      pow(side_3, 2) - pow(side_4, 2)) / (2 * (side_1 - side_2))), 2));
    return ans;

}

Trapezoid &Trapezoid::operator=(const Trapezoid &other) = default;


RegularPolygon::RegularPolygon() : Polygon() {};

RegularPolygon::RegularPolygon(int n, Point *chain) : Polygon(n, chain) {};

RegularPolygon::RegularPolygon(const RegularPolygon &other) = default;

double RegularPolygon::area() const {
    double side = distance(getPoint(0), getPoint(1));
    double ans = (getN() * pow(side, 2.0)) / (4 * tan(M_PI / getN()));
    return ans;
}

double RegularPolygon::perimeter() const {
    double a = distance(getPoint(0), getPoint(1));
    return a * getN();
}

RegularPolygon &RegularPolygon::operator=(const RegularPolygon &other) = default;

