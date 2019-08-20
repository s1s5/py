/**
 * Copyright
 * @file reduce.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:41:12
 */
#ifndef REDUCE_HPP_
#define REDUCE_HPP_

#include <type_traits>

namespace py {

// TODO: not recommended in c++17
template <class TFunc, class Tarray>
auto reduce(TFunc func, const Tarray &ar) {
    auto p0 = begin(ar);
    if (p0 == end(ar)) {
        return typename std::remove_const<
            typename std::remove_reference<decltype(*(begin(std::declval<Tarray>())))>::type>::type();
    }
    typename std::result_of<TFunc(decltype(*(begin(std::declval<Tarray>()))),
                                  decltype(*(begin(std::declval<Tarray>()))))>::type dst = *p0;
    ++p0;
    while (p0 != end(ar)) {
        dst = func(dst, *p0);
        ++p0;
    }
    return dst;
}

template <class TFunc, class Tarray, class TFirst>
TFirst reduce(TFunc func, const Tarray &ar, const TFirst &first) {
    auto p0 = ar.begin();
    auto _end = ar.end();
    if (p0 == _end) {
        return first;
    }
    TFirst dst = func(first, *p0);
    ++p0;
    while (p0 != _end) {
        dst = func(dst, *p0);
        ++p0;
    }
    return dst;
}

#if 0
template <class TFunc, class TIterator>
auto reduce(TFunc func, TIterator iter, TIterator iter_end) ->
    typename std::result_of<TFunc(decltype(*(std::declval<TIterator>())),
                                  decltype(*(std::declval<TIterator>())))>::type {
    if (iter == iter_end) {
        return decltype(*(std::declval<TIterator>()))();
    }
    typename std::result_of<TFunc(decltype(*(std::declval<TIterator>())), decltype(*(std::declval<TIterator>())))>::type
        dst = *iter;
    ++iter;
    for (; iter != iter_end; ++iter) {
        dst = func(dst, *iter);
    }
    return dst;
}

template <class TFunc, class TIterator, class TFirst>
TFirst reduce(TFunc func, TIterator iter, TIterator iter_end, const TFirst &first) {
    if (iter == iter_end) {
        return first;
    }
    TFirst dst = func(first, *iter);
    ++iter;
    for (; iter != iter_end; ++iter) {
        dst = func(dst, *iter);
    }
    return dst;
}
#endif

}  // namespace py

#endif  // REDUCE_HPP_
