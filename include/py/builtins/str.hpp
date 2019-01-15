/**
 * Copyright
 * @file str.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 17:24:10
 */
#ifndef STR_HPP_
#define STR_HPP_

#include <string>
#include <vector>
#include <sstream>

namespace py {

template<class T>
std::string str(const T &t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

inline bool startswith(const std::string &str, const std::string &prefix) {
    return (str.size() >= prefix.size() &&
            str.compare(0, prefix.size(), prefix) == 0);
}

inline bool endswith(const std::string &str, const std::string &suffix) {
    return (str.size() >= suffix.size() &&
            str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0);
}

inline std::vector<std::string> split(const std::string &str, int max_split = -1) {
    std::string split = " ";
    std::vector<std::string> result;
    std::stringstream ss;
    unsigned int i = 0;
    while (startswith(str.substr(i), split)) {
        i += split.size();
    }
    for (; i < str.size() && max_split; i++) {
        unsigned int ii = i, j = 0;
        while (ii < str.size() && j < split.size() && str.at(ii) == split.at(j)) {
            ii++;
            j++;
        }

        if (j == split.size()) {
            i += split.size() - 1;
            if (!ss.str().empty()) {
                result.push_back(ss.str());
                max_split--;
            }
            ss.str("");
        } else {
            ss << str.at(i);
        }
    }
    while (startswith(str.substr(i), split)) {
        i += split.size();
    }
    if (i != str.size()) {
        result.push_back(str.substr(i));
    }
    if (!ss.str().empty()) {
        result.push_back(ss.str());
    }
    return result;
}

inline std::vector<std::string> split(const std::string &str, const std::string &split, int max_split = -1) {
    std::vector<std::string> result;
    std::stringstream ss;
    unsigned int i = 0;
    for (; i < str.size() && max_split; i++) {
        unsigned int ii = i, j = 0;
        while (ii < str.size() && j < split.size() && str.at(ii) == split.at(j)) {
            ii++;
            j++;
        }

        if (j == split.size()) {
            i += split.size() - 1;
            result.push_back(ss.str());
            max_split--;
            ss.str("");
        } else {
            ss << str.at(i);
        }
    }
    if (i != str.size()) {
        result.push_back(str.substr(i));
    } else if (!ss.str().empty()) {
        result.push_back(ss.str());
    } else if (endswith(str, split)) {
        result.push_back("");
    }
    if (!result.size()) {
        result.push_back("");
    }
    return result;
}


inline std::string replace(const std::string &orig, const std::string &target, const std::string &dst, int max_replace = -1) {
    std::string str = orig;
    if (target == "") {
        std::stringstream ss;
        for (auto &&i : orig) {
            if (max_replace == 0) {
                ss << i;
            } else {
                ss << dst;
                ss << i;
                max_replace--;
            }
        }
        if (max_replace) {
            ss << dst;
        }
        return ss.str();
    }
    for (size_t i = str.find(target, 0); i != std::string::npos; i = str.find(target, i + dst.size())) {
        if (max_replace == 0) {
            break;
        }
        str.replace(i, target.length(), dst);
        max_replace--;
    }
    return str;
}

inline std::string strip(const std::string &string, const char *trimCharacterList = " \t\v\r\n\f") {
    std::string result;
    std::string::size_type left = string.find_first_not_of(trimCharacterList);
    if (left != std::string::npos) {
        std::string::size_type right = string.find_last_not_of(trimCharacterList);
        result = string.substr(left, right - left + 1);
    }
    return result;
}

inline std::string lstrip(const std::string &string, const char *trimCharacterList = " \t\v\r\n\f") {
    std::string::size_type left = string.find_first_not_of(trimCharacterList);
    if (left && left != std::string::npos) {
        return string.substr(left);
    }
    return string;
}

inline std::string rstrip(const std::string &string, const char *trimCharacterList = " \t\v\r\n\f") {
    std::string::size_type right = string.find_last_not_of(trimCharacterList);
    if (right != std::string::npos && right != string.size() - 1) {
        return string.substr(0, right + 1);
    }
    return string;
}


inline std::string lower(const std::string &s) {
    std::string data(s);
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] <= 'Z' && s[i] >= 'A') {
            data[i] = s[i] - ('Z' - 'z');
        } else {
            data[i] = s[i];
        }
    }
    return data;
}

inline std::string upper(const std::string &s) {
    std::string data(s);
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] <= 'z' && s[i] >= 'a') {
            data[i] = s[i] + ('Z' - 'z');
        } else {
            data[i] = s[i];
        }
    }
    return data;
}

namespace string {

extern const std::string ascii_letters;
extern const std::string ascii_lowercase;
extern const std::string ascii_uppercase;
extern const std::string digits;
extern const std::string hexdigits;
extern const std::string octdigits;
extern const std::string printable;
extern const std::string punctuation;
extern const std::string whitespace;

template<class X>
std::string join(const std::string &joiner, const X &v) {
    std::stringstream ss;
    bool f = true;
    for (auto &&t : v) {
        if (f) {
            f = false;
        } else {
            ss << joiner;
        }
        ss << t;
    }
    return ss.str();
}

}  // namespace string


}  // namespace py

#endif  // STR_HPP_
