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
izip_rl<range, Tarray> enumerate(Tarray &ar) {  // NOLINT
    return izip_rl<range, Tarray>(range(1 << 30), ar);
}

template <class Tarray>
izip_rr<range, Tarray> enumerate(Tarray &&ar) {  // NOLINT
    return izip_rr<range, Tarray>(range(1 << 30), std::move(ar));
}

}  // namespace py

#endif  // ENUMERATE_HPP_
