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

template<typename Iterator, typename Predicate>
bool allOf(const Iterator begin, const  Iterator end, const Predicate &p) {
    for (Iterator i = begin; i != end; i++) {
        if (!p(*i)) {
            return false;
        }
    }
    return true;
};

template<typename Iterator, typename Predicate>
bool anyOf(const Iterator &begin, const Iterator &end, const Predicate &p) {
    for (Iterator i = begin; i < end; i++) {
        if (p(*i)) {
            return true;
        }
    }
    return false;
}

template <typename Iterator, typename Predicate>
bool noneOf (const Iterator& begin, const Iterator& end, Predicate p) {
    for (Iterator i = begin; i != end; ++i) {
        if (p(*i)) {
            return false;
        }
    }
    return true;
}

template<typename Iterator, typename Predicate>
bool oneOf(const Iterator &begin, const Iterator &end, const Predicate &p) {
    int cnt = 0;
    for (Iterator i = begin; i < end; i++) {
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

template<typename Iterator, typename Predicate = less<>>
bool isSorted(Iterator begin, Iterator end, Predicate p = Predicate()) {
    for (Iterator i = begin; i < end - 1; i++) {
        if (!p(*i, *(i + 1))) {
            return false;
        }
    }
    return true;
}


template <typename Iterator, typename Predicate>
bool isPartitioned (Iterator first, Iterator last, Predicate p) {
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

template<typename Iterator, typename T>
Iterator findNot(const Iterator &begin, const Iterator &end, T value) {
    for (Iterator i = begin; i < end; i++) {
        if (*i != value) {
            return i;
        }
    }
    return end;
}

template<typename Iterator, typename F>
Iterator findBackward(Iterator first, Iterator second, const F &value) {
    auto temp_value = second;
    while (first != second) {
        if (*first == value) {
            temp_value = first;
        }
        first++;
    }
    return temp_value;
}

template<typename Iterator, typename Compare>
bool isPalindrome(Iterator first, Iterator last, Compare comp){
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
