//
// Created by misha on 02.04.2021.
//
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include "pugixml.hpp"
#include <windows.h>
#include "analysis.h"
using namespace std;
using std::pair;
using std::vector;
using std::cout;
using std::map;
using std::set;
using std::string;
using std::stringstream;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<XmlElem> stations;
    map<string, Routes> routes;
    set<string> names;

    map<string, int> locations;
    map<string, int> tram_routes, bus_routes, trolleybus_routes;
    map<string, float> tram_routes_size, bus_routes_size, trolleybus_routes_size;


    string max_tram_routes, max_bus_routes, max_trolleybus_routes;
    string max_tram_route, max_bus_route, max_trolleybus_route;
    int tram_count = 0, bus_count = 0, troll_count = 0;
    float tram_path_counter = 0, bus_path_counter = 0, trolleybus_path_counter = 0;
    int maxi = 0;
    string maximum_size;

    parser(stations, routes, names, locations);
    set_all_information(stations, tram_routes, bus_routes, trolleybus_routes);

    set_count(tram_routes, tram_count, max_tram_routes);
    set_count(bus_routes, bus_count, max_bus_routes);
    set_count(tram_routes, troll_count, max_trolleybus_routes);

    cout << "The maxi number of tram stops is " << tram_count << " ||| Route no. -  "
         << max_trolleybus_routes << "\n";
    cout << "The maxi number of bus stops is " << bus_count << " ||| Route no. - " << max_bus_routes
         << "\n";

    set_routes(names, routes, tram_routes_size, bus_routes_size, trolleybus_routes_size);

    set_size(tram_routes_size, tram_path_counter, max_tram_route);
    set_size(bus_routes_size, bus_path_counter, max_bus_route);
    set_size(trolleybus_routes_size, trolleybus_path_counter, max_trolleybus_route);

    cout << "\n";
    cout << "The longest tram route: " << max_tram_route << "\n";
    cout << "The longest bus route: " << max_bus_route << "\n";
    cout << "The longest trolleybus route: " << max_trolleybus_route << "\n";

    max_routes(maxi, maximum_size, locations);
    cout << "\n" << "Maximum number on the street " << maximum_size << " = " << maxi << "\n";

    return 0;
}
