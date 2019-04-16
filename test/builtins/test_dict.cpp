/**
 * Copyright
 * @file test_dict.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 17:59:50
 */
#include "../cpput.hpp"

#include "py/builtins/dict.hpp"

namespace {

TEST(py_builtins_dict, 000) {
    std::vector<std::pair<int, std::string>> src{{1, "1"}, {2, "2"}};
    auto dst = py::dict(src);
    ASSERT_EQ(dst.find(1)->second, "1");
    ASSERT_EQ(dst.find(2)->second, "2");
    ASSERT_EQ(dst.find(0), dst.end());
}

TEST(py_builtins_dict, keys) {
    std::map<int, int> m = {{1, 3}, {4, 8}};
    std::vector<int> ans = {1, 4};
    int counter = 0;
    for (auto &&i : py::keys(m)) {
        ASSERT_EQ(ans[counter], i);
        counter++;
    }
    {
        const std::map<int, int> &cm = m;
        counter = 0;
        for (auto &&i : py::keys(cm)) {
            ASSERT_EQ(ans[counter], i);
            counter++;
        }
    }
}

TEST(py_builtins_dict, values) {
    std::map<int, int> m = {{1, 3}, {4, 8}};
    std::vector<int> ans = {3, 8};
    int counter = 0;
    for (auto &&i : py::values(m)) {
        ASSERT_EQ(ans[counter], i);
        counter++;
    }
    {
        const std::map<int, int> &cm = m;
        counter = 0;
        for (auto &&i : py::values(cm)) {
            ASSERT_EQ(ans[counter], i);
            counter++;
        }
    }
}

}  // namespace

