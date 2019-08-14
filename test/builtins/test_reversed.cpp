/**
 * Copyright
 * @file test_reversed.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2019-02-26 16:05:47
 */
#include "../cpput.hpp"

#include "py/builtins/base.hpp"
#include "py/builtins/reversed.hpp"

namespace {

using namespace py;

TEST(py_builtins_reversed, access) {
    std::vector<int> data{1, 3, 5}, new_data;
    for (auto &&i : reversed(data)) {
        new_data.push_back(i);
    }
    ASSERT_EQ(new_data.size(), 3);
    ASSERT_EQ(new_data[0], 5);
    ASSERT_EQ(new_data[1], 3);
    ASSERT_EQ(new_data[2], 1);
}

TEST(py_builtins_reversed, overwrite) {
    std::vector<int> data{1, 3, 5};
    int counter = 0;
    for (auto &&i : reversed(data)) {
        i = counter++;
    }
    ASSERT_EQ(data[0], 2);
    ASSERT_EQ(data[1], 1);
    ASSERT_EQ(data[2], 0);
}

TEST(py_builtins_range, implicit_conversion_to_vector) {
    std::vector<int> data{1, 3, 5};
    std::vector<int> l = reversed(data);
    ASSERT_EQ(3, l.size());
    ASSERT_EQ(5, l[0]);
    ASSERT_EQ(3, l[1]);
    ASSERT_EQ(1, l[2]);
}

void check(py::Iterator<int> iterator) {
    std::vector<int> l;
    for (auto &&i : iterator) {
        l.push_back(i);
    }
    ASSERT_EQ(3, l.size());
    ASSERT_EQ(5, l[0]);
    ASSERT_EQ(3, l[1]);
    ASSERT_EQ(1, l[2]);
}

TEST(py_builtins_range, implicit_conversion_to_iterator) {
    std::vector<int> data{1, 3, 5};
    check(py::reversed(data));
}


}  // namespace

