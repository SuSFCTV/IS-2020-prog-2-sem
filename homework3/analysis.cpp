//
// Created by misha on 02.04.2021.
//
#include "analysis.h"
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
const int radius_earth = 6731;
const int degree = 180;
XmlElem::XmlElem(int num, string type_of_vehicle, string name_stopping, string the_official_name, vector<string> location,
        vector<string> routes, pair<double, double> coordinates) :
        num(num), type_of_vehicle(type_of_vehicle), name_stopping(name_stopping),
        the_official_name(the_official_name), location(location), routes(routes), coordinates(coordinates) {};

string XmlElem::get_type_of_vehicle() const {
    return type_of_vehicle;
}

string XmlElem::get_name_stopping() const {
    return name_stopping;
}

string XmlElem::get_the_official_name() const {
    return the_official_name;
}

vector<string> XmlElem::get_location() const {
    return location;
}

vector<string> XmlElem::get_routes() const {
    return routes;
}

double XmlElem::get_coordinates_x() const {
    //cout << coordinates.first << "\n";
//    return coordinates.first;
    auto[first_coord, sec_coord] = coordinates;
    return first_coord;
}

double XmlElem::get_coordinates_y() const {
    //return coordinates.second;
    auto[first_coord, sec_coord] = coordinates;
    return sec_coord;
}

int XmlElem::get_num() const {
    return num;
}

string XmlElem::get_index(int index) const {
    return routes[index];
}

int XmlElem::get_size() const {
    return routes.size();
}
//fixed strange const
double coordinatesLength(const XmlElem &first, const XmlElem &second) {
    double first_latitude = first.get_coordinates_x() * M_PI / degree;
    double second_latitude = second.get_coordinates_x() * M_PI / degree;

    double first_longitude = first.get_coordinates_y() * M_PI / degree;
    double second_longitude = second.get_coordinates_y() * M_PI / degree;

    double general_latitude = second_latitude - first_latitude;
    double general_longitude = second_longitude - first_longitude;

    double ans = pow(sin(general_latitude / 2), 2) +
                    cos(first_latitude) * cos(second_latitude) * pow(sin(general_longitude / 2), 2);

    ans = 2 * asin(sqrt(ans)) * radius_earth;

    return ans;
}
void separator(const string &thing, string &firstItem, string &secondItem) {
    string div = ",";

    auto start = 0;
    auto finish = thing.find(div);

    while (finish != -1) {
        firstItem = thing.substr(start, finish - start);
        start = finish + div.length();
        finish = thing.find(div, start);
    }

    secondItem = thing.substr(start, finish);
}
string sepLocation(string &thing) {
    vector<string> subdiv{"ул.", " ул.", " УЛ.", " ш.", " Ш.", " шоссе", " ШОССЕ", " пер.",
                          " ПЕР.", " переулок",
                          " ПЕРЕУЛОК", " улица", "улица", " УЛИЦА", " бул",
                          " БУЛ", " бульвар", " БУЛЬВАР",
                          " пр",
                          " ПР", " проспект", " ПРОСПЕКТ"};

    for (auto &division : subdiv) {
        if (thing.find(division) != -1) {
            int firstVal = thing.find(division);
            int secondVal = firstVal + division.size();
            thing.erase(firstVal, secondVal);
        }
    }

    if (thing[thing.size() - 1] == ' ') {
        thing.erase(thing.end() - 1);
    }
    return thing;
}



