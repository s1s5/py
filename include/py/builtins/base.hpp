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
#include <vector>
#include <iterator>
#include <memory>
#include <functional>

namespace py {

namespace internal {
template <typename T>
class has_operator_size {
    typedef char one;
    typedef long two;

    template <typename C>
    static one test(decltype(&C::size));
    template <typename C>
    static two test(...);

 public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

}  // internal

// not recommended in c++17
template <class ElementType>
class Iterator {
 public:
    class IteratorType {
     public:
        template<typename X>
        IteratorType(const X &iter) {
            p = new X(iter);
            _delete = [](IteratorType *self) {
                delete (X*)self->p;
            };
            pincrement = [](IteratorType *self) {
                ((X*)self->p)-> operator ++();
            };
            aster = [](IteratorType *self) {
                return *(((X*)self->p)[0]);
            };
            eq = [](const IteratorType *self, const IteratorType *rhs) {
                // return ((X*)self->p)-> operator == (((const X*)(rhs->p))[0]);
                return ((X*)self->p)[0] == (((const X*)(rhs->p))[0]);
            };
            copy = [](const IteratorType *self) {
                return new X(((X*)self->p)[0]);
            };
        }
        ~IteratorType() {
            if (p) {
                _delete(this);
            }
            p = nullptr;
        }

        IteratorType &operator++() {
            pincrement(this);
            return *this;
        }
        auto operator*() { return aster(this); }
        bool operator==(const IteratorType &rhs) const { return eq(this, &rhs); }
        bool operator!=(const IteratorType &rhs) const { return not eq(this, &rhs); }

        IteratorType (const IteratorType &rhs) {
            p = rhs.copy(&rhs);
            pincrement = rhs.pincrement;
            _delete = rhs._delete;
            aster = rhs.aster;
            eq = rhs.eq;
            copy = rhs.copy;
        }

        IteratorType & operator = (const IteratorType &) = delete;

        void *p;
        std::function<void(IteratorType*)> pincrement, _delete;
        std::function<ElementType(IteratorType*)> aster;
        std::function<bool(const IteratorType*, const IteratorType*)> eq;
        std::function<void *(const IteratorType*)> copy;
    };

 public:
    // template<typename X>
    // Iterator(X &&x) : _begin(x.begin()), _end(x.end()) {
    // }
    template<typename X>
    Iterator(X &&x) : _begin(std::begin(x)), _end(std::end(x)) {
    }

    auto begin() const { return _begin; }
    auto end() const { return _end; }
    
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

template<class T>
typename std::enable_if<internal::has_operator_size<T>::value, size_t>::type len(const T& t) {
    return t.size();
}

}  // namespace py

#endif  // BASE_HPP_
