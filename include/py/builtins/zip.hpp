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

namespace py {

template <class IteratorType0, class IteratorType1>
class izip_iterator
    : public std::iterator<std::forward_iterator_tag, std::pair<decltype(*(std::declval<IteratorType0>())),
                                                                decltype(*(std::declval<IteratorType1>()))>> {
    using element_type0 = decltype(*(std::declval<IteratorType0>()));
    using element_type1 = decltype(*(std::declval<IteratorType1>()));
    using element_type = std::pair<element_type0, element_type1>;
    // using element_type = std::pair<IteratorType0, IteratorType1>;

 public:
    izip_iterator(IteratorType0 iter0_, IteratorType1 iter1_)
        :  // _pair(*iter0_, *iter1_),
          _iter0(iter0_),
          _iter1(iter1_) {}
    izip_iterator operator++(int) {
        izip_iterator tmp(_iter0, _iter1);
        ++_iter0;
        ++_iter1;
        // _pair.first = _iter0;
        // _pair.second = _iter1;
        return tmp;
    }
    izip_iterator &operator++() {
        ++_iter0;
        ++_iter1;
        // _pair.first = _iter0;
        // _pair.second = _iter1;
        return *this;
    }

    // element_type0 first() { return *_iter0; }
    // element_type1 second() { return *_iter1; }

    element_type operator*() const { return element_type(*_iter0, *_iter1); }
    std::shared_ptr<element_type> operator->() const {
        return std::shared_ptr<element_type>(new element_type(*_iter0, *_iter1));
    }  // TOOD(sawai): cost....
    // izip_iterator<IteratorType0, IteratorType1> &operator*() const { return *this; }
    // izip_iterator<IteratorType0, IteratorType1> *operator->() const { return this; }

    bool operator==(const izip_iterator &rhs) const { return _iter0 == rhs._iter0 || _iter1 == rhs._iter1; }
    bool operator!=(const izip_iterator &rhs) const { return _iter0 != rhs._iter0 && _iter1 != rhs._iter1; }

 private:
    // element_type _pair;
    IteratorType0 _iter0;
    IteratorType1 _iter1;
};

template <class Tarray0, class Tarray1>
class izip_ll {
    using iter_type0 = decltype(std::declval<Tarray0>().begin());
    using iter_type1 = decltype(std::declval<Tarray1>().begin());

 public:
    izip_ll(Tarray0 &ar0, Tarray1 &ar1) : array0(ar0), array1(ar1) {}
    izip_iterator<iter_type0, iter_type1> begin() {
        return izip_iterator<iter_type0, iter_type1>(array0.begin(), array1.begin());
    }
    izip_iterator<iter_type0, iter_type1> end() {
        return izip_iterator<iter_type0, iter_type1>(array0.end(), array1.end());
    }

 private:
    Tarray0 &array0;
    Tarray1 &array1;
};

template <class Tarray0, class Tarray1>
class izip_rl {
 public:
    using iter_type0 = decltype(std::declval<Tarray0>().begin());
    using iter_type1 = decltype(std::declval<Tarray1>().begin());

 public:
    izip_rl(Tarray0 &&ar0, Tarray1 &ar1) : array0(ar0), array1(ar1) {}
    // void show_types() const {
    //     std::cout << typeid(iter_type0).name() << std::endl;
    //     std::cout << typeid(iter_type1).name() << std::endl;
    //     std::cout << typeid(decltype(array0.begin())).name() << std::endl;
    //     std::cout << typeid(decltype(array1.begin())).name() << std::endl;
    // }
    izip_iterator<iter_type0, iter_type1> begin() {
        return izip_iterator<iter_type0, iter_type1>(array0.begin(), array1.begin());
    }
    izip_iterator<iter_type0, iter_type1> end() {
        return izip_iterator<iter_type0, iter_type1>(array0.end(), array1.end());
    }

 private:
 public:
    Tarray0 array0;
    Tarray1 &array1;
};

template <class Tarray0, class Tarray1>
class izip_lr {
    using iter_type0 = decltype(std::declval<Tarray0>().begin());
    using iter_type1 = decltype(std::declval<Tarray1>().begin());

 public:
    izip_lr(Tarray0 &ar0, Tarray1 &&ar1) : array0(ar0), array1(ar1) {}
    izip_iterator<iter_type0, iter_type1> begin() {
        return izip_iterator<iter_type0, iter_type1>(array0.begin(), array1.begin());
    }
    izip_iterator<iter_type0, iter_type1> end() {
        return izip_iterator<iter_type0, iter_type1>(array0.end(), array1.end());
    }

 private:
    Tarray0 &array0;
    Tarray1 array1;
};

template <class Tarray0, class Tarray1>
class izip_rr {
    using iter_type0 = decltype(std::declval<Tarray0>().begin());
    using iter_type1 = decltype(std::declval<Tarray1>().begin());
    using const_iter_type0 = decltype(std::declval<Tarray0>().cbegin());
    using const_iter_type1 = decltype(std::declval<Tarray1>().cbegin());

 public:
    izip_rr(Tarray0 &&ar0, Tarray1 &&ar1) : array0(ar0), array1(ar1) {}
    izip_iterator<iter_type0, iter_type1> begin() {
        return izip_iterator<iter_type0, iter_type1>(array0.begin(), array1.begin());
    }
    izip_iterator<iter_type0, iter_type1> end() {
        return izip_iterator<iter_type0, iter_type1>(array0.end(), array1.end());
    }

    izip_iterator<const_iter_type0, const_iter_type1> begin() const {
        return izip_iterator<iter_type0, iter_type1>(array0.begin(), array1.begin());
    }
    izip_iterator<const_iter_type0, const_iter_type1> end() const {
        return izip_iterator<iter_type0, iter_type1>(array0.end(), array1.end());
    }

 private:
    Tarray0 array0;
    Tarray1 array1;
};

template <class Tarray0, class Tarray1>
izip_ll<Tarray0, Tarray1> zip(Tarray0 &ar0, Tarray1 &ar1) {  // NOLINT
    return izip_ll<Tarray0, Tarray1>(ar0, ar1);
}

template <class Tarray0, class Tarray1>
izip_rl<Tarray0, Tarray1> zip(Tarray0 &&ar0, Tarray1 &ar1) {  // NOLINT
    return izip_rl<Tarray0, Tarray1>(std::move(ar0), ar1);
}

template <class Tarray0, class Tarray1>
izip_lr<Tarray0, Tarray1> zip(Tarray0 &ar0, Tarray1 &&ar1) {  // NOLINT
    return izip_lr<Tarray0, Tarray1>(ar0, std::move(ar1));
}

template <class Tarray0, class Tarray1>
izip_rr<Tarray0, Tarray1> zip(Tarray0 &&ar0, Tarray1 &&ar1) {  // NOLINT
    return izip_rr<Tarray0, Tarray1>(std::move(ar0), std::move(ar1));
}


}  // namespace py

#endif  // ZIP_HPP_