void parser(vector<XmlElem> &thing, map<string, Routes> &mappedRoutes, set<string> &nameRoutes,
            map<string, int> &locations) {
    pugi::xml_document document;
    document.load_file("data1.xml");
    pugi::xml_node data = document.child("dataset");

    for (pugi::xml_node i = data.child("transport_station"); i; i = i.next_sibling("transport_station")) {

        string first_param;
        string second_param;
        float first_val;
        float second_val;

        separator(i.child_value("coordinates"), first_param, second_param);

        first_val = stof(first_param);
        second_val = stof(second_param);

       pair<double, double> coordinates;
        coordinates.first = first_val;
        coordinates.second = second_val;
//        auto [first_coord,sec_coord] = coordinates;
//        first_coord = first_val;
//        sec_coord = second_val;


        //МАРШРУТЫ
        first_param = "";
        second_param = "";

        string strRoutes = i.child_value("routes"), segment;
        stringstream tmp_StrRoutes(strRoutes);
        vector<string> vecRoutes;

        if (count(strRoutes.begin(), strRoutes.end(), ',')) {
            while (getline(tmp_StrRoutes, segment, ',')) {
                vecRoutes.push_back(segment);
            }
        } else {
            while (getline(tmp_StrRoutes, segment, '.')) {
                vecRoutes.push_back(segment);
            }
        }

        //МЕСТОПОЛОЖЕНИЯ
        first_param = "";
        second_param = "";

        string StrLoc = i.child_value("location");
        vector<string> vectLoc;
        stringstream tmp_StrLoc(StrLoc);

        if (count(StrLoc.begin(), StrLoc.end(), ',') && !StrLoc.empty()) {
            while (getline(tmp_StrLoc, segment, ',')) {
                if (segment[0] == ' ') {
                    segment.erase(segment.begin());
                }
                vectLoc.push_back(sepLocation(segment));
                locations[sepLocation(segment)] += 1;
            }
        } else if (!StrLoc.empty()) {
            vectLoc.push_back(sepLocation(StrLoc));
            locations[sepLocation(StrLoc)] += 1;
        }

        int numValue = stoi(i.child_value("number"));
        string vehicle_type = i.child_value("type_of_vehicle");
        string name_stopping = i.child_value("name_stopping");
        string the_official_name = i.child_value("the_official_name");
        thing.emplace_back(
                XmlElem(numValue, vehicle_type, name_stopping, the_official_name, vectLoc, vecRoutes,
                        coordinates));

        if (!strcmp(i.child_value("type_of_vehicle"), "Трамвай")) {
            for (int j = 0; j < vecRoutes.size(); ++j) {
                mappedRoutes[vecRoutes[j]].Tram.emplace_back(
                        XmlElem(numValue, vehicle_type, name_stopping, the_official_name, vectLoc, vecRoutes,
                                coordinates));

                mappedRoutes[vecRoutes[j]].route = vecRoutes[j];
                nameRoutes.insert(vecRoutes[j]);
            }

        } else if (!strcmp(i.child_value("type_of_vehicle"), "Автобус")) {
            for (int j = 0; j < vecRoutes.size(); ++j) {
                mappedRoutes[vecRoutes[j]].Bus.emplace_back(
                        XmlElem(numValue, vehicle_type, name_stopping, the_official_name, vectLoc, vecRoutes,
                                coordinates));

                mappedRoutes[vecRoutes[j]].route = vecRoutes[j];
                nameRoutes.insert(vecRoutes[j]);
            }
        } else if (!strcmp(i.child_value("type_of_vehicle"), "Троллейбус")) {
            for (int j = 0; j < vecRoutes.size(); ++j) {
                mappedRoutes[vecRoutes[j]].Trolleybus.emplace_back(
                        XmlElem(numValue, vehicle_type, name_stopping, the_official_name, vectLoc, vecRoutes,
                                coordinates));

                mappedRoutes[vecRoutes[j]].route = vecRoutes[j];
                nameRoutes.insert(vecRoutes[j]);
            }
        }
    }
}
void set_all_information(vector<XmlElem> &element, map<string, int> &tram_routes, map<string, int> &bus_routes,
                         map<string, int> &trolleybus_routes) {
    for (auto const &i : element) {
        if (i.get_type_of_vehicle() == "Трамвай") {
            for (int j = 0; j < i.get_size(); j++)
                tram_routes[i.get_index(j)] += 1;
        } else if (i.get_type_of_vehicle() == "Автобус") {
            for (int j = 0; j < i.get_size(); j++)
                bus_routes[i.get_index(j)] += 1;
        } else if (i.get_type_of_vehicle() == "Троллейбус") {
            for (int j = 0; j < i.get_size(); j++)
                trolleybus_routes[i.get_index(j)] += 1;
        }
    }
}
void set_count(map<string, int> &routes, int &counter, string &max_routes) {
//    for (auto const i : routes)
//        if (i.second > counter) {
//            counter = i.second;
//            max_routes = i.first;
//        }
    for(auto[a, b] : routes)
        if (b > counter){
            counter = b;
            max_routes = a;
        }
}
void set_routes(set<string> &names, map<string, Routes> &routes, map<string, float> &tram_routes_size,
                map<string, float> &bus_routes_size, map<string, float> &trolleybus_routes_size) {
    for (auto const j : names) {
        if (routes[j].Tram.size() > 1) {
            for (int k = 0; k < routes[j].Tram.size() - 1; k++)
                tram_routes_size[routes[j].route] += coordinatesLength(routes[j].Tram[k], routes[j].Tram[k + 1]);
        }
        if (routes[j].Bus.size() > 1) {
            for (int k = 0; k < routes[j].Bus.size() - 1; k++)
                bus_routes_size[routes[j].route] += coordinatesLength(routes[j].Bus[k], routes[j].Bus[k + 1]);
        }
        if (routes[j].Trolleybus.size() > 1) {
            for (int k = 0; k < routes[j].Trolleybus.size() - 1; k++)
                trolleybus_routes_size[routes[j].route] += coordinatesLength(routes[j].Trolleybus[k],
                                                                             routes[j].Trolleybus[k + 1]);
        }
    }
}
void set_size(map<string, float> &routes_size, float &path_counter, string &max_route) {
//    for (auto const &i : routes_size) {
//        if (i.second > path_counter) {
//            path_counter = i.second;
//            max_route = i.first;
//        }
//    }
        for(const auto&[a, b] : routes_size){
            if (b > path_counter){
                path_counter = b;
                max_route = a;
            }
        }
}
void max_routes(int &maximum, string &max_size, map<string, int> &locations) {
//    for (auto const i : locations) {
//        if (i.second > maximum) {
//            maximum = i.second;
//            max_size = i.first;
//        }
//    }
    for(const auto&[a, b] : locations){
        if (b > maximum){
            maximum = b;
            max_size = a;
        }
    }
}




