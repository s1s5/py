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

inline std::string abspath(const std::string &path_) {
    std::string path = path_;
    if (!isabs(path)) {
        path = join(getcwd(), path);
        return normpath(path);
    }
    return normpath(path);
}
std::string basename(const std::string &path);
std::string commonpath(const std::vector<std::string> &paths);
std::string commonprefix(const std::vector<std::string> &paths);
std::string dirname(const std::string &path);
inline bool exists(const std::string &path) {
    if (0 != access(path.c_str(), F_OK)) {
        if (ENOENT == errno) {
            return false;
        }
    }
    return true;
}
bool lexists(const std::string &path);
std::string expanduser(const std::string &path);
std::string expandvars(const std::string &path);
float getatime(const std::string &path);
float getmtime(const std::string &path);
float getctime(const std::string &path);
size_t getsize(const std::string &path);
bool isabs(const std::string &path) {
    return (path != "" && path[0] == '/');
}
bool isfile(const std::string &path);
inline bool isdir(const std::string &path) {
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0) {
        return false;
    }
    return S_ISDIR(statbuf.st_mode);    
}
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
inline std::string normpath(const std::string &path) {
    std::string path = path_;
    if (path == "") {
        return ".";
    }
    int initial_slashes = py::startswith(path, "/") ? 1 : 0;
    if (initial_slashes &&
        py::startswith(path, "//") && (!py::startswith(path, "///"))) {
        initial_slashes = 2;
    }
    auto comps = py::split(path, "/");
    std::vector<std::string> new_comps;
    for (auto &&comp : comps) {
        if (comp == "" || comp == ".") {
            continue;
        }
        if (comp != ".." || ((!initial_slashes) && (!new_comps.size())) ||
            (new_comps.size() && new_comps.back() == "..")) {
            new_comps.push_back(comp);
        } else if (new_comps.size()) {
            new_comps.pop_back();
        }
    }
    comps = new_comps;
    std::stringstream ss;
    for (int i = 0; i < initial_slashes; i++) {
        ss << "/";
    }
    for (unsigned int i = 0; i < comps.size(); i++) {
        if (i) {
            ss << "/";
        }
        ss << comps[i];
    }
    path = ss.str();
    return path == "" ? "." : path;
}

std::string realpath(const std::string &path);
inline std::string relpath(const std::string &path, const std::string &base_ = "") {
    if (path == "") {
        return path;
    }
    std::string base = base_;
    if (base == "") {
        if (path != "" && path[0] != '/') {
            return path;
        }
        base = os::getcwd();
    }

    auto start_list = filter([](auto v) { return v.size(); }, py::split(path::abspath(base), "/"));
    auto path_list = filter([](auto v) { return v.size(); }, py::split(path::abspath(path), "/"));
    int common_prefix = 0;
    for (auto &&i : izip(start_list, path_list)) {
        // std::cout << *i.first << " - " << *i.second << std::endl;
        if (i.first != i.second) {
            break;
        }
        common_prefix++;
    }
    // printf("%d / %d / %d\n", common_prefix, start_list.size(), path_list.size());
    std::vector<std::string> rel_list;
    for (int i = 0; i < static_cast<int>(start_list.size()) - common_prefix; i++) {
        rel_list.push_back("..");
    }
    for (unsigned int i = common_prefix; i < path_list.size(); i++) {
        rel_list.push_back(path_list[i]);
    }
    if (rel_list.size() == 0) {
        return ".";
    }
    std::stringstream ss;
    for (unsigned int i = 0; i < rel_list.size(); i++) {
        if (i) {
            ss << "/";
        }
        ss << rel_list[i];
    }
    return ss.str();
}
bool samefile(const std::string &path1, const std::string &path2);
// sameopenfile(fp1, fp2)
// samestat(stat1, stat2)

inline std::pair<std::string, std::string> split(const std::string &path) {
    size_t pos = path.rfind('/');
    if (std::string::npos == pos) {
        return {"", path};
    }
    std::string head = path.substr(0, pos + 1);
    std::string tail = path.substr(pos + 1);
    std::stringstream all_slash;
    for (unsigned int i = 0; i < head.size(); i++) {
        all_slash << "/";
    }
    if (head != "" && head != all_slash.str()) {
        size_t right = head.find_last_not_of("/");
        if (std::string::npos != right) {
            head = head.substr(0, right + 1);
        }
    }
    return {head, tail};
}

// splitdrive(path)
inline std::pair<std::string, std::string> splitext(const std::string &path) {
    std::vector<std::string> s;
    size_t sep_index = path.rfind("/");
    size_t dot_index = path.rfind(".");
    if (sep_index != std::string::npos &&
        dot_index != std::string::npos &&
        sep_index > dot_index) {
        return {path, ""};
    }
    if (dot_index == 0 || dot_index == std::string::npos) {
        return {path, ""};
    }
    int fnindex = sep_index + 1;
    while (fnindex < dot_index) {
        if (path[fnindex] != '/' && path[fnindex] != '.') {
            return {
                path.substr(0, dot_index), path.substr(dot_index, path.size()),
                    };
        } else {
            fnindex++;
        }
    }
    return {
        // path.substr(0, index), path.substr(index, path.size()),
        path, "",
    };
}
// supports_unicode_filenames

}  // namespace py::os::path

#endif  // PATH_HPP_
