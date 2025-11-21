add_library(LibraryManagementCore INTERFACE)

add_subdirectory(book)

target_link_libraries(LibraryManagementCore
    INTERFACE Book
)