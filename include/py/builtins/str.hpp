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

std::vector<std::string> split(const std::string &str, int max_split = -1);
std::vector<std::string> split(const std::string &str, const std::string &split, int max_split = -1);
bool startswith(const std::string &str, const std::string &prefix);
bool endswith(const std::string &str, const std::string &suffix);
std::string replace(const std::string &orig, const std::string &target, const std::string &dst, int max_replace = -1);
std::string strip(const std::string &string, const char *trimCharacterList = " \t\v\r\n\f");
std::string lstrip(const std::string &string, const char *trimCharacterList = " \t\v\r\n\f");
std::string rstrip(const std::string &string, const char *trimCharacterList = " \t\v\r\n\f");

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
