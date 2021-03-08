//
// Created by misha on 23.02.2021.
//

#ifndef CPP1_GEOMETRY_H
#define CPP1_GEOMETRY_H
#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>

using namespace std;
//fixed cpp
//fixed  S P A C E S
//fixed destructor
//fixed area
//fixed perimeter regular polygon
//fixed return expression
//fixed "to do without sqrt"

class Point {
private:
    int c_x, c_y;
public:
    explicit Point(int x = 0, int y = 0);

    int getX() const;

    int getY() const;

    Point(const Point &other);

    virtual ~Point();

    static double distance(const Point &p_1, const Point &p_2);

    Point &operator=(const Point &other);
};

class PolygonalChain : public Point {
private:
    vector<Point> poly_chain;
    int poly_number;
public:
    PolygonalChain();

    PolygonalChain(int number, Point chain[]);

    int getN() const;

    Point getPoint(int number) const;

    PolygonalChain(const PolygonalChain &other);

    virtual double perimeter() const;

    PolygonalChain &operator=(const PolygonalChain &other);
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain();

    ClosedPolygonalChain(int n, Point *chain);

    ClosedPolygonalChain(const ClosedPolygonalChain &other);

    double perimeter() const override;

    ClosedPolygonalChain &operator=(const ClosedPolygonalChain &other);
};

class Polygon : public ClosedPolygonalChain {

public:
    Polygon();

    Polygon(int n, Point *chain);

    Polygon(const Polygon &other);

    virtual double area() const;

    Polygon &operator=(const Polygon &other);
};

class Triangle : public Polygon {
public:
    Triangle();

    Triangle(int n, Point *chain);

    Triangle(const Triangle &other);

    bool hasRightAngle() const;

    Triangle &operator=(const Triangle &other);
};

class Trapezoid : public Polygon {
public:
    Trapezoid();

    Trapezoid(int n, Point *chain);

    Trapezoid(const Trapezoid &other);

    double height() const;

    Trapezoid &operator=(const Trapezoid &other);
};

class RegularPolygon : public Polygon {
public:
    RegularPolygon();

    RegularPolygon(int n, Point *chain);

    RegularPolygon(const RegularPolygon &other);

    double area() const override;

    double RegularPolygon::perimeter() const override;

    RegularPolygon &operator=(const RegularPolygon &other);
};

#endif //CPP1_GEOMETRY_H

