/**
 * Copyright
 * @file filter.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:40:05
 */
#ifndef FILTER_HPP_
#define FILTER_HPP_

#include "base.hpp"

namespace py {

template <class TFunc, class IteratorType>
class ifilter_iterator
    : public std::iterator<std::forward_iterator_tag,
                           typename std::remove_reference<decltype(*(std::declval<IteratorType>()))>::type> {
    using element_type = typename std::remove_reference<decltype(*(std::declval<IteratorType>()))>::type;

 public:
    ifilter_iterator(const TFunc &func_, IteratorType iter_, IteratorType end_)
        : func(func_), _iter(iter_), _end(end_) {
        _search_next();
    }
    // ifilter_iterator operator++(int) {
    //     ifilter_iterator tmp(func, _iter, _end);
    //     if (_iter != _end) {
    //         ++_iter;
    //     }
    //     _search_next();
    //     return tmp;
    // }
    ifilter_iterator &operator++() {
        if (_iter != _end) {
            ++_iter;
        }
        _search_next();
        return *this;
    }
    element_type &operator*() const { return *_iter; }
    element_type *operator->() const { return &(*_iter); }
    bool operator==(const ifilter_iterator &rhs) const { return _iter == rhs._iter; }
    bool operator!=(const ifilter_iterator &rhs) const { return _iter != rhs._iter; }

 private:
    void _search_next() {
        while (_iter != _end and (not func(*_iter))) {
            ++_iter;
        }
    }

 private:
    const TFunc &func;
    IteratorType _iter, _end;
};

template <class TFunc, class Tarray>
class ifilter_lvalue {
 public:
    using array_type = typename std::remove_const<typename std::remove_reference<Tarray>::type>::type;
    using array_iterator_type = decltype(std::declval<Tarray>().begin());
    // using element_type = typename std::remove_reference<decltype(*(std::declval<array_iterator_type>()))>::type;
 public:
    ifilter_lvalue(TFunc func_, Tarray &ar) : func(func_), array(ar) {}
    ifilter_iterator<TFunc, array_iterator_type> begin() {
        return ifilter_iterator<TFunc, array_iterator_type>(func, array.begin(), array.end());
    }
    ifilter_iterator<TFunc, array_iterator_type> end() {
        return ifilter_iterator<TFunc, array_iterator_type>(func, array.end(), array.end());
    }

    template<typename T>
    operator std::vector<T> () {
        return std::vector<T>{begin(), end()};
    }

 public:
    TFunc func;
    Tarray &array;
};

template <class TFunc, class Tarray>
class ifilter_rvalue {
 public:
    using array_type = typename std::remove_const<typename std::remove_reference<Tarray>::type>::type;
    using array_iterator_type = decltype(std::declval<Tarray>().begin());
    // using element_type = typename std::remove_reference<decltype(*(std::declval<array_iterator_type>()))>::type;
 public:
    ifilter_rvalue(TFunc func_, Tarray &&ar) : func(func_), array(ar) {}
    ifilter_iterator<TFunc, array_iterator_type> begin() {
        return ifilter_iterator<TFunc, array_iterator_type>(func, array.begin(), array.end());
    }
    ifilter_iterator<TFunc, array_iterator_type> end() {
        return ifilter_iterator<TFunc, array_iterator_type>(func, array.end(), array.end());
    }

    template<typename T>
    operator std::vector<T> () {
        return std::vector<T>{begin(), end()};
    }

 public:
    TFunc func;
    Tarray array;
};

template <class TFunc, class Tarray>
ifilter_lvalue<TFunc, Tarray> filter(TFunc func_, Tarray &ar) {  // NOLINT
    return ifilter_lvalue<TFunc, Tarray>(func_, ar);
}

template <class TFunc, class Tarray>
ifilter_rvalue<TFunc, Tarray> filter(TFunc func_, Tarray &&ar) {
    return ifilter_rvalue<TFunc, Tarray>(func_, std::move(ar));
}

// template <class TFunc, class IteratorType>
// Iterable<ifilter_iterator<TFunc, IteratorType>> filter(const TFunc &func_, IteratorType begin_, IteratorType end_) {
//     return Iterable<ifilter_iterator<TFunc, IteratorType>>(ifilter_iterator<TFunc, IteratorType>(func_, begin_, end_),
//                                                            ifilter_iterator<TFunc, IteratorType>(func_, end_, end_));
// }

}  // namespace py

#endif  // FILTER_HPP_
