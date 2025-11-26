cmake_minimum_required(VERSION 3.29)
project(OnlineShoppingManagement)

set(CMAKE_CXX_STANDARD 20)


add_executable(OnlineShoppingManagement
        main.cpp
)


target_include_directories(OnlineShoppingManagement
        PUBLIC include/
)




