# python like header-only c++ lirary

# how to use
## prerequisite
- add include path `/include`
- add following line `#include <py/py.hpp>`

``` c++
std::vector<int> v0{0, 1, 2, 3};

// ---------- enumerate ----------
for (auto &&[i, j] : py::enumerate(v0)) {
    std::cout << i << ", " << j << std::endl;  // (0, 0), (1, 1), ...
}

// ---------- map ----------
for (auto &&i : py::map([](auto e) { return e + 10; }, v0)) {
    std::cout << i << std::endl;  // 10, 11, ...
}

// ---------- zip ----------
for (auto &&[i, j] : py::zip(v0, v0)) {
    std::cout << i << ", " << j << std::endl;  // (0, 0), (1, 1), ...
}
```

# todos
- [builtins](/include/py/builtins/readme.md)
