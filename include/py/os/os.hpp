/**
 * Copyright
 * @file os.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 17:09:52
 */
#ifndef OS_HPP_
#define OS_HPP_

#include <string>
#include <vector>

namespace py::os {
std::string getcwd();
void mkdir(const std::string &path);
void mkdirs(const std::string &path);
std::vector<std::string> listdir(const std::string &path);
void remove(const std::string &path);
void rmdir(const std::string &path);
}  // namespace py::os

#endif  // OS_HPP_
