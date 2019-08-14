/**
 * Copyright
 * @file reversed.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2019-02-26 16:04:22
 */
#ifndef REVERSED_HPP_
#define REVERSED_HPP_

#include <vector>
#include <iterator>

namespace py {

template <typename T>
struct reversion_wrapper {
    // using IterType = decltype(std::declval<T>().rbegin());
    // using ElementType = decltype(*std::declval<IterType>());
    // using RRElementType = typename std::remove_reference<ElementType>::type;

    T& iterable;

    template<typename X>
    operator std::vector<X> () {
        return std::vector<X>{begin(), end()};
    }

    auto begin() { return std::rbegin(iterable); }
    auto end() { return std::rend(iterable); }
};

// template <typename T>
// auto begin(reversion_wrapper<T> w) {
//     return std::rbegin(w.iterable);
// }

// template <typename T>
// auto end(reversion_wrapper<T> w) {
//     return std::rend(w.iterable);
// }

template <typename T>
reversion_wrapper<T> reversed(T&& iterable) {
    return {iterable};
}

}  // namespace py

#endif  // REVERSED_HPP_
