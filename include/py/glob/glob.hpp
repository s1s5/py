/**
 * Copyright
 * @file glob.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 17:26:31
 */
#ifndef GLOB_HPP_
#define GLOB_HPP_

#include <string>
#include <vector>

namespace py::glob {
std::vector<std::string> glob(const std::string &pattern);
}  // namespace py::glob

#endif  // GLOB_HPP_
