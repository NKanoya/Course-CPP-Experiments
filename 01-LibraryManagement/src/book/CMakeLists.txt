add_library(Book
    book.cpp
    book_stream.cpp
)

target_include_directories(Book
    PRIVATE ../../include/
)