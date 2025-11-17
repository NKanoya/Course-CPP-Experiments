cmake_minimum_required(VERSION 3.29)
project(LibraryManagement)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/book)
add_subdirectory(src/csv)

add_executable(LibraryManagement
    main.cpp
)

target_link_libraries(LibraryManagement
        PUBLIC Book
        PUBLIC CSVParserCore
)

target_include_directories(LibraryManagement
    PUBLIC include/
)