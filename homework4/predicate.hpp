//
// Created by misha on 05.05.2021.
//

#ifndef HOMEWORK4_PREDICATE_HPP
#define HOMEWORK4_PREDICATE_HPP
#include <iostream>
#include <sstream>
#include <assert.h>
#include <vector>
#include <set>
#include <iterator>
#include <functional>


using namespace std;

template<typename T, typename P>
bool allOf(const T begin,const  T end, const P &p) {
    for (T i = begin; i != end; i++) {
        if (!p(*i)) {
            return false;
        }
    }
    return true;
};

template<typename T, typename P>
bool anyOf(const T &begin, const T &end, const P &p) {
    for (T i = begin; i < end; i++) {
        if (p(*i)) {
            return true;
        }
    }
    return false;
}

template <typename T, typename P>
bool noneOf (const T& begin, const T& end, P p) {
    for (T i = begin; i != end; ++i) {
        if (p(*i)) {
            return false;
        }
    }
    return true;
}

template<typename T, typename P>
bool oneOf(const T &begin, const T &end, const P &p) {
    int cnt = 0;
    for (T i = begin; i < end; i++) {
        if (p(*i)) {
            cnt++;
        }
    }

    if (cnt == 1) {
        return true;
    } else {
        return false;
    }
}

template<typename T, typename P = less<>>
bool isSorted(T begin, T end, P p = P()) {
    for (T i = begin; i < end - 1; i++) {
        if (!p(*i, *(i + 1))) {
            return false;
        }
    }
    return true;
}


template <typename T, typename P>
bool isPartitioned (T first, T last, P p) {
    for (; first != last; ++first) {
        if (!p(*first))
            break;
    }
    for (; first != last; ++first) {
        if (p(*first))
            return false;
    }
    return true;
}

template<typename T1, typename T2>
T1 findNot(const T1 &begin, const T1 &end, T2 value) {
    for (T1 i = begin; i < end; i++) {
        if (*i != value) {
            return i;
        }
    }
    return end;
}

template<typename T, typename F>
T findBackward(T first, T second, const F &value) {
    auto temp_value = second;
    while (first != second) {
        if (*first == value) {
            temp_value = first;
        }
        first++;
    }
    return temp_value;
}

template<typename T, typename C>
bool isPalindrome(T first, T last, C comp){
    if (first == last){
        return true;
    }
    --last;
    while (last != first){
        if(!comp(*first,*last)){
            return false;
        }
        ++first;

        if(first == last){
            break;
        }
        --last;
    }
    return true;
}


#endif //HOMEWORK4_PREDICATE_HPP
