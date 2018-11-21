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

namespace internal {
class RandomGenerator {
 public:
    static std::mt19937 &get() {
        static std::mt19937 mt{0};
        return mt;
    }
};
}  // namespace internal

// [0.0, 1.0)
template <class G>
double random(G &g) {
    return std::uniform_real_distribution<double>(0.0, 1.0)(g);
}

// minv <= N <= maxv
template <class G>
double uniform(G &g, double minv, double maxv) {
    return std::uniform_real_distribution<double>(minv,  std::nextafter(maxv, std::numeric_limits<double>::max()))(g);
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

template <class G, class V>
auto choice(G &g, V &v) -> decltype(*(std::declval<V>().begin())) {
    if (v.empty()) { throw std::invalid_argument("py::random::choice() list is empty"); }
    return v[randint(g, 0, v.size() - 1)];
}
template <class G, class V>
auto choice(G &g, const V &v) -> decltype(*(std::declval<V>().cbegin())) {
    if (v.empty()) { throw std::invalid_argument("py::random::choice() list is empty"); }
    return v[randint(g, 0, v.size() - 1)];
}

inline void seed(uint32_t seed) { internal::RandomGenerator::get().seed(seed); }
inline double random() { return random(internal::RandomGenerator::get()); }
inline double uniform(double minv, double maxv) { return uniform(internal::RandomGenerator::get(), minv, maxv); }
inline double gauss(double myu, double sigma) { return gauss(internal::RandomGenerator::get(), myu, sigma); }
inline int randint(int minv, int maxv) { return randint(internal::RandomGenerator::get(), minv, maxv); }
template <class V> auto choice(V &v) { return choice(internal::RandomGenerator::get(), v); }
template <class V> auto choice(const V &v) { return choice(internal::RandomGenerator::get(), v); }

}  // namespace py::random

#endif  // RANDOM_HPP_
