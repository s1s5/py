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

TEST(py_builtins_map, debug) {
    Class x;
    const std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    int i = 0;
    for (auto &&j : py::map(x, v0)) {
        std::cout << i << " : " << j << std::endl;
        i++;
    }
    for (auto &&j : py::map(Class(), v0)) {
        std::cout << i << " : " << j << std::endl;
        i++;
    }
}

//TEST(py_builtins_map, iterator) {
//    const std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
//    auto iv = py::map([](auto e) { return e + 10; }, v0.begin(), v0.end());
//    int i = 0;
//    for (auto &&j : iv) {
//        ASSERT_EQ(i + 10, j);
//        i++;
//    }
//}
//
}  // namespace

