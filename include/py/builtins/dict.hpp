/**
 * Copyright 
 * @file dict.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:38:18
 */
#ifndef DICT_HPP_
#define DICT_HPP_

#include <map>
#include "./map.hpp"

namespace py {

template <class Tzip>
auto dict(const Tzip &tz) {
    using iter_type = decltype(*(std::declval<Tzip>().begin()));
    using key_type = typename std::remove_const<typename std::remove_reference<decltype(
        std::declval<iter_type>().first)>::type>::type;
    using value_type = typename std::remove_const<typename std::remove_reference<decltype(
        std::declval<iter_type>().second)>::type>::type;
    std::map<key_type, value_type> m;
    for (auto &&i : tz) {
        m.insert(std::make_pair(i.first, i.second));
    }
    return m;
}

template <class Tzip>
auto dict(Tzip &&tz) {
    using iter_type = decltype(*(std::declval<Tzip>().begin()));
    using key_type = typename std::remove_const<typename std::remove_reference<decltype(
        std::declval<iter_type>().first)>::type>::type;
    using value_type = typename std::remove_const<typename std::remove_reference<decltype(
        std::declval<iter_type>().second)>::type>::type;
    std::map<key_type, value_type> m;
    for (auto &&i : tz) {
        m.insert(std::make_pair(i.first, i.second));
    }
    return m;
}

template<class T>
auto keys(T &t) {
    return ::py::map([](auto &iter) { return iter.first; }, t);
}

template<class T>
auto values(T &t) {
    return ::py::map([](auto &iter) { return iter.second; }, t);
}

template<class T>
auto items(T &t) {
    return std::forward(t);
}

}  // namespace py

#endif  // DICT_HPP_
