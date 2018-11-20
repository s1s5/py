/**
 * Copyright
 * @file path.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 17:10:36
 */
#ifndef PATH_HPP_
#define PATH_HPP_

#include <string>
#include <vector>
#include <sstream>
#include <utility>

namespace py::os::path {

std::string abspath(const std::string &path_);
std::string basename(const std::string &path);
std::string commonpath(const std::vector<std::string> &paths);
std::string commonprefix(const std::vector<std::string> &paths);
std::string dirname(const std::string &path);
bool exists(const std::string &path);
bool lexists(const std::string &path);
std::string expanduser(const std::string &path);
std::string expandvars(const std::string &path);
float getatime(const std::string &path);
float getmtime(const std::string &path);
float getctime(const std::string &path);
size_t getsize(const std::string &path);
bool isabs(const std::string &path);
bool isfile(const std::string &path);
bool isdir(const std::string &path);
bool islink(const std::string &path);
bool ismount(const std::string &path);

template <typename... Args>
std::string join(Args const &... args) {
    std::ostringstream stream;
    bool start_slash = true, prev_slash = false;
    auto join_func = [&stream, &start_slash, &prev_slash](const std::string &s) {
        if (s != "" && s[0] == '/') {
            stream.str("");
            start_slash = true;
        }
        if (!start_slash && !prev_slash) {
            stream << "/";
            prev_slash = true;
        }
        stream << s;
        if (s != "") {
            start_slash = s.back() == '/';
            prev_slash = false;
        }
    };
    using List = int[];
    // (void)List{0, ((void)(stream << "/" << pargs), 0)...};
    (void)List{0, ((void)(join_func(args)), 0)...};
    // return stream.str().substr(1);
    return stream.str();
}
std::string normcase(const std::string &path);
std::string normpath(const std::string &path);
std::string realpath(const std::string &path);
std::string relpath(const std::string &path, const std::string &base = "");
bool samefile(const std::string &path1, const std::string &path2);
// sameopenfile(fp1, fp2)
// samestat(stat1, stat2)

std::pair<std::string, std::string> split(const std::string &path);
// splitdrive(path)
std::pair<std::string, std::string> splitext(const std::string &path);
// supports_unicode_filenames

}  // namespace py::os::path

#endif  // PATH_HPP_
