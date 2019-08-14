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
 public:
    imap_iterator(TFunc &func_, TupleType&& iter_) : func(func_), iter(iter_) {}
    imap_iterator &operator++() {
        internal::tuple_pincrement(iter);
        return *this;
    }
    auto operator*() const { return internal::tuple_apply_iterators(func, iter); }
    bool operator==(const imap_iterator &rhs) const { return internal::tuple_equal_or(iter, rhs.iter); }
    bool operator!=(const imap_iterator &rhs) const { return not internal::tuple_equal_or(iter, rhs.iter); }

 private:
    TFunc &func;
    TupleType iter;
};


template <class TFunc, class TupleType>
class imap {
    using IterType = decltype(internal::tuple_begin(std::declval<TupleType&>()));
    using ElementType = decltype(internal::tuple_apply_iterators(std::declval<TFunc&>(), std::declval<IterType&>()));

 public:
    imap(TFunc &&func_, TupleType &&args_) : func(func_), args(args_) {}
    auto begin() {
        auto iters = internal::tuple_begin(args);
        return imap_iterator<TFunc, decltype(iters)>(func, std::move(iters));
    }

    auto end() {
        auto iters = internal::tuple_end(args);
        return imap_iterator<TFunc, decltype(iters)>(func, std::move(iters));
    }

    operator std::vector<ElementType> () {
        return std::vector<ElementType>{begin(), end()};
    }

 public:
    TFunc func;
    TupleType args;
};

template <class TFunc, class ...Args>
auto map(TFunc &&func_, Args &&... args) {
    auto t = std::tuple_cat(internal::tuple_intelligent_forward<Args>(args)...);
    return imap<TFunc, decltype(t)>(std::forward<TFunc>(func_), std::move(t));
}

}  // namespace py

namespace std {
template<class TFunc, class TupleType>
struct iterator_traits<py::imap_iterator<TFunc, TupleType>> {
    using iterator_category = std::input_iterator_tag;
};
} // namespace std

#endif  // MAP_HPP_
