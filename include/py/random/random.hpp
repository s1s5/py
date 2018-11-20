/**
 * Copyright
 * @file random.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 17:25:52
 */
#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <random>
#include <stdexcept>

namespace py::random {

// [0.0, 1.0)
template <class G>
double random(G &g) {
    return std::uniform_real_distribution<double>(0.0, 1.0)(g);
}

// minv <= N <= maxv
template <class G>
double uniform(G &g, double minv, double maxv) {
    std::uniform_real_distribution<double> r(minv, maxv + 1.0e-16);
    double value = r(g);
    while (value < minv || value > maxv) { value = r(g); }
    return value;
}

// return gaussian distribution
template <class G>
double gauss(G &g, double myu, double sigma) {
    return std::normal_distribution<>(myu, sigma)(g);
}

// minv <= N <= maxv
template <class G>
int randint(G &g, int minv, int maxv) {
    if (minv >= maxv) { return minv; }
    return std::uniform_int_distribution<>(minv, maxv)(g);
}

template <class V>
auto choice(V &v) -> decltype(*(std::declval<V>().begin())) {
    if (v.empty()) { throw std::invalid_argument("py::random::choice() list is empty"); }
    return v[randint(0, v.size() - 1)];
}
template <class V>
auto choice(const V &v) -> decltype(*(std::declval<V>().cbegin())) {
    if (v.empty()) { throw std::invalid_argument("py::random::choice() list is empty"); }
    return v[randint(0, v.size() - 1)];
}

}  // namespace py::random

#endif  // RANDOM_HPP_
