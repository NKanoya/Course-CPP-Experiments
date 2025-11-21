add_library(BookTest
    book_test.cpp
)

target_include_directories(BookTest
        PUBLIC ../../include/
        PUBLIC ../
)

target_link_libraries(BookTest
        PUBLIC Book
)