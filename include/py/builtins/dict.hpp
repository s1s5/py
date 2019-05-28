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

template<typename Iter>
class keys_iterator {
 public:
    using element_type = decltype(std::declval<Iter>()->first);
 public:
    keys_iterator(Iter iter_) : iter(iter_) {}
    keys_iterator &operator++() {
        ++iter;
        return *this;
    }
    element_type &operator*() const { return iter->first; }
    bool operator==(const keys_iterator &rhs) const { return iter == rhs.iter; }
    bool operator!=(const keys_iterator &rhs) const { return iter != rhs.iter; }

 private:
    Iter iter;
};

template<class T>
class keys_list {
 public:
    using Iter = decltype(std::declval<T>().begin());

 public:
    keys_list(T &t_) : t(t_) {
    }
    auto begin() const {
        return keys_iterator<Iter>(t.begin());
    }
    auto end() const {
        return keys_iterator<Iter>(t.end());
    }
    auto cbegin() const { return begin(); }
    auto cend() const { return end(); }    
 private:
    T &t;
};

template<class T>
auto keys(T &t) {
    return keys_list<T>(t);
}

template<typename Iter>
class values_iterator {
 public:
    using element_type = decltype(std::declval<Iter>()->second);
 public:
    values_iterator(Iter iter_) : iter(iter_) {}
    values_iterator &operator++() {
        ++iter;
        return *this;
    }
    // typename std::enable_if<not std::is_const<element_type>::value, element_type>::type &operator*() { return iter->second; }
    const element_type &operator*() const { return iter->second; }
    bool operator==(const values_iterator &rhs) const { return iter == rhs.iter; }
    bool operator!=(const values_iterator &rhs) const { return iter != rhs.iter; }

 private:
    Iter iter;
};

template<class T>
class values_list {
 public:
    using Iter = decltype(std::declval<T>().begin());

 public:
    values_list(T &t_) : t(t_) {
    }
    auto begin() const {
        return values_iterator<Iter>(t.begin());
    }
    auto end() const {
        return values_iterator<Iter>(t.end());
    }
    auto cbegin() const { return begin(); }
    auto cend() const { return end(); }    
 private:
    T &t;
};

template<class T>
auto values(T &t) {
    return values_list<T>(t);
}

}  // namespace py

#endif  // DICT_HPP_
