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

}  // namespace

