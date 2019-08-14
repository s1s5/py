/**
 * Copyright
 * @file test_zip.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 18:00:58
 */
#include "../cpput.hpp"

#include "py/builtins/base.hpp"
#include "py/builtins/zip.hpp"

namespace {

using namespace py;

TEST(py_builtins_zip, clcl) {
    std::vector<int> v0_{0, 1, 2, 3, 4};
    std::vector<double> v1_{0.0, 0.1, 0.2, 0.3, 0.4};
    const std::vector<int> &v0 = v0_;
    const std::vector<double> &v1 = v1_;
    int i = 0;
    for (auto &&[a, b] : zip(v0, v1)) {
        ASSERT_EQ(a, i);
        ASSERT_NEAR(b, 0.1 * i, 1.0e-8);
        i++;
    }
}

TEST(py_builtins_zip, rcl) {
    std::vector<double> v1_{0.0, 0.1, 0.2, 0.3, 0.4};
    const std::vector<double> &v1 = v1_;
    int i = 0;
    for (auto &&[a, b] : zip(std::vector<int>{0, 1, 2, 3, 4}, v1)) {
        ASSERT_EQ(a, i);
        ASSERT_NEAR(b, 0.1 * i, 1.0e-8);
        i++;
    }
}

TEST(py_builtins_zip, clr) {
    std::vector<int> v0_{0, 1, 2, 3, 4};
    ;
    const std::vector<int> &v0 = v0_;
    int i = 0;
    for (auto &&[a, b] : zip(v0, std::vector<double>{0.0, 0.1, 0.2, 0.3, 0.4})) {
        ASSERT_EQ(a, i);
        ASSERT_NEAR(b, 0.1 * i, 1.0e-8);
        i++;
    }
}

TEST(py_builtins_zip, rr) {
    int i = 0;
    for (auto &&[a, b] : zip(std::vector<int>{0, 1, 2, 3, 4}, std::vector<double>{0.0, 0.1, 0.2, 0.3, 0.4})) {
        ASSERT_EQ(a, i);
        ASSERT_NEAR(b, 0.1 * i, 1.0e-8);
        i++;
    }
}

TEST(py_builtins_zip, ll) {
    std::vector<int> v0{0, 1, 2, 3, 4};
    std::vector<double> v1{0.0, 0.1, 0.2, 0.3, 0.4};
    int i = 0;
    for (auto &&[a, b] : zip(v0, v1)) {
        ASSERT_EQ(a, i);
        ASSERT_NEAR(b, 0.1 * i, 1.0e-8);
        i++;
        a *= 2;
        b *= 2;
    }
    for (i = 0; i < 5; i++) {
        ASSERT_EQ(v0[i], 2 * i);
        ASSERT_NEAR(v1[i], 0.1 * 2 * i, 1.0e-8);
    }
}

TEST(py_builtins_zip, rl) {
    std::vector<double> v1{0.0, 0.1, 0.2, 0.3, 0.4};
    int i = 0;
    for (auto &&[a, b] : zip(std::vector<int>{0, 1, 2, 3, 4}, v1)) {
        ASSERT_EQ(a, i);
        ASSERT_NEAR(b, 0.1 * i, 1.0e-8);
        i++;
        a *= 2;
        b *= 2;
    }
    for (i = 0; i < 5; i++) {
        // ASSERT_EQ(v0[i], i);  // not overwrite
        ASSERT_NEAR(v1[i], 0.1 * 2 * i, 1.0e-8);
    }
}

TEST(py_builtins_zip, lr) {
    std::vector<int> v0{0, 1, 2, 3, 4};
    int i = 0;
    for (auto &&[a, b] : zip(v0, std::vector<double>{0.0, 0.1, 0.2, 0.3, 0.4})) {
        ASSERT_EQ(a, i);
        ASSERT_NEAR(b, 0.1 * i, 1.0e-8);
        i++;
        a *= 2;
        b *= 2;
    }
    for (i = 0; i < 5; i++) {
        ASSERT_EQ(v0[i], 2 * i);
        // ASSERT_NEAR(v1[i], 0.1 * i, 1.0e-8); // not overwrite
    }
}

TEST(py_builtins_zip, different_size) {
    std::vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7};
    std::vector<double> v1{0.0, 0.1, 0.2, 0.3, 0.4};
    int i = 0;
    for (auto &&[a, b] : zip(v0, v1)) {
        ASSERT_EQ(a, i);
        ASSERT_NEAR(b, 0.1 * i, 1.0e-8);
        i++;
    }
    ASSERT_EQ(i, 5);
}

TEST(py_builtins_zip, multiple_args) {
    int i = 0;
    for (auto &&[a, b, c, d] : zip(std::vector<int>{0, 1, 2, 3},
                                   std::vector<int>{1, 2, 3, 4},
                                   std::vector<int>{2, 3, 4, 5},
                                   std::vector<int>{3, 4, 5, 6})) {
        ASSERT_EQ(i + 0, a);
        ASSERT_EQ(i + 1, b);
        ASSERT_EQ(i + 2, c);
        ASSERT_EQ(i + 3, d);
        i++;
    }
    ASSERT_EQ(i, 4);
}

// TODO
// TEST(py_builtins_zip, implicit_conversion) {
//     std::vector<int> v0{0, 1, 2, 3, 4};
//     std::vector<int> v1{0, 1, 2, 3, 4};
//     std::vector<std::tuple<int, int>> v = zip(v0, v1);
// }

int sum2(py::Iterator<std::tuple<int&, int &>> iterator) {
    int sum = 0;
    for (auto &&[i, j] : iterator) {
        sum += i * j;
    }
    return sum;
}

TEST(py_builtins_zip, iterator_int) {
    std::vector<int> v0{1, 2, 3, 4};
    std::vector<int> v1{5, 6, 7, 8};
    int s = sum2(zip(v0, v1));
    ASSERT_EQ(1 * 5 + 2 * 6 + 3 * 7 + 4 * 8, s);
}

}  // namespace

