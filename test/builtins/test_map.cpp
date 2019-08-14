/**
 * Copyright
 * @file test_map.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 18:00:20
 */
#include "../cpput.hpp"

#include <iostream>

#include "py/builtins/map.hpp"
#include "../debug.hpp"

namespace {

int add(int a, int b) {
    return a + b;
}

TEST(py_builtins_map, rvalue_function_lvalue_reference) {
    std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    auto iv = py::map([](auto e) { return e + 10; }, v0);

    int i = 0;
    for (auto &&j : iv) {
        ASSERT_EQ(i + 10, j);
        i++;
    }

    i = 0;
    for (auto &&j : py::map([](auto &e) { return e += 20; }, v0)) {
        ASSERT_EQ(i + 20, j);
        i++;
    }

    i = 0;
    for (auto &&j : v0) {
        ASSERT_EQ(i + 20, j);
        i++;
    }
}

TEST(py_builtins_map, rvalue_function_multi_lvalue_reference) {
    std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    std::vector<int> v1{3, 4, 5, 6, 7, 8, 9, };
    std::vector<int> v2{5, 6, 7, 8, 9, };
    
    auto iv = py::map([](auto e0, auto e1, auto e2) { return e0 + e1 + e2; }, v0, v1, v2);

    int i = 0;
    for (auto &&j : iv) {
        ASSERT_EQ(3 * i + (0 + 3 + 5), j);
        i++;
    }
    ASSERT_EQ(5, i);
}

TEST(py_builtins_map, rvalue_function_rvalue_reference) {
    auto iv = py::map([](auto e) { return e + 10; }, std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, });

    int i = 0;
    for (auto &&j : iv) {
        ASSERT_EQ(i + 10, j);
        i++;
    }
}

TEST(py_builtins_map, rvalue_function_const_lvalue_reference) {
    const std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    auto iv = py::map([](auto e) { return e + 10; }, v0);
    int i = 0;
    for (auto &&j : iv) {
        ASSERT_EQ(i + 10, j);
        i++;
    }
}

TEST(py_builtins_map, multi) {
    std::vector<int> result;
    for (auto &&r : py::map(add,
                           std::vector<int>{0, 1, 2, 3},
                           std::vector<int>{4, 5, 6, 7})) {
        result.push_back(r);
    }
    ASSERT_EQ(4, result.size());
    ASSERT_EQ(4, result[0]);
    ASSERT_EQ(6, result[1]);
    ASSERT_EQ(8, result[2]);
    ASSERT_EQ(10, result[3]);
}

TEST(py_builtins_map, debug) {
    Class_counter = 0;
    Class x;
    ASSERT_EQ(1, Class_counter);
    const std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    int i = 0, s = 0;
    for (auto &&j : py::map(x, v0)) {
        // std::cout << i << " : " << j << std::endl;
        i++;
        s += j;
    }
    ASSERT_EQ(10, i);
    ASSERT_EQ(55, s);
    ASSERT_EQ(1, Class_counter);
    // for (auto &&j : py::map(Class(), v0)) {
    //     // std::cout << i << " : " << j << std::endl;
    //     i++;
    //     s += j;
    // }
    // std::cout << Class_counter << std::endl;
}

TEST(py_builtins_map, copy_count_arg_lvalue_reference) {
    Class_counter = 0;
    Class x;
    ASSERT_EQ(1, Class_counter);
    int s = 0;
    for (auto &&j : py::map([](auto i) { return i; }, x)) {
        s += j;
    }
    ASSERT_EQ(45, s);
    ASSERT_EQ(1, Class_counter);
}

TEST(py_builtins_map, copy_count_arg_const_lvalue_reference) {
    Class_counter = 0;
    Class x_;
    const Class &x = x_;
    ASSERT_EQ(1, Class_counter);
    int s = 0;
    for (auto &&j : py::map([](auto i) { return i; }, x)) {
        s += j;
    }
    ASSERT_EQ(10, s);
    ASSERT_EQ(1, Class_counter);
}

// TEST(py_builtins_map, copy_count_arg_const_xvalue_reference) {
//     Class_counter = 0;
//     int s = 0;
//     for (auto &&j : py::map([](auto i) { return i; }, Class())) {
//         s += j;
//     }
//     ASSERT_EQ(10, s);
//     ASSERT_EQ(1, Class_counter);
// }

TEST(py_builtins_map, implicit_conversion) {
    {
        std::vector<int> v0{0, 1, 2, 3, 4};
        std::vector<int> v1 = py::map([](auto e) { return e + 10; }, v0);
        ASSERT_EQ(5, v1.size());
    }
    {
        std::vector<int> v0{0, 1, 2, 3, 4};
        std::vector<double> v1 = py::map([](auto e) { return e + 10.0; }, v0);
        ASSERT_EQ(5, v1.size());
    }
    {
        std::vector<std::string> v0{"0", "1", "2", "3", "4"};
        std::vector<std::string> v1 = py::map([](auto e) { return e + "0"; }, v0);
        ASSERT_EQ(5, v1.size());
    }
}

int sum0(py::Iterator<int> iterator) {
    int sum = 0;
    for (auto &&i : iterator) {
        sum += i;
    }
    return sum;
}

int sum1(py::Iterator<const int&> iterator) {
    int sum = 0;
    for (auto &&i : iterator) {
        sum += i;
    }
    return sum;
}

TEST(py_builtins_map, iterator_int) {
    std::vector<int> v0{0, 1, 2, 3, 4};
    int s0 = sum0(py::map([](auto e) { return e + 10; }, v0));
    ASSERT_EQ(10 * 5 + 10, s0);
    int s1 = sum1(py::map([](auto e) { return e + 8; }, v0));
    ASSERT_EQ(8 * 5 + 10, s1);
}

}  // namespace

