/**
 * Copyright
 * @file map.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:39:05
 */
#ifndef MAP_HPP_
#define MAP_HPP_

#include "base.hpp"

namespace py {

template <class TFunc, class array_iterator_type>
class imap_iterator : public std::iterator<std::input_iterator_tag,
                                           decltype(std::declval<TFunc>()(*(std::declval<array_iterator_type>())))> {
    using element_type = decltype(std::declval<TFunc>()(*(std::declval<array_iterator_type>())));

 public:
    imap_iterator(const TFunc &func_, array_iterator_type iter_) : func(&func_), iter(iter_) {}
    // imap_iterator(const imap_iterator &i) : func(i.func), iter(i.iter) {}
    // imap_iterator &operator = (const imap_iterator &i) { iter = i.iter; }
    imap_iterator operator++(int) {
        imap_iterator tmp(*func, iter);
        ++iter;
        return tmp;
    }
    imap_iterator &operator++() {
        ++iter;
        return *this;
    }
    element_type operator*() const { return (*func)(*iter); }
    element_type operator->() const { return (*func)(*iter); }
    bool operator==(const imap_iterator &rhs) const { return iter == rhs.iter; }
    bool operator!=(const imap_iterator &rhs) const { return iter != rhs.iter; }

 private:
    const TFunc *func;
    array_iterator_type iter;
};

template <class TFunc, class Tarray>
class imap_lvalue {
 public:
    using array_type = typename std::remove_const<typename std::remove_reference<Tarray>::type>::type;
    using array_iterator_type = decltype(std::declval<const Tarray>().begin());

 public:
    imap_lvalue(TFunc func_, const Tarray &ar) : func(func_), array(ar) {}
    imap_iterator<TFunc, array_iterator_type> begin() const {
        return imap_iterator<TFunc, array_iterator_type>(func, array.begin());
    }
    imap_iterator<TFunc, array_iterator_type> end() const {
        return imap_iterator<TFunc, array_iterator_type>(func, array.end());
    }
    imap_iterator<TFunc, array_iterator_type> cbegin() const { return begin(); }
    imap_iterator<TFunc, array_iterator_type> cend() const { return end(); }

 public:
    TFunc func;
    const Tarray &array;
};

template <class TFunc, class Tarray>
class imap_rvalue {
 public:
    using array_type = typename std::remove_const<typename std::remove_reference<Tarray>::type>::type;
    using array_iterator_type = decltype(std::declval<const Tarray>().begin());

 public:
    imap_rvalue(TFunc func_, const Tarray &&ar) : func(func_), array(ar) {}
    imap_iterator<TFunc, array_iterator_type> begin() const {
        return imap_iterator<TFunc, array_iterator_type>(func, array.begin());
    }
    imap_iterator<TFunc, array_iterator_type> end() const {
        return imap_iterator<TFunc, array_iterator_type>(func, array.end());
    }
    imap_iterator<TFunc, array_iterator_type> cbegin() const { return begin(); }
    imap_iterator<TFunc, array_iterator_type> cend() const { return end(); }

 public:
    TFunc func;
    array_type array;
};

template <class TFunc, class Tarray>
imap_lvalue<TFunc, Tarray> map(TFunc func_, const Tarray &ar) {
    return imap_lvalue<TFunc, Tarray>(func_, ar);
}
template <class TFunc, class Tarray>
imap_lvalue<TFunc, Tarray> map(TFunc func_, Tarray &ar) {  // NOLINT
    return imap_lvalue<TFunc, Tarray>(func_, ar);
}
template <class TFunc, class Tarray>
imap_rvalue<TFunc, Tarray> map(TFunc func_, Tarray &&ar) {
    return imap_rvalue<TFunc, Tarray>(func_, std::move(ar));
}
template <class TFunc, class IteratorType>
Iterable<imap_iterator<TFunc, IteratorType>> map(const TFunc &func_, IteratorType begin_, IteratorType end_) {
    return Iterable<imap_iterator<TFunc, IteratorType>>(imap_iterator<TFunc, IteratorType>(func_, begin_),
                                                        imap_iterator<TFunc, IteratorType>(func_, end_));
}

}  // namespace py

#endif  // MAP_HPP_
