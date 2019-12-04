/**
 * Copyright
 * @file zip.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:42:16
 */
#ifndef ZIP_HPP_
#define ZIP_HPP_

#include <vector>
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

template <class TupleType>
class izip {
    // using IterType = decltype(internal::tuple_begin(std::declval<TupleType&>()));
    // using ElementType = decltype(internal::tuple_deref(std::declval<IterType&>()));
    // TODO: deref tuple
    // using RRElementType = typename std::remove_reference<ElementType>::type;

 public:
    izip(TupleType &&t_) : t(t_) {}
    auto begin() {
        auto iters = internal::tuple_begin(t);
        return izip_iterator<decltype(iters)>(std::move(iters));
    }
    auto end() {
        auto iters = internal::tuple_end(t);
        return izip_iterator<decltype(iters)>(std::move(iters));
    }

    template<typename T>
    operator std::vector<T> () {
        return std::vector<T>{begin(), end()};
    }

 private:
    TupleType t;
};

template<typename ...Args>
auto zip(Args&&... args) {
    auto t = std::tuple_cat(internal::tuple_intelligent_forward<Args>(args)...);
    // auto t = std::tie(internal::tuple_intelligent_forward<Args>(args)...);
    // auto t = internal::tuple_intelligent_clone(args...);
    return izip<decltype(t)>(std::move(t));
}

}  // namespace py

namespace std {
template<class TupleType>
struct iterator_traits<py::izip_iterator<TupleType>> {
    using iterator_category = std::input_iterator_tag;
};
} // namespace std


#endif  // ZIP_HPP_
