/**
 * Copyright
 * @file reversed.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2019-02-26 16:04:22
 */
#ifndef REVERSED_HPP_
#define REVERSED_HPP_

#include <iterator>

namespace py {

template <typename T>
struct reversion_wrapper {
    T& iterable;
};

template <typename T>
auto begin(reversion_wrapper<T> w) {
    return std::rbegin(w.iterable);
}

template <typename T>
auto end(reversion_wrapper<T> w) {
    return std::rend(w.iterable);
}

template <typename T>
reversion_wrapper<T> reversed(T&& iterable) {
    return {iterable};
}

}  // namespace py

#endif  // REVERSED_HPP_
