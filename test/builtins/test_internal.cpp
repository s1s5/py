/**
 * Copyright
 * @file test_internal.cpp
 * @brief
 * @author Shogo Sawai
 * @date 2019-06-19 12:03:29
 */
#include "../cpput.hpp"

#include "py/builtins/internal.hpp"

#include "../debug.hpp"

namespace {

using namespace py::internal;

TEST(py_builtins_internal, intelligent_clone) {
    {
        int x = 0;
        auto xy = tuple_intelligent_clone(x, 9, 10, 18);
        // std::cout << typeid(decltype(xy)).name() << std::endl;
        // std::cout << std::get<0>(xy) << ", " << std::get<1>(xy) << std::endl;
        ASSERT_EQ(0, std::get<0>(xy));
        ASSERT_EQ(9, std::get<1>(xy));
        std::get<0>(xy) = 3;
        std::get<1>(xy) = 4;
        ASSERT_EQ(3, std::get<0>(xy));
        ASSERT_EQ(4, std::get<1>(xy));

        ASSERT_EQ(3, x);
        // std::cout << std::get<0>(xy) << ", " << std::get<1>(xy) << std::endl;
        // std::cout << x << std::endl;
    }

    {
        int x = 0;
        auto xy = tuple_intelligent_clone(12, 13, 9, x);
        // std::cout << typeid(decltype(xy)).name() << std::endl;
        ASSERT_EQ(12, std::get<0>(xy));
        ASSERT_EQ(0, std::get<3>(xy));
        std::get<0>(xy) = 3;
        std::get<3>(xy) = 4;
        ASSERT_EQ(3, std::get<0>(xy));
        ASSERT_EQ(4, std::get<3>(xy));
        ASSERT_EQ(4, x);
    }

    {
        int x = 0, y = 1, z = 2;
        auto xy = tuple_intelligent_clone(x, 9, 4, y, 8, z);
        // std::cout << typeid(decltype(xy)).name() << std::endl;
        ASSERT_EQ(0, x);
        ASSERT_EQ(1, y);
        ASSERT_EQ(2, z);
        ASSERT_EQ(0, std::get<0>(xy));
        ASSERT_EQ(9, std::get<1>(xy));
        ASSERT_EQ(4, std::get<2>(xy));
        ASSERT_EQ(1, std::get<3>(xy));
        ASSERT_EQ(8, std::get<4>(xy));
        ASSERT_EQ(2, std::get<5>(xy));
        std::get<0>(xy) = 3;
        std::get<1>(xy) = 4;
        std::get<2>(xy) = 9;
        std::get<3>(xy) = 7;
        std::get<4>(xy) = 6;
        std::get<5>(xy) = 1;
        ASSERT_EQ(3, std::get<0>(xy));
        ASSERT_EQ(4, std::get<1>(xy));
        ASSERT_EQ(9, std::get<2>(xy));
        ASSERT_EQ(7, std::get<3>(xy));
        ASSERT_EQ(6, std::get<4>(xy));
        ASSERT_EQ(1, std::get<5>(xy));
        ASSERT_EQ(3, x);
        ASSERT_EQ(7, y);
        ASSERT_EQ(1, z);

        decltype(xy) xy0 = xy;
        std::get<0>(xy0) = 6;
        ASSERT_EQ(6, x);
    }

    {
        std::vector<int> v0{0, 1, 2, 3, 4};
        std::vector<double> v1{9, 8, 7, 6};
        auto xy = tuple_intelligent_clone(v0, v1);
        ASSERT_EQ(0, v0[0]);
        ASSERT_EQ(9, v1[0]);
        ASSERT_EQ(0, std::get<0>(xy)[0]);
        ASSERT_EQ(9, std::get<1>(xy)[0]);
        std::get<0>(xy)[0] = 9;
        std::get<1>(xy)[0] = 0;
        ASSERT_EQ(9, std::get<0>(xy)[0]);
        ASSERT_EQ(0, std::get<1>(xy)[0]);

        ASSERT_EQ(9, v0[0]);
        ASSERT_EQ(0, v1[0]);
    }

    {
        std::vector<double> v1{9, 8, 7, 6};
        auto xy = tuple_intelligent_clone(std::vector<int>{0, 1, 2, 3, 4}, v1);
        ASSERT_EQ(9, v1[0]);
        for (int i = 0; i < 4; i++) {
            std::cout << i << " : " << std::get<1>(xy)[i] << std::endl;
            ASSERT_EQ(9 - i, std::get<1>(xy)[i]);
        }
        std::cout << "size : " << std::get<0>(xy).size() << std::endl;
        ASSERT_EQ(5, std::get<0>(xy).size());
        for (int i = 0; i < 5; i++) {
            std::cout << i << " : " << std::get<0>(xy)[i] << std::endl;
            ASSERT_EQ(i, std::get<0>(xy)[i]);
        }
        ASSERT_EQ(9, std::get<1>(xy)[0]);
        std::get<0>(xy)[0] = 9;
        std::get<1>(xy)[0] = 0;
        ASSERT_EQ(9, std::get<0>(xy)[0]);
        ASSERT_EQ(0, std::get<1>(xy)[0]);

        ASSERT_EQ(0, v1[0]);
    }

    {
        std::vector<double> v1{9, 8, 7, 6};
        auto xy = tuple_intelligent_clone(v1, std::vector<int>{0, 1, 2, 3, 4});
        ASSERT_EQ(9, v1[0]);
        ASSERT_EQ(5, std::get<1>(xy).size());
        for (int i = 0; i < 5; i++) {
            ASSERT_EQ(i, std::get<1>(xy)[i]);
        }
    }
#if 0
    {
        Class x0;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        auto tmp0 = tuple_intelligent_clone(x0, Class());
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        auto tmp1 = tuple_intelligent_clone(Class(), x0);
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        std::cout << std::get<1>(tmp0).my_id << std::endl;
        std::cout << std::get<0>(tmp1).my_id << std::endl;
    }
#endif
}

}  // namespace

