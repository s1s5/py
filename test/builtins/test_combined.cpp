/**
 * Copyright
 * @file test_combined.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2019-04-16 13:40:50
 */
#include "../cpput.hpp"

#include "py/builtins/builtins.hpp"

TEST(py_builtins_combined, list_keys) {
    std::map<int, int> m = {{1, 3}, {4, 8}};
    std::vector<int> ans = {1, 4};
    int counter = 0;
    for (auto &&i : py::list(py::keys(m))) {
        ASSERT_EQ(ans[counter], i);
        counter++;
    }
}

TEST(py_builtins_combined, sorted_keys) {
    std::map<int, int> m = {{1, 3}, {4, 8}, {2, 4}};
    std::vector<int> ans = {1, 2, 4};
    int counter = 0;
    for (auto &&i : py::sorted(py::keys(m))) {
        ASSERT_EQ(ans[counter], i);
        counter++;
    }
}
