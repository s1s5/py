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
#include "internal.hpp"

namespace py {

template <class TFunc, class TupleType>
class imap_iterator {
    // using element_type = decltype(std::declval<TFunc>()(*(std::declval<array_iterator_type>())));

 public:
    imap_iterator(TFunc &func_, TupleType&& iter_) : func(func_), iter(iter_) {}
    // imap_iterator(const imap_iterator &i) : func(i.func), iter(i.iter) {}
    // imap_iterator &operator = (const imap_iterator &i) { iter = i.iter; }
    // imap_iterator operator++(int) {
    //     imap_iterator tmp(*func, iter);
    //     ++iter;
    //     return tmp;
    // }
    imap_iterator &operator++() {
        internal::tuple_pincrement(iter);
        return *this;
    }
    auto operator*() const { return internal::tuple_apply(func, iter); }
    // auto operator->() const { return (*func)(*iter); }
    bool operator==(const imap_iterator &rhs) const { return internal::tuple_equal_or(iter, rhs.iter); }
    bool operator!=(const imap_iterator &rhs) const { return not internal::tuple_equal_or(iter, rhs.iter); }

 private:
    TFunc &func;
    TupleType iter;
};


template <class TFunc, class ...Tarrays>
class imap_lvalue {
 public:
    // using array_type = typename std::remove_const<typename std::remove_reference<Tarray>::type>::type;
    // using array_iterator_type = decltype(std::declval<const Tarray>().begin());

 public:
    imap_lvalue(TFunc func_, Tarrays&...args) : func(func_), arrays(std::forward_as_tuple(args...)) {}
    auto begin() {
        auto iters = internal::tuple_begin(arrays);
        return imap_iterator<TFunc, decltype(iters)>(func, std::move(iters));
    }
    auto end() {
        auto iters = internal::tuple_end(arrays);
        return imap_iterator<TFunc, decltype(iters)>(func, std::move(iters));
    }
    // auto end() const { return internal::tuple_end(arrays); }

    // imap_iterator<TFunc, decltype(begin(std::declval<std::tuple<Tarrays&...>>()))> begin() const {
    //     return imap_iterator<TFunc, decltype(begin(arrays))>(func, begin(arrays));
    // }
    // imap_iterator<TFunc, decltype(end(std::declval<std::tuple<Tarrays&...>>()))> end() const {
    //     return imap_iterator<TFunc, decltype(end(arrays))>(func, end(arrays));
    // }
    // imap_iterator<TFunc, array_iterator_type> cbegin() const { return begin(); }
    // imap_iterator<TFunc, array_iterator_type> cend() const { return end(); }

 public:
    TFunc func;
    std::tuple<Tarrays&...> arrays;
};

template <class TFunc, class ...Tarrays>
class imap_rvalue {
 public:
    // using array_type = typename std::remove_const<typename std::remove_reference<Tarray>::type>::type;
    // using array_iterator_type = decltype(std::declval<const Tarray>().begin());

 public:
    imap_rvalue(TFunc func_, const Tarrays &&...ar) : func(func_), arrays(ar...) {}
    auto begin() {
        auto iters = internal::tuple_begin(arrays);
        return imap_iterator<TFunc, decltype(iters)>(func, std::move(iters));
    }
    auto end() {
        auto iters = internal::tuple_end(arrays);
        return imap_iterator<TFunc, decltype(iters)>(func, std::move(iters));
    }
    // imap_iterator<TFunc, array_iterator_type> begin() const {
    //     return imap_iterator<TFunc, array_iterator_type>(func, array.begin());
    // }
    // imap_iterator<TFunc, array_iterator_type> end() const {
    //     return imap_iterator<TFunc, array_iterator_type>(func, array.end());
    // }
    // imap_iterator<TFunc, array_iterator_type> cbegin() const { return begin(); }
    // imap_iterator<TFunc, array_iterator_type> cend() const { return end(); }

 public:
    TFunc func;
    std::tuple<Tarrays...> arrays;
    // array_type array;
};

// template <class TFunc, class ...Tarrays>
// imap_lvalue<TFunc, Tarrays...> map(TFunc func_, const Tarrays&... ar) {
//     return imap_lvalue<TFunc, Tarrays...>(func_, ar...);
// }
template <class TFunc, class ...Tarrays>
auto map(TFunc &&func_, Tarrays&... ar) {  // NOLINT
    return imap_lvalue<TFunc, Tarrays...>(func_, ar...);
}
template <class TFunc, class ...Tarrays>
auto map(TFunc &func_, Tarrays&... ar) {  // NOLINT
    return imap_lvalue<TFunc&, Tarrays...>(func_, ar...);
}

template <class TFunc, class ...Tarrays>
auto map(TFunc &&func_, Tarrays&&... ar) {
    return imap_rvalue<TFunc, Tarrays...>(func_, std::move(ar...));
}
template <class TFunc, class ...Tarrays>
auto map(TFunc &func_, Tarrays&&... ar) {
    return imap_rvalue<TFunc&, Tarrays...>(func_, std::move(ar...));
}
// template <class TFunc, class IteratorType>
// Iterable<imap_iterator<TFunc, IteratorType>> map(const TFunc &func_, IteratorType begin_, IteratorType end_) {
//     return Iterable<imap_iterator<TFunc, IteratorType>>(imap_iterator<TFunc, IteratorType>(func_, begin_),
//                                                         imap_iterator<TFunc, IteratorType>(func_, end_));
// }

}  // namespace py

#endif  // MAP_HPP_
