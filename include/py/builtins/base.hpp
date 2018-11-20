/**
 * Copyright
 * @file base.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:32:40
 */
#ifndef BASE_HPP_
#define BASE_HPP_

#include <iterator>
#include <utility>

namespace py {

// not recommended in c++17
template <class IteratorType>
class Iterable : public std::iterator<std::input_iterator_tag,
                                      decltype(*std::declval<IteratorType>())> {
 public:
    Iterable(IteratorType begin_, IteratorType end_) : _begin(begin_), _end(end_) {}
    IteratorType begin() const { return _begin; }
    IteratorType end() const { return _end; }

 private:
    IteratorType _begin, _end;
};

template<class E, class V>
bool in(const E &e, const V &v) {
    for (auto &&i : v) {
        if (e == i) {
            return true;
        }
    }
    return false;
}


}  // namespace py

#endif  // BASE_HPP_
