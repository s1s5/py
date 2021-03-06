/**
 * Copyright
 * @file 
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:37:38
 */
#ifndef SORTED_HPP_
#define SORTED_HPP_

#include <algorithm>
#include "list.hpp"

namespace py {

template <class Tarray>
auto sorted(const Tarray &iterable) {
    using el = typename std::remove_cv<typename std::remove_reference<decltype(*((std::declval<Tarray>().begin())))>::type>::type;
    std::vector<el> dst = list(iterable);
    std::sort(dst.begin(), dst.end());
    return dst;
}

template <class Tarray>
auto sorted(Tarray &&iterable) {
    using el = typename std::remove_cv<typename std::remove_reference<decltype((*((std::declval<Tarray>().begin()))))>::type>::type;
    std::vector<el> dst = list(iterable);
    std::sort(dst.begin(), dst.end());
    return dst;
}

}  // namespace py

#endif  // SORTED_HPP_
