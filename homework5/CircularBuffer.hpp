#include <iostream>
#include <exception>
#include <iterator>
#include <string>
using namespace std;
//there is already min in c++ (still)
#define min(a, b) ((a < b) ? a : b)
template<class T>
class Iterator  {
    T* array;
    int start;
    int capacity;
    int curr;
public:
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Iterator() { }

    Iterator(T* array_, int start_, int capacity_, int cur_pos)
            : array(array_), start(start_), capacity(capacity_), curr(cur_pos) { }

    Iterator(const Iterator& iter)
            : array(iter.array), start(iter.start), capacity(iter.capacity), curr(iter.curr) { }

    T& operator*()
    {
        return array[(curr + start) % capacity];
    }

    T* operator->()
    {
        return &curr;
    }

    Iterator& operator++()
    {
        curr++;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator tmp(*this);
        ++tmp;
        return tmp;
    }

    Iterator& operator--()
    {
        curr--;
        return *this;
    }

    Iterator operator--(int)
    {
        Iterator tmp(*this);
        --tmp;
        return tmp;
    }

    Iterator operator-(Iterator::difference_type iter)
    {
        return Iterator(array, start, capacity, curr - iter);
    }

    Iterator operator+(Iterator::difference_type iter)
    {
        return Iterator(array, start, capacity, curr + iter);
    }

    bool operator==(const Iterator& lhs) const
    {
        return lhs.curr == curr;
    }

    bool operator!=(const Iterator& lhs) const
    {
        return lhs.curr != curr;
    }

    bool operator==(T* pointer) const
    {
        return *pointer == curr;
    }

    bool operator!=(T* pointer) const
    {
        return *pointer != curr;
    }

    bool operator>(const Iterator& lhs) const
    {
        return curr > lhs.curr;
    }

    bool operator<(const Iterator& lhs) const
    {
        return curr < lhs.curr;
    }

    bool operator>=(const Iterator& lhs) const
    {
        return curr >= lhs.curr;
    }

    bool operator<=(const Iterator& lhs) const
    {
        return curr <= lhs.curr;
    }

    Iterator& operator+=(Iterator::difference_type iter)
    {
        curr += iter;
        return *this;
    }

    Iterator& operator-=(Iterator::difference_type iter)
    {
        curr -= iter;
        return *this;
    }

    Iterator& operator=(const Iterator& lhs)
    {
        curr = lhs.curr;
        start = lhs.start;
        capacity = lhs.capacity;
        array = lhs.array;
        return *this;
    }

    friend Iterator operator+(Iterator::difference_type n, Iterator iter)
    {
        return iter + n;
    }

    friend Iterator::difference_type operator-(const Iterator& lhs, const Iterator& rhs)
    {
        return lhs.curr - rhs.curr;
    }

};



template<class T>
class CircularBuffer {
public:
    int size_;
    int capacity;
    T* array;
    int head;

    CircularBuffer(int capacity_)
    {
        capacity = capacity_;
        array = new T[capacity];
        head = 0;
        size_ = 0;
    }

    void addFirst(T value_)
    {
        if (head == 0){
            head = capacity - 1;
        }

        else{
            head--;
        }

        array[head] = value_;
        if (size_ < capacity){
            size_++;
        }

    };

    void addLast(T value_)
    {
        array[(head + size_) % capacity] = value_;
        if (size_ < capacity){
            size_++;
        }
    }

    void delFirst()
    {

        head = (head + 1) % capacity;
        if (size_ > 0){
            size_--;
        }


    }

    void delLast()
    {
        if (size_ > 0){
            size_--;
        }

    }

    T& first()
    {
        if (size_ == 0){
            throw range_error("Empty buffer");
        }
        return array[head];
    }

    T& last()
    {
        if (size_ == 0){
            throw range_error("Empty buffer");
        }
        return array[(head + size_ - 1) % capacity];
    }

    Iterator<T> begin() const
    {
        return Iterator(array, head % capacity, capacity, 0);
    }

    Iterator<T> end() const
    {
        return Iterator(array, head % capacity, capacity, size_);

    }

    //fixed more informations in exceptions
    T& operator[](int index)
    {
        if (index >= capacity){
            throw range_error("Invalid value index. Index is bigger than capacity. Capacity is " + to_string(capacity) + " | Index is " +  to_string(index + 1));
        }
        else if (index < capacity && index >= size_ ){
            throw range_error("Invalid value index. Not enough elems in the buffer, there are " + to_string(size_) + " elems in buffer");
        }
        return array[(head + index) % capacity];
    };

    T& operator[](int index) const
    {
        if (index >= capacity){
            throw range_error("Invalid value index. Index is bigger than capacity. Capacity is " + to_string(capacity) + "| Index is " +  to_string(index + 1));
        }
        else if (index < capacity && index >= size_ ){
            throw range_error("Invalid value index. Not enough elems in the buffer, there are " + to_string(size_) + " elems in buffer");
        }
        return array[(head + index) % capacity];
    };

    void changeCapacity(int capacity_)
    {
        if (capacity_ > 0) {
            int new_capacity = capacity_;
            int new_size = min(new_capacity, size_);
            T* newArray = new T[new_capacity]();
            for (int i = 0; i < new_size; i++){
                newArray[i] = array[head];
                ++head %= capacity;
            }

            delete[] array;
            array = newArray;
            head = 0;
            size_ = new_size;
            capacity = new_capacity;
        }
        else {
            throw range_error("Wrong value for capacity!");
        }
    }
};