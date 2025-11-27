cmake_minimum_required(VERSION 3.29)
project(online_shopping_management)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/utils)

add_executable(online_shopping_management
        main.cpp
)


        PUBLIC include/
        PUBLIC include
)
target_link_libraries(online_shopping_management
        PUBLIC core
        PUBLIC utils
)




