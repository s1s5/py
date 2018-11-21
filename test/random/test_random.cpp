/**
 * Copyright
 * @file test_random.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-21 09:57:29
 */

#include "../cpput.hpp"

#include "py/random/random.hpp"

namespace {

using namespace py;

TEST(py_random, random_seed) {
    py::random::seed(0);
    double v0 = py::random::random();
    py::random::seed(0);
    double v1 = py::random::random();
    ASSERT_NEAR(v0, v1, 1.0e-16);
}

TEST(py_random, random) {
    std::mt19937 mt(0);
    double v = py::random::random(mt);
    ASSERT_TRUE(v >= 0.0);
    ASSERT_TRUE(v < 1.0);
}

TEST(py_random, uniform) {
    std::mt19937 mt(0);
    double v = py::random::uniform(mt, -1, 1);
    ASSERT_TRUE(v >= -1.0);
    ASSERT_TRUE(v <= 1.0);
}

TEST(py_random, gauss) {
    std::mt19937 mt(0);
    py::random::gauss(mt, 0, 1.0);
}

TEST(py_random, randint) {
    std::mt19937 mt(0);
    int v = py::random::randint(mt, 0, 100);
    ASSERT_TRUE(v >= 0);
    ASSERT_TRUE(v <= 100);
}

TEST(py_random, choice) {
    std::mt19937 mt(0);
    std::vector<int> values{1, 2, 3, 4, 5};
    int v = py::random::choice(mt, values);
    ASSERT_TRUE(v > 0);
    ASSERT_TRUE(v < 6);
}


}  // namespace

