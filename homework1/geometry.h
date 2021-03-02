//
// Created by misha on 23.02.2021.
//

#ifndef CPP1_GEOMETRY_H
#define CPP1_GEOMETRY_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

using namespace std;
class Point {
private:
    int c_x, c_y;
public:
    explicit Point(int x = 0, int y = 0) : c_x(x), c_y(y) {}
    int getX() const {
        return c_x;
    }

    int getY() const{
        return c_y;
    }
    Point(const Point &other) {
        c_x = other.c_x;
        c_y = other.c_y;
    }

    static double distance(const Point& p_1, const Point& p_2)
    {
        double ans;
        ans = sqrt(pow(p_1.getX() - p_2.getX(), 2) + pow(p_1.getY() - p_2.getY(), 2));
        return ans;
    }

    Point &operator=(const Point &other) = default;
};

class PolygonalChain : public Point{
private:
    vector <Point> poly_chain;
    int poly_number;
public:
    PolygonalChain() {
        poly_number = 0;
    }
    PolygonalChain(int number, Point chain[]){
        poly_number = number;
        for (int i = 0; i < poly_number; i++) {
            poly_chain.push_back(chain[i]);
        }
    }
    virtual ~PolygonalChain() {
        poly_chain.clear();
    }
    int getN() const{
        return poly_number;
    }
    Point getPoint(int number) const{
        return poly_chain[number];
    }
    PolygonalChain(const PolygonalChain &other) : Point(other){
        poly_number = other.poly_number;
        poly_chain = other.poly_chain;
    }
    virtual double perimeter() const {
        double ans = 0;
        for (int i = 0; i < getN() - 1; i++){
            ans += distance(getPoint(i), getPoint(i+1));
        }
        return ans;
    }
    PolygonalChain &operator=(const PolygonalChain &other) = default;
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain() : PolygonalChain() {};
    ClosedPolygonalChain(int n, Point *chain) : PolygonalChain(n, chain) {}

    double perimeter() const override {
        double ans = PolygonalChain :: perimeter();
        ans += distance(getPoint(0), getPoint(getN() - 1));
        return ans;
    }
    ClosedPolygonalChain(const ClosedPolygonalChain &other)  = default ;

    ClosedPolygonalChain &operator=(const ClosedPolygonalChain &other) = default;
};

class Polygon : public ClosedPolygonalChain {

public:
    Polygon() : ClosedPolygonalChain() {};
    Polygon(int n, Point *chain) : ClosedPolygonalChain(n , chain) {};
    Polygon(const Polygon &other)  = default;
    virtual double area() const {
        double ans = perimeter() / 2;
        for (int i = 0; i < getN() - 1; i++){
            ans *= (perimeter()/2 - (distance(getPoint(i), getPoint(i+1))));
        }
        ans *= (perimeter()/2 - (distance(getPoint(getN() - 1), getPoint(0))));
        return sqrt(ans);
    }
    Polygon &operator=(const Polygon &other) = default;
};

class Triangle : public Polygon {
public:
    Triangle() : Polygon() {};

    Triangle(int n, Point *chain) : Polygon(n, chain) {};

    Triangle(const Triangle &other)  = default;

    bool hasRightAngle() const {
        double side_1, side_2, side_3;
        side_1 = distance(getPoint(0), getPoint(1));
        side_2 = distance(getPoint(1), getPoint(2));
        side_3 = distance(getPoint(2), getPoint(0));

        if (side_1 > side_2) {
            swap(side_1, side_2);
        }
        if (side_2 > side_3){
            swap(side_2, side_3);
        }
        if (side_1 * side_1 + side_2 * side_2 == side_3 * side_3){
            return true;
        }
        else{
            return false;
        }
    }
    Triangle &operator=(const Triangle &other) = default;
};

class Trapezoid : public Polygon {
public:
    Trapezoid() : Polygon() {};

    Trapezoid(int n, Point *chain) : Polygon(n, chain) {};

    Trapezoid(const Trapezoid &other)  = default;
    double height() const {
        double side_1, side_2, side_3, side_4, ans;

        side_1 = distance(getPoint(0), getPoint(3));
        side_2 = distance(getPoint(1), getPoint(2));
        side_3 = distance(getPoint(0), getPoint(1));
        side_4 = distance(getPoint(2), getPoint(3));

        ans = sqrt(pow(side_3, 2) - pow(((pow(side_1 - side_2, 2) +
                                          pow(side_3, 2) - pow(side_4, 2)) / (2 * (side_1 - side_2))), 2));
        return ans;

    }
    Trapezoid &operator=(const Trapezoid &other) = default;
};
class RegularPolygon : public Polygon {
public:
    RegularPolygon() : Polygon() {};

    RegularPolygon(int n, Point *chain) : Polygon(n, chain){};

    RegularPolygon(const RegularPolygon &other)  = default;

    double area() const override {
        double side = distance(getPoint(0), getPoint(1));
        double ans = (getN() * pow(side, 2.0)) / (4 * tan(M_PI / getN()));
        return ans;
    }
    RegularPolygon &operator=(const RegularPolygon &other) = default;
};

#endif //CPP1_GEOMETRY_H

