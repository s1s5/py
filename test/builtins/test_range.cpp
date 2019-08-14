/**
 * Copyright
 * @file test_range.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 18:00:27
 */
#include "../cpput.hpp"

#include "py/builtins/base.hpp"
#include "py/builtins/range.hpp"

namespace {

using namespace py;

TEST(py_builtins_range, arg1) {
    auto v0 = range(10);
    ASSERT_EQ(len(v0), 10);
    ASSERT_EQ(v0.size(), 10);
    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(v0[i], i);
    }
}

TEST(py_builtins_range, arg2) {
    auto v0 = range(10, 20);
    ASSERT_EQ(len(v0), 10);
    ASSERT_EQ(v0.size(), 10);
    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(v0[i], i + 10);
    }
}

TEST(py_builtins_range, arg3_0) {
    auto v0 = range(10, 20, 3);
    ASSERT_EQ(len(v0), (20 - 10) / 3 + 1);
    ASSERT_EQ(v0.size(), (20 - 10) / 3 + 1);
    auto iter = v0.begin();
    for (int i = 10; i < 20; i += 3, iter++) {
        ASSERT_EQ(i, *iter);
        ASSERT_NEQ(iter, v0.end());
    }
    ASSERT_EQ(iter, v0.end());
}

TEST(py_builtins_range, arg3_1) {
    auto v0 = range(10, 25, 3);
    ASSERT_EQ(len(v0), (25 - 10) / 3);
    ASSERT_EQ(v0.size(), (25 - 10) / 3);
    auto iter = v0.begin();
    for (int i = 10; i < 25; i += 3, iter++) {
        ASSERT_EQ(i, *iter);
        ASSERT_NEQ(iter, v0.end());
    }
    ASSERT_EQ(iter, v0.end());
}

TEST(py_builtins_range, arg3_2) {
    auto v0 = range(10, 0, -3);
    ASSERT_EQ(len(v0), 10 / 3 + 1);
    ASSERT_EQ(v0.size(), len(v0));
    auto iter = v0.begin();
    for (int i = 10; i > 0; i -= 3, iter++) {
        ASSERT_EQ(i, *iter);
        ASSERT_NEQ(iter, v0.end());
    }
    ASSERT_EQ(iter, v0.end());
}

TEST(py_builtins_range, arg3_3) {
    auto v0 = range(15, 0, -3);
    ASSERT_EQ(len(v0), 15 / 3 + 1);
    ASSERT_EQ(v0.size(), len(v0));
    auto iter = v0.begin();
    for (int i = 15; i > 0; i -= 3, iter++) {
        ASSERT_EQ(i, *iter);
        ASSERT_NEQ(iter, v0.end());
    }
    ASSERT_EQ(iter, v0.end());
}

TEST(py_builtins_range, loop0) {
    int i = 0;
    for (auto &&v : range(10)) {
        ASSERT_EQ(v, i);
        i++;
    }
    ASSERT_EQ(i, 10);
}

TEST(py_builtins_range, loop1) {
    int i = 0;
    for (auto &&v : range(10, 20)) {
        ASSERT_EQ(v, i + 10);
        i++;
    }
    ASSERT_EQ(i, 10);
}

TEST(py_builtins_range, loop2) {
    int i = 0;
    for (auto &&v : range(10, 20, 3)) {
        ASSERT_EQ(v, 10 + 3 * i);
        i++;
    }
    ASSERT_EQ(i, (20 - 10 + 3 - 1) / 3);
}

TEST(py_builtins_range, loop3) {
    int i = 0;
    for (auto &&v : range(20, 10, -3)) {
        ASSERT_EQ(v, 20 - 3 * i);
        i++;
    }
    ASSERT_EQ(i, (20 - 10 + 3 - 1) / 3);
}

TEST(py_builtins_range, loop4) {
    int i = 0;
    for (auto &&v : range(20, 10, -1)) {
        ASSERT_EQ(v, 20 - i);
        i++;
    }
    ASSERT_EQ(i, 10);
}

TEST(py_builtins_range, implicit_conversion_to_vector) {
    std::vector<int> l = py::range(10);
    ASSERT_EQ(10, l.size());
    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(i, l[i]);
    }
}

int sum0(py::Iterator<int> iterator) {
    int sum = 0;
    for (auto &&i : iterator) {
        sum += i;
    }
    return sum;
}

TEST(py_builtins_range, implicit_conversion_to_iterator) {
    int s = sum0(py::range(10));
    ASSERT_EQ(45, s);
}

}  // namespace

