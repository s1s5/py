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

TEST(py_builtins_combined, zip_map) {
    {
        std::vector<int> v{0, 1, 2, 3};
        std::vector<uintptr_t> p{(uintptr_t)&v[0], (uintptr_t)&v[1], (uintptr_t)&v[2], (uintptr_t)&v[3]};
        int loop_counter = 0;
        for (auto &&[i0, i1] : py::zip(v, py::map([](int x) { return x + 10; }, v))) {
            ASSERT_EQ(loop_counter, i0);
            ASSERT_EQ(loop_counter + 10, i1);
            ASSERT_EQ(p[loop_counter], (uintptr_t)&i0);

            i0 += 100;
            i1 += 50;

            ASSERT_EQ(loop_counter + 100, i0);
            ASSERT_EQ(loop_counter + 10 + 50, i1);

            loop_counter += 1;
        }

        for (int i = 0; i < 4; i++) {
            ASSERT_EQ(100 + i, v[i]);
        }
    }

    {
        std::vector<int> v{0, 1, 2, 3};
        std::vector<uintptr_t> p{(uintptr_t)&v[0], (uintptr_t)&v[1], (uintptr_t)&v[2], (uintptr_t)&v[3]};
        int loop_counter = 0;
        for (auto &&[i0, i1] : py::zip(py::map([](int x) { return x + 5; }, v), v)) {
            ASSERT_EQ(loop_counter + 5, i0);
            ASSERT_EQ(loop_counter, i1);
            ASSERT_EQ(p[loop_counter], (uintptr_t)&i1);

            i0 += 100;
            i1 += 50;

            ASSERT_EQ(loop_counter + 5 + 100, i0);
            ASSERT_EQ(loop_counter + 50, i1);

            loop_counter += 1;
        }

        for (int i = 0; i < 4; i++) {
            ASSERT_EQ(50 + i, v[i]);
        }
    }

    {
        std::vector<int> v{0, 1, 2, 3};
        int loop_counter = 0;
        for (auto &&[i0, i1] : py::zip(py::map([](int x) { return x + 5; }, v), py::map([](int x) { return x + 10; }, v))) {
            ASSERT_EQ(loop_counter + 5, i0);
            ASSERT_EQ(loop_counter + 10, i1);

            i0 += 100;
            i1 += 50;

            ASSERT_EQ(loop_counter + 5 + 100, i0);
            ASSERT_EQ(loop_counter + 10 + 50, i1);

            loop_counter += 1;
        }

        for (int i = 0; i < 4; i++) {
            ASSERT_EQ(i, v[i]);
        }
    }
}
