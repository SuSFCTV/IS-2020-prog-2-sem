//
// Created by misha on 02.04.2021.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <map>
#include <set>
#include <cmath>
#include "pugixml.hpp"
using namespace std;
using std::pair;
using std::vector;
using std::cout;
using std::map;
using std::set;
using std::string;
using std::stringstream;
#ifndef MAIN_CPP_ANALYSIS_H
#define MAIN_CPP_ANALYSIS_H

class XmlElem {
private:
    int num;
    string type_of_vehicle;
    string name_stopping;
    string the_official_name;
    vector<string> location;
    vector<string> routes;
    pair<double, double> coordinates;

public:
    XmlElem(int num, string type_of_vehicle, string name_stopping, string the_official_name, vector<string> location,
            vector<string> routes, pair<double, double> coordinates);

    string get_type_of_vehicle() const;

    string get_name_stopping() const;

    string get_the_official_name() const;

    vector<string> get_location() const;

    vector<string> get_routes() const;

    double get_coordinates_x() const;

    double get_coordinates_y() const;

    int get_num() const;

    string get_index(int index) const;

    int get_size() const;
};
class Routes {
public:
    string route;
    vector<XmlElem> Bus;
    vector<XmlElem> Tram;
    vector<XmlElem> Trolleybus;
};
double coordinatesLength(const XmlElem &first, const XmlElem &second);
void separator(const string &thing, string &firstItem, string &secondItem);
string sepLocation(string &thing);
void parser(vector<XmlElem> &thing, map<string, Routes> &mappedRoutes, set<string> &nameRoutes,
            map<string, int> &locations);
void set_all_information(vector<XmlElem> &element, map<string, int> &tram_routes, map<string, int> &bus_routes,
                         map<string, int> &trolleybus_routes);
void set_count(map<string, int> &routes, int &counter, string &max_routes);
void set_routes(set<string> &names, map<string, Routes> &routes, map<string, float> &tram_routes_size,
                map<string, float> &bus_routes_size, map<string, float> &trolleybus_routes_size);
void set_size(map<string, float> &routes_size, float &path_counter, string &max_route);
void max_routes(int &maximum, string &max_size, map<string, int> &locations);
#endif //MAIN_CPP_ANALYSIS_H
