/**
 * Copyright
 * @file test_base.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 17:59:27
 */
#include "../cpput.hpp"

#include "py/builtins/base.hpp"

namespace {

using namespace py;

TEST(py_builtins_base_in, 000) {
    std::vector<int> v{0, 1, 2, 3};
    ASSERT_TRUE(py::in(0, v));
    ASSERT_FALSE(py::in(4, v));
}

}  // namespace
