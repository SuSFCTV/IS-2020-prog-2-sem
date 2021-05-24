#include <iostream>
#include <exception>
#include <iterator>

using namespace std;
#define min(a, b) ((a < b) ? a : b)

template<class T>
class Iterator : iterator<random_access_iterator_tag, T> {
    T *curr;
public:
    using typename iterator<random_access_iterator_tag, T>::iterator_category;
    using typename iterator<random_access_iterator_tag, T>::value_type;
    using typename iterator<random_access_iterator_tag, T>::difference_type;
    using typename iterator<random_access_iterator_tag, T>::pointer;
    using typename iterator<random_access_iterator_tag, T>::reference;

    Iterator() {}

    Iterator(T *cur_pos)
            : curr(cur_pos) {}

    Iterator(const Iterator &iter)
            : curr(iter.curr) {}

    T &operator*() {
        return *curr;
    }

    T *operator->() {
        return curr;
    }

    Iterator &operator++() {
        curr++;
        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp(*this);
        ++tmp;
        return tmp;
    }

    Iterator &operator--() {
        curr--;
        return *this;
    }

    Iterator operator--(int) {
        Iterator tmp(*this);
        --tmp;
        return tmp;
    }

    Iterator operator-(difference_type iter) {
        return Iterator(curr - iter);
    }

    Iterator operator+(difference_type iter) {
        return Iterator(curr + iter);
    }

    bool operator==(const Iterator &lhs) const {
        return lhs.curr == curr;
    }

    bool operator==(T *pointer) const {
        return pointer == curr;
    }

    bool operator!=(const Iterator &lhs) const {
        return lhs.curr != curr;
    }

    bool operator!=(T *pointer) const {
        return pointer != curr;
    }

    bool operator>(const Iterator &lhs) const {
        return curr > lhs.curr;
    }

    bool operator<(const Iterator &lhs) const {
        return curr < lhs.curr;
    }

    bool operator>=(const Iterator &lhs) const {
        return curr >= lhs.curr;
    }

    bool operator<=(const Iterator &lhs) const {
        return curr <= lhs.curr;
    }

    bool operator>(T *pointer) const {
        return curr > pointer;
    }

    bool operator<(T *pointer) const {
        return curr < pointer;
    }

    bool operator>=(T *pointer) const {
        return curr >= pointer;
    }

    bool operator<=(T *pointer) const {
        return curr <= pointer;
    }

    Iterator &operator+=(difference_type iter) {
        curr += iter;
        return *this;
    }

    Iterator &operator-=(difference_type iter) {
        curr -= iter;
        return *this;
    }

    Iterator &operator=(const Iterator &lhs) {
        curr = lhs.curr;
        return *this;
    }

    Iterator &operator=(Iterator *pointer) {
        curr = pointer;
        return *this;
    }

    friend Iterator operator+(Iterator::difference_type n, Iterator iter) {
        return iter + n;
    }

    friend Iterator::difference_type operator-(const Iterator &lhs, const Iterator &rhs) {
        return lhs.curr - rhs.curr;
    }

};


template<class T>
class CircularBuffer {
    unsigned size;
    unsigned capacity;
    T *array;
    Iterator<T> begin_;
    Iterator<T> end_;
public:
    CircularBuffer(unsigned size_) {
        capacity = size_;
        size = 0;
        array = new T[capacity];

    }

    Iterator<T> begin() const {
        return Iterator(array);
    }

    Iterator<T> end() const {
        return Iterator(array + size);
    }

    void addFirst(T data_) {
        if (capacity > 0) {
            if (size < capacity) {
                if (size == 0) {
                    array[size] = data_;
                    size++;

                } else {
                    begin_ = begin();
                    end_ = end() - 1;
                    for (Iterator<T> iter = end_; iter >= begin_; --iter) {
                        *(iter + 1) = *iter;

                    }

                    array[0] = data_;
                    size++;

                }
            } else {
                size = capacity - 1;
                begin_ = begin();
                end_ = end();
                for (Iterator<T> iter = end_; iter >= begin_; --iter) {
                    *(iter + 1) = *iter;

                }

                array[0] = data_;
                size++;

            }

        } else {
            throw range_error("Negative/0 capacity");

        }
    }

    void delFirst() {
        if (size > 0) {
            begin_ = begin();
            end_ = end();
            for (Iterator<T> iter = begin_ + 1; iter <= end_; ++iter) {
                *(iter - 1) = *iter;
            }
            size--;

        } else {
            throw range_error("Empty buffer");

        }
    }

    void addLast(T data_) {
        if (capacity > 0) {
            if (size < capacity) {
                if (size == 0) {
                    array[size] = data_;
                    size++;

                } else {
                    array[size] = data_;
                    size++;

                }
            } else {
                size = capacity - 1;
                begin_ = begin();
                end_ = end();
                for (Iterator<T> iter = begin_ + 1; iter <= end_; ++iter) {
                    *(iter - 1) = *iter;

                }
                array[size] = data_;
                size++;

            }
        } else {
            throw range_error("Negative/0 capacity");

        }
    }

    void delLast() {
        if (size > 0) {
            size--;

        } else {
            throw range_error("Empty buffer");

        }
    }

    T &last() {
        if (size == 0) {
            throw range_error("Empty buffer");

        } else {
            return *(end() - 1);
        }

    }

    T &first() {
        if (size == 0) {
            throw range_error("Empty buffer");

        } else {
            return *begin();
        }
    }

    T &at(unsigned index) {
        if (size == 0) {
            throw range_error("Empty buffer");

        } else if (index >= size) {
            throw range_error("Invalid index value");

        } else {
            return *(array + index);
        }

    }

    T operator[](unsigned index) const {
        if (size == 0) {
            throw range_error("Empty buffer");

        } else if (index >= size) {
            throw range_error("Invalid index value");

        } else {
            return *(array + index);
        }
    }

    T &operator[](unsigned index) {
        if (size == 0) {
            throw range_error("Empty buffer");

        } else if (index >= size) {
            throw range_error("Invalid index value");

        } else {
            return *(array + index);
        }
    }

    void changeCapacity(unsigned size_) {
        if (size_ > 0) {
            T *newArray = new T[size_]();
            int new_size = min(size, size_);
            for (int i = 0; i < new_size; i++) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
            size = new_size;
            capacity = size_;
        } else {
            throw range_error("Wrong value for capacity!");
        }
    }
};