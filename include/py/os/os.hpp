/**
 * Copyright
 * @file os.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 17:09:52
 */
#ifndef OS_HPP_
#define OS_HPP_

#include "base.hpp"
#include "path.hpp"

namespace py::os {
inline void mkdirs(const std::string &path) {
    throw std::logic_error("py::os::makedirs not implemented");
}
}  // namespace py::os

#endif  // OS_HPP_
