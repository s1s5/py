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

TEST(py_builtins_filter, const_vector_2) {
    int i = 0;
    const std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    auto v1 = filter([](auto e) { return e % 3 == 0; }, v0);
    for (auto &&j : v1) {
        ASSERT_EQ(3 * i, j);
        i++;
    }
    ASSERT_EQ(4, i);
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

TEST(py_builtins_filter, implicit_conversion) {
    std::vector<int> v0{0, 1, 2, 3, 4};
    std::vector<int> v1 = filter([](auto e) { return e >= 3; }, v0);
    ASSERT_EQ(2, v1.size());
    ASSERT_EQ(3, v1[0]);
    v1[0] = 8;
    ASSERT_EQ(3, v0[3]);

    // TODO: impossible ?
    // std::vector<int&> v2 = filter([](auto e) { return e >= 3; }, v0);
    // ASSERT_EQ(2, v2.size());
    // ASSERT_EQ(3, v2[0]);
    // v2[0] = 8;
    // ASSERT_EQ(8, v0[3]);
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

TEST(py_builtins_filter, iterator_int) {
    std::vector<int> v0{0, 1, 2, 3, 4};
    int s0 = sum0(py::filter([](auto e) { return e > 2; }, v0));
    ASSERT_EQ(3 + 4, s0);

    int s1 = sum1(py::filter([](auto e) { return e > 2; }, v0));
    ASSERT_EQ(3 + 4, s1);
}


}  // namespace

