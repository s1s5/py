/**
 * Copyright
 * @file internal.hpp
 * @brief
 * @author Shogo Sawai
 * @date 2019-06-19 10:31:10
 */
#ifndef PY_INTERNAL_HPP_
#define PY_INTERNAL_HPP_

#include <tuple>

namespace py::internal {

template <int N>
struct TupleUtil {
    template <typename F, typename Tuple, typename... Args>
    static auto apply_iterators(F &f, Tuple& t, Args&... args) {
        return TupleUtil<N - 1>::apply_iterators(f, t, std::get<N - 1>(t), args...);
    }
    template <typename Tuple, typename... Args>
    static auto deref(Tuple& t, Args&... args) {
        return TupleUtil<N - 1>::deref(t, std::get<N - 1>(t), args...);
    }
    template <typename Tuple, typename... Args>
    static auto begin(Tuple& t, Args&... args) {
        return TupleUtil<N - 1>::begin(t, std::get<N - 1>(t), args...);
    }
    template <typename Tuple, typename... Args>
    static auto end(Tuple& t, Args&... args) {
        return TupleUtil<N - 1>::end(t, std::get<N - 1>(t), args...);
    }
    template <typename Tuple, typename... Args>
    static void pincrement(Tuple& t, Args&... args) {
        ++std::get<N - 1>(t);
        TupleUtil<N - 1>::pincrement(t, std::get<N - 1>(t), args...);
    }

    template <typename Tuple>
    static bool tuple_equal_or(Tuple& lhs, Tuple& rhs) {
        return (std::get<N - 1>(lhs) == std::get<N - 1>(rhs)) or
            TupleUtil<N - 1>::tuple_equal_or(lhs, rhs);
    }

    // template<typename Tuple, typename ... Args>
    // static auto intelligent_clone(Tuple &t, Args ... args) {
    //     using type = decltype(std::get<N - 1>(t));
    //     if constexpr (std::is_rvalue_reference<type>::value) {
    //         return TupleUtil<N - 1>::intelligent_clone(t, (typename std::remove_reference<type>::type)std::get<N - 1>(t), args...);
    //     } else {
    //         return TupleUtil<N - 1>::intelligent_clone(t, std::get<N - 1>(t), args...);
    //     }
    // }
};

template <>
struct TupleUtil<0> {
    template <typename F, typename Tuple, typename... Args>
    static auto apply_iterators(F &f, Tuple & t, Args&... args) {
        return f(*args...);
    }

    template <typename Tuple, typename... Args>
    static auto deref(Tuple& t, Args&... args) {
        return std::tie(*args...);  // create reference
    }

    template <typename Tuple, typename... Args>
    static auto begin(Tuple& t, Args&... args) {
        return std::make_tuple(args.begin()...);  // create copy
    }

    template <typename Tuple, typename... Args>
    static auto end(Tuple& t, Args&... args) {
        return std::make_tuple(args.end()...);
    }

    template <typename Tuple, typename... Args>
    static void pincrement(Tuple& t, Args&... args) {
    }

    template <typename Tuple>
    static bool tuple_equal_or(Tuple& lhs, Tuple& rhs) {
        return false;
    }

    // template<typename Tuple, typename ... Args>
    // static auto intelligent_clone(Tuple &t, Args ... args) {
    //     return std::make_tuple(args...);
    // }
};

template <typename F, typename Tuple>
auto tuple_apply_iterators(F &f, Tuple& t) {
    return TupleUtil<std::tuple_size<Tuple>::value>::apply_iterators(f, t);
}

template <typename Tuple>
auto tuple_deref(Tuple& t) {
    return TupleUtil<std::tuple_size<Tuple>::value>::deref(t);
}

template <typename Tuple>
auto tuple_begin(Tuple& t) {
    return TupleUtil<std::tuple_size<Tuple>::value>::begin(t);
}

template <typename Tuple>
auto tuple_end(Tuple& t) {
    return TupleUtil<std::tuple_size<Tuple>::value>::end(t);
}

template <typename Tuple>
auto tuple_pincrement(Tuple& t) {
    return TupleUtil<std::tuple_size<Tuple>::value>::pincrement(t);
}

template <typename Tuple>
auto tuple_equal_or(Tuple& lhs, Tuple& rhs) {
    return TupleUtil<std::tuple_size<Tuple>::value>::tuple_equal_or(lhs, rhs);
}

// template <typename Tuple>
// auto tuple_intelligent_clone(Tuple& t) {
//     return TupleUtil<std::tuple_size<Tuple>::value>::intelligent_clone(t);
// }
#if 0
template <typename Arg>
auto tuple_intelligent_clone(Arg &arg) {
    return std::tie(arg);
}

template <typename Arg>
auto tuple_intelligent_clone(Arg &&arg) {
    return std::make_tuple(arg);
}

template <typename Arg, typename ...Args>
auto tuple_intelligent_clone(Arg &&arg, Args&&...args) {
    return std::tuple_cat(std::make_tuple(arg), tuple_intelligent_clone(std::forward<Args>(args)...));
}

template <typename Arg, typename ...Args>
auto tuple_intelligent_clone(Arg &arg, Args&&...args) {
    return std::tuple_cat(std::tie(arg), tuple_intelligent_clone(std::forward<Args>(args)...));
}
#else

template <typename Arg>
auto tuple_intelligent_forward(Arg &arg) {
    if constexpr (std::is_lvalue_reference<Arg>::value) {
        return std::tie(arg);
    } else {
        return std::make_tuple(arg);
    }
    // std::cout << "lvalue reference " << arg.size() << ", " << std::is_rvalue_reference<Arg>::value << ", " << std::is_lvalue_reference<Arg>::value << std::endl;
    // return arg;
}

// template <typename Arg>
// auto tuple_intelligent_forward(Arg &&arg) {
//     std::cout << "rvalue reference " << arg.size() << std::endl;
//     return (typename std::remove_reference<Arg>::type)arg;
//     // return arg;
// }

template <typename ...Args>
auto tuple_intelligent_clone(Args&&...args) {
    // return std::tie(tuple_intelligent_forward<Args>(args)...);
    return std::tuple_cat(tuple_intelligent_forward<Args>(args)...);
}
#endif

}  // namespace py::internal

#endif  // PY_INTERNAL_HPP_
