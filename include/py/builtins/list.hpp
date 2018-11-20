/**
 * Copyright
 * @file list.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:36:18
 */
#ifndef LIST_HPP_
#define LIST_HPP_

#include <vector>

namespace py {

template <class Tarray>
std::vector<typename std::remove_reference<decltype((*((std::declval<Tarray>().begin()))))>::type> list(const Tarray &iterable) {
    using el = typename std::remove_reference<decltype((*((std::declval<Tarray>().begin()))))>::type;
    std::vector<el> dst;
    for (auto &&iter : iterable) {
        dst.emplace_back(iter);
    }
    return dst;
}

template <class Tarray>
std::vector<typename std::remove_reference<decltype((*((std::declval<Tarray>().begin()))))>::type> list(Tarray &&iterable) {
    using el = typename std::remove_reference<decltype((*((std::declval<Tarray>().begin()))))>::type;
    std::vector<el> dst;
    for (auto &&iter : iterable) {
        dst.emplace_back(iter);
    }
    return dst;
}

template <class Iterator>
std::vector<typename std::remove_reference<typename std::remove_cv<decltype(*(std::declval<Iterator>()))>::type>::type> list(Iterator begin, Iterator end) {
    return std::vector<typename std::remove_reference<typename std::remove_cv<decltype(*(std::declval<Iterator>()))>::type>::type>(begin, end);
}

}  // namespace py

#endif  // LIST_HPP_
