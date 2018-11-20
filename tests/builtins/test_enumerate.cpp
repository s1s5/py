/**
 * Copyright
 * @file test_enumerate.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:53:54
 */
#include "../cpput.hpp"

#include "py/builtins/enumerate.hpp"

namespace {

using namespace py;

TEST(py_builtins_enumerate, read) {
    std::vector<int> values{3, 6, 8};
    int ref_index = 0;
    for (auto &&[index, value] : py::enumerate(values)) {
        ASSERT_EQ(index, ref_index);
        ASSERT_EQ(value, values[ref_index]);
        ref_index++;
    }
    ASSERT_EQ(ref_index, values.size());
}

}  // namespace
