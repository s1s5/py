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
#include <glob.h>

namespace py::glob {
inline std::vector<std::string> glob(const std::string &pattern) {
    std::vector<std::string> result;
    glob_t globbuf;
    glob(pattern.c_str(), 0, NULL, &globbuf);
    for (size_t i = 0; i < globbuf.gl_pathc; i++) {
        result.push_back(globbuf.gl_pathv[i]);
    }
    globfree(&globbuf);
    return result;
}
}  // namespace py::glob

#endif  // GLOB_HPP_
