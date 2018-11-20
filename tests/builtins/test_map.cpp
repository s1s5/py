/**
 * Copyright
 * @file test_map.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 18:00:20
 */
#include "../cpput.hpp"

#include "py/builtins/map.hpp"

namespace {

TEST(py_builtins_map, temporal) {
    const std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    auto iv = py::map([](auto e) { return e + 10; }, std::vector<int>(v0.begin(), v0.end()));
    int i = 0;
    for (auto &&j : iv) {
        ASSERT_EQ(i + 10, j);
        i++;
    }
}

TEST(py_builtins_map, const_vector) {
    const std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    auto iv = py::map([](auto e) { return e + 10; }, v0);
    int i = 0;
    for (auto &&j : iv) {
        ASSERT_EQ(i + 10, j);
        i++;
    }
}

TEST(py_builtins_map, iterator) {
    const std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    auto iv = py::map([](auto e) { return e + 10; }, v0.begin(), v0.end());
    int i = 0;
    for (auto &&j : iv) {
        ASSERT_EQ(i + 10, j);
        i++;
    }
}

}  // namespace

