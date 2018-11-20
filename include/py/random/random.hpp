/**
 * Copyright
 * @file random.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 17:25:52
 */
#ifndef RANDOM_HPP_
#define RANDOM_HPP_

namespace py::random {

void seed(int s);
double random();  // [0.0, 1.0)
double uniform(double minv, double maxv);  // minv <= N <= maxv
double gauss(double myu, double sigma);  // return gaussian distribution
int randint(int minv, int maxv);  // minv <= N <= maxv
template<class V> auto choice(V &v) -> decltype(*(std::declval<V>().begin())) { return v[randint(0, v.size() -1)]; }
template<class V> auto choice(const V &v) -> decltype(*(std::declval<V>().cbegin())) { return v[randint(0, v.size() -1)]; }


}  // namespace py::random

#endif  // RANDOM_HPP_
