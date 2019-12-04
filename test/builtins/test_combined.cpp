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
    std::vector<int> v0{1, 2, 3, 4};
    // std::vector<int> v0{1,};
    // for (auto &&i : py::map([](int x) { return x + 10; }, v0)) {
    //     std::cout << i << std::endl;
    // }
    // {
    //     int x = 8;
    //     auto t = std::forward_as_tuple(x, x + 8);
    //     std::cout << std::get<0>(t) << " : " << std::get<1>(t) << std::endl;
    // }
    // {
    //     auto z = py::zip(v0, py::map([](int x) { return x + 10; }, v0));
    //     auto iter = z.begin();
    //     auto &&[i0, i1] = *iter;
    //     std::cout << "z : " << i0 << ", " << i1 << std::endl;    
    // }
    std::cout << "ptr : " << (uint64_t)&v0[0] << std::endl;
    // for (auto &&[i0, i1] : py::zip(v0, py::map([](int x) { return x + 10; }, v0))) {
    for (auto &&[i0, i1] : py::zip(v0, py::map([](int x) { return x + 10; }, v0))) {
        std::cout << "result : " << i0 << ", " << i1 << std::endl;
        std::cout << "i0 ptr = " << (uint64_t)&i0 << std::endl;
        i0 += 100;
    }
    std::cout << "CHECK ref " << v0[0] << std::endl;
    for (auto &&[i0, i1] : py::zip(py::map([](int x) { return x + 5; }, v0), v0)) {
        std::cout << "result : " << i0 << ", " << i1 << std::endl;
        std::cout << "i1 ptr = " << (uint64_t)&i1 << std::endl;
    }
    for (auto &&[i0, i1] : py::zip(py::map([](int x) { return x + 5; }, v0), py::map([](int x) { return x + 10; }, v0))) {
        std::cout << "result : " << i0 << ", " << i1 << std::endl;
    }
}
