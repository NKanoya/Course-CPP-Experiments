cmake_minimum_required(VERSION 3.29)
project(online_shopping_management)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/core)
add_subdirectory(src/utils)
add_subdirectory(test)

add_executable(online_shopping_management
        main.cpp
)


target_include_directories(online_shopping_management
        PUBLIC include
        PUBLIC test
)

target_link_libraries(online_shopping_management
        PUBLIC core
        PUBLIC utils
        PUBLIC test
)




