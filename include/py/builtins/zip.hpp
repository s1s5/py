/**
 * Copyright
 * @file zip.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:42:16
 */
#ifndef ZIP_HPP_
#define ZIP_HPP_

#include <iterator>
#include <memory>

#include "internal.hpp"

namespace py {

template <class TupleType>
class izip_iterator {
 public:
    izip_iterator(TupleType &&iter_) : iter(iter_) {}
    izip_iterator &operator++() {
        internal::tuple_pincrement(iter);
        return *this;
    }

    auto operator*() const { return internal::tuple_deref(iter); }
    bool operator==(const izip_iterator &rhs) const { return internal::tuple_equal_or(iter, rhs.iter); }
    bool operator!=(const izip_iterator &rhs) const { return not internal::tuple_equal_or(iter, rhs.iter); }

 private:
    TupleType iter;
};

template <class ...Tarrays>
class izip_l {
 public:
    izip_l(Tarrays&...arrays_) : arrays(std::forward_as_tuple(arrays_...)) {}
    auto begin() {
        auto iters = internal::tuple_begin(arrays);
        return izip_iterator<decltype(iters)>(std::move(iters));
    }
    auto end() {
        auto iters = internal::tuple_end(arrays);
        return izip_iterator<decltype(iters)>(std::move(iters));
    }

 private:
    std::tuple<Tarrays&...> arrays;
};

template <class ...Tarrays>
class izip_r {
 public:
    izip_r(Tarrays&&...arrays_) : arrays(std::forward_as_tuple(arrays_...)) {}
    auto begin() {
        auto iters = internal::tuple_begin(arrays);
        return izip_iterator<decltype(iters)>(std::move(iters));
    }
    auto end() {
        auto iters = internal::tuple_end(arrays);
        return izip_iterator<decltype(iters)>(std::move(iters));
    }

 private:
    std::tuple<Tarrays...> arrays;
};

template<class ...Tarrays>
auto zip(Tarrays & ... arrays) {
    return izip_l<Tarrays...>(arrays...);
}

template<class ...Tarrays>
auto zip(Tarrays && ... arrays) {
    return izip_l<Tarrays...>(arrays...);
}

}  // namespace py

#endif  // ZIP_HPP_
