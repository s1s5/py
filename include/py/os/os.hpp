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
#include <stdexcept>

#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace py::os {
inline std::string getcwd() {
    char cwd[4096];
    if (::getcwd(cwd, sizeof(cwd)) != NULL) {
        return cwd;
    }
    throw std::runtime_error("py::os::getcwd()");
}

inline void mkdir(const std::string &path) {
    ::mkdir(path.c_str(), S_IRWXU);
}

inline void mkdirs(const std::string &path) {
    throw std::logic_error("py::os::makedirs not implemented");
}

inline std::vector<std::string> listdir(const std::string &path) {
    std::vector<std::string> l;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (::strcmp(ent->d_name, ".") == 0 ||
                ::strcmp(ent->d_name, "..") == 0) {
                continue;
            }
            l.push_back(ent->d_name);
        }
        closedir(dir);
    } else {
        throw std::runtime_error("py::os::listdir()");
    }
    return l;
}

inline void remove(const std::string &path) {
    ::remove(path.c_str());
}

inline void rmdir(const std::string &path) {
    ::remove(path.c_str());
}

}  // namespace py::os

#include "path.hpp"

#endif  // OS_HPP_
