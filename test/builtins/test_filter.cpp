/**
 * Copyright
 * @file test_filter.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 18:00:01
 */
#include "../cpput.hpp"

#include "py/builtins/filter.hpp"

namespace {

using namespace py;

TEST(py_builtins_filter, const_vector) {
    int i = 0;
    const std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    auto v1 = filter([](auto e) { return e >= 5; }, v0);
    for (auto &&j : v1) {
        ASSERT_EQ(i + 5, j);
        // j += 8;  // <= forbidden
        i++;
    }
    ASSERT_EQ(5, i);
}

TEST(py_builtins_filter, vector) {
    int i = 0;
    std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    auto v1 = filter([](auto e) { return e >= 5; }, v0);
    for (auto &&j : v1) {
        ASSERT_EQ(i + 5, j);
        j += 8;
        i++;
    }
    ASSERT_EQ(5, i);
    for (int j = 0; j < 10; j++) {
        if (j >= 5) {
            ASSERT_EQ(j + 8, v0[j]);
        } else {
            ASSERT_EQ(j, v0[j]);
        }
    }
}

TEST(py_builtins_filter, temporal) {
    int i = 0;
    std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    auto v1 = filter([](auto e) { return e >= 5; }, std::vector<int>(v0.begin(), v0.end()));
    for (auto &&j : v1) {
        ASSERT_EQ(i + 5, j);
        i++;
    }
    ASSERT_EQ(5, i);    
}

}  // namespace

