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

namespace py {

template <class Tzip>
std::map<typename std::remove_const<typename std::remove_reference<
             decltype(std::declval<decltype(*(std::declval<Tzip>().begin()))>().first)>::type>::type,
         typename std::remove_const<typename std::remove_reference<
             decltype(std::declval<decltype(*(std::declval<Tzip>().begin()))>().second)>::type>::type>
dict(const Tzip &tz) {
    using key_type = typename std::remove_const<typename std::remove_reference<decltype(
        std::declval<decltype(*(std::declval<Tzip>().begin()))>().first)>::type>::type;
    using value_type = typename std::remove_const<typename std::remove_reference<decltype(
        std::declval<decltype(*(std::declval<Tzip>().begin()))>().second)>::type>::type;
    std::map<key_type, value_type> m;
    for (auto &&i : tz) {
        m.insert(std::make_pair(i.first, i.second));
    }
    return m;
}

template <class Tzip>
std::map<typename std::remove_const<typename std::remove_reference<
             decltype(std::declval<decltype(*(std::declval<Tzip>().begin()))>().first)>::type>::type,
         typename std::remove_const<typename std::remove_reference<
             decltype(std::declval<decltype(*(std::declval<Tzip>().begin()))>().second)>::type>::type>
dict(Tzip &&tz) {
    using key_type = typename std::remove_const<typename std::remove_reference<decltype(
        std::declval<decltype(*(std::declval<Tzip>().begin()))>().first)>::type>::type;
    using value_type = typename std::remove_const<typename std::remove_reference<decltype(
        std::declval<decltype(*(std::declval<Tzip>().begin()))>().second)>::type>::type;
    std::map<key_type, value_type> m;
    for (auto &&i : tz) {
        m.insert(std::make_pair(i.first, i.second));
    }
    return m;
}


}  // namespace py

#endif  // DICT_HPP_
