/**
 * Copyright
 * @file test_str.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2018-11-20 18:00:52
 */
#include "../cpput.hpp"

#include "py/builtins/str.hpp"

namespace {

using namespace py;

TEST(py_builtins_str, str) {
    ASSERT_EQ(std::string("3"), str(3));
}

TEST(py_builtins_str, startswith) {
#define CHECK_(b, s, x) ASSERT_EQ(b, startswith(s, x))
    CHECK_(true, "hello", "he");
    CHECK_(true, "hello", "hello");
    CHECK_(false, "hello", "hello world");
    CHECK_(true, "hello", "");
    CHECK_(false, "hello", "ello");
#undef CHECK_
}

TEST(py_builtins_str, endswith) {
#define CHECK_(b, s, x) ASSERT_EQ(b, endswith(s, x))
    CHECK_(true, "hello", "lo");
    CHECK_(false, "hello", "he");
    CHECK_(true, "hello", "");
    CHECK_(false, "hello", "hello world");
    CHECK_(false, "helloworld", "worl");
#undef CHECK_
}

TEST(py_builtins_str, split) {
    auto equal = [](const std::vector<std::string> &ans, const std::vector<std::string> &res) {
        ASSERT_EQ(ans.size(), res.size());
        for (int i = 0; i < std::min<int>(ans.size(), res.size()); i++) {
            ASSERT_EQ(ans[i], res[i]);
        }
    };

    equal({"a", "b", "c", "d"}, split("a b c d "));
    equal({"a", "b c d"}, split("a b c d", 1));
    equal({"a", "b", "c d"}, split("a b c d", 2));
    equal({"a", "b", "c", "d"}, split("a b c d", 3));
    equal({"a", "b", "c", "d"}, split("a b c d", 4));
    equal({"a", "b", "c", "d"}, split("a b c d", 1 << 30));
    equal({"a b c d"}, split("a b c d", 0));
    equal({"a b c d"}, split("  a b c d", 0));
    equal({"a", "b", "c  d"}, split("a  b  c  d", 2));
    equal({}, split("         "));
    equal({"a"}, split("  a    "));
    equal({"a", "b"}, split("  a    b   "));
    equal({"a", "b   "}, split("  a    b   ", 1));
    equal({"a    b   c   "}, split("  a    b   c   ", 0));
    equal({"a", "b   c   "}, split("  a    b   c   ", 1));
    equal({"a", "b", "c   "}, split("  a    b   c   ", 2));
    equal({"a", "b", "c"}, split("  a    b   c   ", 3));
    equal({"a", "b", "c", "d"}, split("a|b|c|d", "|"));
    equal({"a|b|c|d"}, split("a|b|c|d", "|", 0));
    equal({"a", "b|c|d"}, split("a|b|c|d", "|", 1));
    equal({"a", "b", "c|d"}, split("a|b|c|d", "|", 2));
    equal({"a", "b", "c", "d"}, split("a|b|c|d", "|", 3));
    equal({"a", "b", "c", "d"}, split("a|b|c|d", "|", 4));
    equal({"a", "b", "c", "d"}, split("a|b|c|d", "|", 1 << 30));
    equal({"a|b|c|d"}, split("a|b|c|d", "|", 0));
    equal({"a", "", "b||c||d"}, split("a||b||c||d", "|", 2));
    equal({"abcd"}, split("abcd", "|"));
    equal({""}, split("", "|"));
    equal({"endcase ", ""}, split("endcase |", "|"));
    equal({"", " startcase"}, split("| startcase", "|"));
    equal({"", "bothcase", ""}, split("|bothcase|", "|"));
    equal({"a", "b", "c", "d"}, split("a//b//c//d", "//"));
    equal({"a", "b//c//d"}, split("a//b//c//d", "//", 1));
    equal({"a", "b", "c//d"}, split("a//b//c//d", "//", 2));
    equal({"a", "b", "c", "d"}, split("a//b//c//d", "//", 3));
    equal({"a", "b", "c", "d"}, split("a//b//c//d", "//", 4));
    equal({"a", "b", "c", "d"}, split("a//b//c//d", "//", 1 << 30));
    equal({"a//b//c//d"}, split("a//b//c//d", "//", 0));
    equal({"a", "", "b////c////d"}, split("a////b////c////d", "//", 2));
    equal({"endcase ", ""}, split("endcase test", "test"));
    equal({"", " begincase"}, split("test begincase", "test"));
    equal({"", " bothcase ", ""}, split("test bothcase test", "test"));
    equal({"a", "bc"}, split("abbbc", "bb"));
    equal({"", ""}, split("aaa", "aaa"));
    equal({"aaa"}, split("aaa", "aaa", 0));
    equal({"ab", "ab"}, split("abbaab", "ba"));
    equal({"aaaa"}, split("aaaa", "aab"));
    equal({""}, split("", "aaa"));
    equal({"aa"}, split("aa", "aaa"));
    equal({"A", "bobb"}, split("Abbobbbobb", "bbobb"));
    equal({"A", "B", ""}, split("AbbobbBbbobb", "bbobb"));
}


TEST(py_builtins_str, replace) {
#define EQ(ans, ...) ASSERT_EQ(ans, replace(__VA_ARGS__))

    // Operations on the empty string
    EQ("", "", "", "");
    EQ("A", "", "", "A");
    EQ("", "", "A", "");
    EQ("", "", "A", "A");
    EQ("", "", "", "", 100);
    EQ("", "", "", "", 1 << 30);

    // interleave (from=="", 'to' gets inserted everywhere)
    EQ("A", "A", "", "");
    EQ("*A*", "A", "", "*");
    EQ("*1A*1", "A", "", "*1");
    EQ("*-#A*-#", "A", "", "*-#");
    EQ("*-A*-A*-", "AA", "", "*-");
    EQ("*-A*-A*-", "AA", "", "*-", -1);
    EQ("*-A*-A*-", "AA", "", "*-", 1 << 30);
    EQ("*-A*-A*-", "AA", "", "*-", 4);
    EQ("*-A*-A*-", "AA", "", "*-", 3);
    EQ("*-A*-A", "AA", "", "*-", 2);
    EQ("*-AA", "AA", "", "*-", 1);
    EQ("AA", "AA", "", "*-", 0);

    //  single character deletion (from=="A", to=="")
    EQ("", "A", "A", "");
    EQ("", "AAA", "A", "");
    EQ("", "AAA", "A", "", -1);
    EQ("", "AAA", "A", "", 1 << 30);
    EQ("", "AAA", "A", "", 4);
    EQ("", "AAA", "A", "", 3);
    EQ("A", "AAA", "A", "", 2);
    EQ("AA", "AAA", "A", "", 1);
    EQ("AAA", "AAA", "A", "", 0);
    EQ("", "AAAAAAAAAA", "A", "");
    EQ("BCD", "ABACADA", "A", "");
    EQ("BCD", "ABACADA", "A", "", -1);
    EQ("BCD", "ABACADA", "A", "", 1 << 30);
    EQ("BCD", "ABACADA", "A", "", 5);
    EQ("BCD", "ABACADA", "A", "", 4);
    EQ("BCDA", "ABACADA", "A", "", 3);
    EQ("BCADA", "ABACADA", "A", "", 2);
    EQ("BACADA", "ABACADA", "A", "", 1);
    EQ("ABACADA", "ABACADA", "A", "", 0);
    EQ("BCD", "ABCAD", "A", "");
    EQ("BCD", "ABCADAA", "A", "");
    EQ("BCD", "BCD", "A", "");
    EQ("*************", "*************", "A", "");
    // EQ("^A^", "^"+"A"*1000+"^", "A", "", 999);

    // # substring deletion (from=="the", to=="")
    EQ("", "the", "the", "");
    EQ("ater", "theater", "the", "");
    EQ("", "thethe", "the", "");
    EQ("", "thethethethe", "the", "");
    EQ("aaaa", "theatheatheathea", "the", "");
    EQ("that", "that", "the", "");
    EQ("thaet", "thaet", "the", "");
    EQ("here and re", "here and there", "the", "");
    EQ("here and re and re", "here and there and there", "the", "", 1 << 30);
    EQ("here and re and re", "here and there and there", "the", "", -1);
    EQ("here and re and re", "here and there and there", "the", "", 3);
    EQ("here and re and re", "here and there and there", "the", "", 2);
    EQ("here and re and there", "here and there and there", "the", "", 1);
    EQ("here and there and there", "here and there and there", "the", "", 0);
    EQ("here and re and re", "here and there and there", "the", "");

    EQ("abc", "abc", "the", "");
    EQ("abcdefg", "abcdefg", "the", "");

    // # substring deletion (from=="bob", to=="");
    EQ("bob", "bbobob", "bob", "");
    EQ("bobXbob", "bbobobXbbobob", "bob", "");
    EQ("aaaaaaa", "aaaaaaabob", "bob", "");
    EQ("aaaaaaa", "aaaaaaa", "bob", "");

    // # single character replace in place (len(from);==len(to);==1);
    EQ("Who goes there?", "Who goes there?", "o", "o");
    EQ("WhO gOes there?", "Who goes there?", "o", "O");
    EQ("WhO gOes there?", "Who goes there?", "o", "O", 1 << 30);
    EQ("WhO gOes there?", "Who goes there?", "o", "O", -1);
    EQ("WhO gOes there?", "Who goes there?", "o", "O", 3);
    EQ("WhO gOes there?", "Who goes there?", "o", "O", 2);
    EQ("WhO goes there?", "Who goes there?", "o", "O", 1);
    EQ("Who goes there?", "Who goes there?", "o", "O", 0);

    EQ("Who goes there?", "Who goes there?", "a", "q");
    EQ("who goes there?", "Who goes there?", "W", "w");
    EQ("wwho goes there?ww", "WWho goes there?WW", "W", "w");
    EQ("Who goes there!", "Who goes there?", "?", "!");
    EQ("Who goes there!!", "Who goes there??", "?", "!");

    EQ("Who goes there?", "Who goes there?", ".", "!");

    // # substring replace in place (len(from);==len(to); > 1);
    EQ("Th** ** a t**sue", "This is a tissue", "is", "**");
    EQ("Th** ** a t**sue", "This is a tissue", "is", "**", 1 << 30);
    EQ("Th** ** a t**sue", "This is a tissue", "is", "**", -1);
    EQ("Th** ** a t**sue", "This is a tissue", "is", "**", 4);
    EQ("Th** ** a t**sue", "This is a tissue", "is", "**", 3);
    EQ("Th** ** a tissue", "This is a tissue", "is", "**", 2);
    EQ("Th** is a tissue", "This is a tissue", "is", "**", 1);
    EQ("This is a tissue", "This is a tissue", "is", "**", 0);
    EQ("cobob", "bobob", "bob", "cob");
    EQ("cobobXcobocob", "bobobXbobobob", "bob", "cob");
    EQ("bobob", "bobob", "bot", "bot");

    // # replace single character (len(from);==1, len(to);>1);
    EQ("ReyKKjaviKK", "Reykjavik", "k", "KK");
    EQ("ReyKKjaviKK", "Reykjavik", "k", "KK", -1);
    EQ("ReyKKjaviKK", "Reykjavik", "k", "KK", 1 << 30);
    EQ("ReyKKjaviKK", "Reykjavik", "k", "KK", 2);
    EQ("ReyKKjavik", "Reykjavik", "k", "KK", 1);
    EQ("Reykjavik", "Reykjavik", "k", "KK", 0);
    EQ("A----B----C----", "A.B.C.", ".", "----");

    EQ("Reykjavik", "Reykjavik", "q", "KK");

    // # replace substring (len(from);>1, len(to);!=len(from););
    EQ("ham, ham, eggs and ham", "spam, spam, eggs and spam", "spam", "ham");
    EQ("ham, ham, eggs and ham", "spam, spam, eggs and spam", "spam", "ham", 1 << 30);
    EQ("ham, ham, eggs and ham", "spam, spam, eggs and spam", "spam", "ham", -1);
    EQ("ham, ham, eggs and ham", "spam, spam, eggs and spam", "spam", "ham", 4);
    EQ("ham, ham, eggs and ham", "spam, spam, eggs and spam", "spam", "ham", 3);
    EQ("ham, ham, eggs and spam", "spam, spam, eggs and spam", "spam", "ham", 2);
    EQ("ham, spam, eggs and spam", "spam, spam, eggs and spam", "spam", "ham", 1);
    EQ("spam, spam, eggs and spam", "spam, spam, eggs and spam", "spam", "ham", 0);

    EQ("bobob", "bobobob", "bobob", "bob");
    EQ("bobobXbobob", "bobobobXbobobob", "bobob", "bob");
    EQ("BOBOBOB", "BOBOBOB", "bob", "bobby");
#undef EQ
}

TEST(py_builtins_str, strip_lstrip_rstrip) {
#define EQ(ans, func, ...) ASSERT_EQ(ans, func(__VA_ARGS__))
    EQ("hello", strip, "   hello   ");
    EQ("hello   ", lstrip, "   hello   ");
    EQ("   hello", rstrip, "   hello   ");
    EQ("hello", strip, "hello");
    std::string b = " \t\n\r\f\vabc \t\n\r\f\v";
    EQ("abc", strip, b);
    EQ("abc \t\n\r\f\v", lstrip, b);
    EQ(" \t\n\r\f\vabc", rstrip, b);

    // # strip/lstrip/rstrip with str arg
    EQ("hello", strip, "xyzzyhelloxyzzy", "xyz");
    EQ("helloxyzzy", lstrip, "xyzzyhelloxyzzy", "xyz");
    EQ("xyzzyhello", rstrip, "xyzzyhelloxyzzy", "xyz");
    EQ("hello", strip, "hello", "xyz");
    EQ("hello", lstrip, "hello", "xyz");
    EQ("hello", rstrip, "hello", "xyz");
    EQ("", strip, "mississippi", "mississippi");
    // # only trims the start and end, does not strip internal characters
    EQ("mississipp", strip, "mississippi", "i");
#undef EQ
}

TEST(py_builtins_str, lower) {
    ASSERT_EQ(".hello world!!!", lower(".HelLO WorlD!!!"));
}

TEST(py_builtins_str, upper) {
    ASSERT_EQ(".HELLO WORLD!!!", upper(".HelLO WorlD!!!"));
}

TEST(py_builtins_string, join) {
    ASSERT_EQ("a,b,c", string::join(",", std::vector<std::string>{"a", "b", "c"}));
}

}  // namespace

