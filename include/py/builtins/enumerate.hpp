/**
 * Copyright
 * @file enumerate.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 16:43:41
 */
#ifndef ENUMERATE_HPP_
#define ENUMERATE_HPP_

#include "zip.hpp"
#include "range.hpp"

namespace py {

template <class Tarray>
auto enumerate(Tarray &ar, int start_index = 0) {  // NOLINT
    return zip(range(start_index, 1 << 30), ar);
}

template <class Tarray>
auto enumerate(Tarray &&ar, int start_index = 0) {  // NOLINT
    return zip(range(start_index, 1 << 30), std::move(ar));
}

}  // namespace py

#endif  // ENUMERATE_HPP_
