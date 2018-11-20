/**
 * Copyright 2015- Co. Ltd. sizebook
 * @file test_path.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 19:33:37
 */
#include "../cpput.hpp"

#include "py/os/path.hpp"

namespace {

TEST(py_os_path, basename) {
    // Python test
    ASSERT_EQ(std::string("bar"), ::py::os::path::basename("/foo/bar"));
    ASSERT_EQ(std::string(""), ::py::os::path::basename("/"));
    ASSERT_EQ(std::string("foo"), ::py::os::path::basename("foo"));
    ASSERT_EQ(std::string("foo"), ::py::os::path::basename("////foo"));
    ASSERT_EQ(std::string("bar"), ::py::os::path::basename("//foo//bar"));
    ASSERT_EQ(std::string(""), ::py::os::path::basename("/usr/"));

    // posix test
    ASSERT_EQ(std::string("lib"), ::py::os::path::basename("/usr/lib"));
    // ASSERT_EQ("usr", ::py::os::path::basename("/usr/"));
    ASSERT_EQ(std::string("usr"), ::py::os::path::basename("usr"));
    // ASSERT_EQ("/", ::py::os::path::basename("/"));
    ASSERT_EQ(std::string("."), ::py::os::path::basename("."));
    ASSERT_EQ(std::string(".."), ::py::os::path::basename(".."));
}

TEST(py_os_path, dirname) {
    // Python test
    ASSERT_EQ(std::string("/foo"), ::py::os::path::dirname("/foo/bar"));
    ASSERT_EQ(std::string("/"), ::py::os::path::dirname("/"));
    ASSERT_EQ(std::string("."), ::py::os::path::dirname("./foo"));
    ASSERT_EQ(std::string(""), ::py::os::path::dirname("foo"));
    ASSERT_EQ(std::string("////"), ::py::os::path::dirname("////foo"));
    ASSERT_EQ(std::string("///"), ::py::os::path::dirname("///foo"));
    ASSERT_EQ(std::string("//"), ::py::os::path::dirname("//foo"));
    ASSERT_EQ(std::string("/"), ::py::os::path::dirname("/foo"));
    ASSERT_EQ(std::string("//foo"), ::py::os::path::dirname("//foo//bar"));

    // posix test
    ASSERT_EQ(std::string("/usr"), ::py::os::path::dirname("/usr/lib"));
    // ASSERT_EQ("/", ::py::os::path::dirname("/usr/"));
    // ASSERT_EQ(".", ::py::os::path::dirname("usr"));
    ASSERT_EQ(std::string("/"), ::py::os::path::dirname("/"));
    // ASSERT_EQ(".", ::py::os::path::dirname("."));
    // ASSERT_EQ(".", ::py::os::path::dirname(".."));
}

TEST(py_os_path, relpath) {
    std::string curdir = ::py::os::path::basename(::py::os::getcwd());
    // std::cout << curdir << std::endl;
    // ASSERT_EQ("a", relpath("a"));
    ASSERT_EQ(std::string(""), ::py::os::path::relpath(""));
    ASSERT_EQ(std::string("a"), ::py::os::path::relpath(::py::os::path::abspath("a")));
    ASSERT_EQ(std::string("a/b"), ::py::os::path::relpath("a/b"));
    ASSERT_EQ(std::string("../a/b"), ::py::os::path::relpath("../a/b"));
    ASSERT_EQ(std::string("../" + curdir + "/a"), ::py::os::path::relpath("a", "../b"));
    ASSERT_EQ(std::string("../" + curdir + "/a/b"), ::py::os::path::relpath("a/b", "../c"));
    ASSERT_EQ(std::string("../../a"), ::py::os::path::relpath("a", "b/c"));
    ASSERT_EQ(std::string("."), ::py::os::path::relpath("a", "a"));
    ASSERT_EQ(std::string("../../../foo/bar/bat"), ::py::os::path::relpath("/foo/bar/bat", "/x/y/z"));
    ASSERT_EQ(std::string("bat"), ::py::os::path::relpath("/foo/bar/bat", "/foo/bar"));
    ASSERT_EQ(std::string("foo/bar/bat"), ::py::os::path::relpath("/foo/bar/bat", "/"));
    ASSERT_EQ(std::string("../../.."), ::py::os::path::relpath("/", "/foo/bar/bat"));
    ASSERT_EQ(std::string("../foo/bar/bat"), ::py::os::path::relpath("/foo/bar/bat", "/x"));
    ASSERT_EQ(std::string("../../../x"), ::py::os::path::relpath("/x", "/foo/bar/bat"));
    ASSERT_EQ(std::string("."), ::py::os::path::relpath("/", "/"));
    ASSERT_EQ(std::string("."), ::py::os::path::relpath("/a", "/a"));
    ASSERT_EQ(std::string("."), ::py::os::path::relpath("/a/b", "/a/b"));
}

TEST(py_os_path, join) {
    ASSERT_EQ(std::string("/bar/baz"), ::py::os::path::join("/foo", "bar", "/bar", "baz"));
    ASSERT_EQ(std::string("/foo/bar/baz"), ::py::os::path::join("/foo", "bar", "baz"));
    ASSERT_EQ(std::string("/foo/bar/baz/"), ::py::os::path::join("/foo/", "bar/", "baz/"));
    ASSERT_EQ(std::string("hello/world"), ::py::os::path::join("", "hello", "world"));
    ASSERT_EQ(std::string("hello/world"), ::py::os::path::join("hello", "", "world"));
    ASSERT_EQ(std::string("hello/world"), ::py::os::path::join("", "hello", "", "", "world"));
    ASSERT_EQ(std::string("./hello/world"), ::py::os::path::join("", "./", "", "hello", "", "", "world"));
    ASSERT_EQ(std::string("././hello/world"), ::py::os::path::join("", "./", ".", "hello", "", "", "world"));
}

TEST(py_os_path, listFiles) {}

TEST(py_os_path, isDir) {}

TEST(py_os_path, exists) {}


TEST(py_os_path, splitext) {
    auto test_split_ext = [](const std::string &path, const std::string &filename, const std::string &ext) {
        std::vector<std::pair<std::string, std::string>> answer = {
            {filename, ext},
            {"/" + filename, ext},
            {"abc/" + filename, ext},
            {"abc.def/" + filename, ext},
            {"/abc.def/" + filename, ext},
            {filename + ext + "/", ""},
        };
        std::vector<std::pair<std::string, std::string>> results = {
            ::py::os::path::splitext(path),
            ::py::os::path::splitext("/" + path),
            ::py::os::path::splitext("abc/" + path),
            ::py::os::path::splitext("abc.def/" + path),
            ::py::os::path::splitext("/abc.def/" + path),
            ::py::os::path::splitext(path + "/"),
        };

        for (size_t i = 0; i < answer.size(); i++) {
            ASSERT_EQ(answer[i].first, results[i].first);
            ASSERT_EQ(answer[i].second, results[i].second);
        }
    };

    test_split_ext("foo.bar", "foo", ".bar");
    test_split_ext("foo.boo.bar", "foo.boo", ".bar");
    test_split_ext("foo.boo.biff.bar", "foo.boo.biff", ".bar");
    test_split_ext(".csh.rc", ".csh", ".rc");
    test_split_ext("nodots", "nodots", "");
    test_split_ext(".cshrc", ".cshrc", "");
    test_split_ext("...manydots", "...manydots", "");
    test_split_ext("...manydots.ext", "...manydots", ".ext");
    test_split_ext(".", ".", "");
    test_split_ext("..", "..", "");
    test_split_ext("........", "........", "");
    test_split_ext("", "", "");
    test_split_ext("/home/hoge/xxx.y", "/home/hoge/xxx", ".y");
}

TEST(py_os_path, split) {
    std::vector<std::pair<std::string, std::string>> answer = {
        {"/foo", "bar"}, {"/", ""}, {"", "foo"}, {"////", "foo"}, {"//foo", "bar"},
    };
    std::vector<std::pair<std::string, std::string>> results = {
        ::py::os::path::split("/foo/bar"), ::py::os::path::split("/"), ::py::os::path::split("foo"),
        ::py::os::path::split("////foo"), ::py::os::path::split("//foo//bar"),
    };
    for (size_t i = 0; i < answer.size(); i++) {
        ASSERT_EQ(answer[i].first, results[i].first);
        ASSERT_EQ(answer[i].second, results[i].second);
    }
}

TEST(py_os_path, isabs) {
    ASSERT_EQ(false, ::py::os::path::isabs(""));
    ASSERT_EQ(true, ::py::os::path::isabs("/"));
    ASSERT_EQ(true, ::py::os::path::isabs("/foo"));
    ASSERT_EQ(true, ::py::os::path::isabs("/foo/bar"));
    ASSERT_EQ(false, ::py::os::path::isabs("foo/bar"));
}


}  // namespace

