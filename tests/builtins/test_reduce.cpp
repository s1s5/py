/**
 * Copyright
 * @file test_reduce.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 18:00:38
 */
#include "../cpput.hpp"

#include "py/builtins/reduce.hpp"

namespace {

using namespace py;

TEST(py_builtins_reduce, int) {
    const std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    auto v1 = reduce([](const auto &x, const auto &y) -> int { return x + y; }, v0);
    static_assert(std::is_same<decltype(v1), int>::value, "v1 type is unexpected!");
    ASSERT_EQ(10 * 9 / 2, v1);
}

TEST(py_builtins_reduce, int2double) {
    const std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    auto v1 = reduce([](const auto &x, const auto &y) { return x + y; }, v0, 0.1);
    static_assert(std::is_same<decltype(v1), double>::value, "v1 type is unexpected!");
    ASSERT_EQ(10 * 9 / 2 + 0.1, v1);
}

TEST(py_builtins_reduce, char) {
    auto v1 = reduce([](const auto &x, const auto &y) { return x + y; }, std::vector<char>{'a', 'b', 'c'}, std::string());
    static_assert(std::is_same<decltype(v1), std::string>::value, "v1 type is unexpected!");
    ASSERT_EQ(v1, "abc");
}

}  // namespace

