add_library(Book
        book.cpp
        book_stream.cpp
)

target_include_directories(Book
    PUBLIC ../../../include
)

target_link_libraries(Book
    PUBLIC CSVParser
)