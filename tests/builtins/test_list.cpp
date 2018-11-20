/**
 * Copyright
 * @file test_list.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 18:00:11
 */
#include "../cpput.hpp"

#include "py/builtins/list.hpp"

namespace {

using namespace py;

TEST(py_builtins_list, 000) {
    std::vector<int> src{3, 2, 1, 0};
    auto dst = list(src);
    ASSERT_EQ(dst.size(), src.size());
    for (int i = 0; i < src.size(); i++) {
        ASSERT_EQ(dst[i], src[i]);
    }
}

}  // namespace

