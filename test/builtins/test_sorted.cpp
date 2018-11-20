/**
 * Copyright
 * @file test_sorted.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 18:00:45
 */
#include "../cpput.hpp"

#include "py/builtins/sorted.hpp"

namespace {

using namespace py;

TEST(py_builtins_sorted, 000) {
    std::vector<int> s{3, 1, 4, 2};
    auto l = sorted(s);
    ASSERT_EQ(l[0], 1);
    ASSERT_EQ(l[1], 2);
    ASSERT_EQ(l[2], 3);
    ASSERT_EQ(l[3], 4);
}

}  // namespace

