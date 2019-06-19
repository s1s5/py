/**
 * Copyright
 * @file range.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:43:06
 */
#ifndef RANGE_HPP_
#define RANGE_HPP_

#include <iterator>

namespace py {

class range {
 public:
    class Iterator : public std::iterator<std::input_iterator_tag, int> {
     private:
        Iterator(int c, int e, int s) : _cur(c), _end(e), _step(s) {}

     public:
        // Iterator(const Iterator &i) : _cur(i._cur), _end(i._end), _step(i._step) {}
        Iterator operator++(int) {
            Iterator tmp(_cur, _end, _step);
            _cur += _step;
            return tmp;
        }
        Iterator &operator++() {
            _cur += _step;
            return *this;
        }
        const int &operator*() const { return _cur; }
        const int *operator->() const { return &_cur; }
        bool operator==(const Iterator &rhs) const { return _cur == rhs._cur; }
        bool operator!=(const Iterator &rhs) const { return !((*this) == rhs); }

     // private:
     //    bool isEnd() const;

     private:
        int _cur, _end, _step;
        friend class range;
    };

 public:
    explicit range(int32_t a) : range(0, a, 1) {}
    range(int32_t s, int32_t e) : range(s, e, 1) {}
    range(int32_t s, int32_t e, int32_t step) : _start(s), _end(e), _step(step) {
        if ((_end - _start) * _step < 0) {
            _size = 0;
        } else {
            _size = (_end - _start + _step - 1) / _step;
        }
    }
    
    Iterator begin() const { return Iterator(_start, _end, _step); }
    Iterator end() const {
        if ((_end - _start) * _step < 0) {
            return Iterator(_start, _end, _step);
        } else {
            return Iterator(
                ((_end - _start) / _step + (((_end - _start) % _step) ? 1 : 0)) * _step + _start, _end, _step);
        }
    }
    Iterator cbegin() const { return begin(); }
    Iterator cendy() const { return end(); }

    int32_t operator[](int i) const {
        if (i < 0) {
            i = _size + i;
        }
        if (i < 0 or i >= _size) {
            throw std::range_error("py::range::operator[]");
        }
        return _start + _step * i;
    }

    size_t size() const {
        return _size;
    }

 private:
    int _start, _end, _step, _size;

    friend py::range::Iterator begin(const py::range &r);
    friend py::range::Iterator end(const py::range &r);
};

inline py::range::Iterator begin(const py::range &r) {
    return r.begin();
}
inline py::range::Iterator end(const py::range &r) {
    return r.end();
}

}  // namespace py

#endif  // RANGE_HPP_
