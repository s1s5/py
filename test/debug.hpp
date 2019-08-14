/**
 * Copyright
 * @file debug.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2019-06-19 10:45:26
 */
#ifndef PY_DEBUG_HPP_
#define PY_DEBUG_HPP_

#include <iostream>

struct CustomIterator {
    CustomIterator(int c) : counter(c) {}
    CustomIterator &operator++() {
        counter++;
        return *this;
    }
    auto operator *()  const { return counter; }
    bool operator == (const CustomIterator &rhs) const { return counter == rhs.counter; }
    bool operator != (const CustomIterator &rhs) const { return counter != rhs.counter; }
    int counter{0};
};

static int Class_counter = 0;

class Class {
 public:
    Class() : my_id(Class_counter++) {
        std::cout << "Class(" << my_id << ") construted" << std::endl;
    }

    ~Class() {
        std::cout << "Class(" << my_id << ") destrcuted" << std::endl;
    }

    Class(const Class &x) : my_id(Class_counter++) {
        std::cout << "Class(" << my_id << ") copy constructed from (" << x.my_id << ")" << std::endl;
    }

    Class(Class && x) : my_id(Class_counter++) {
        std::cout << "Class(" << my_id << ") move constructed from (" << x.my_id << ")" << std::endl;
    }

    Class& operator=(const Class& x) {
        std::cout << "Class(" << my_id << ") copy assign from (" << x.my_id << ")" << std::endl;
        return *this;
    }
    
    Class& operator=(Class&& x) {
        std::cout << "Class(" << my_id << ") move assign from (" << x.my_id << ")" << std::endl;
        return *this;
    }

    int operator() (int value) {
        return value + 1;
    }

    auto begin() { return CustomIterator(0); }
    auto end() { return CustomIterator(10); }

    auto begin() const { return CustomIterator(0); }
    auto end() const { return CustomIterator(5); }

    int my_id;
};


#endif  // PY_DEBUG_HPP_
