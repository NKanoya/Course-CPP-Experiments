add_library(LibraryManagementCoreTest INTERFACE)

add_subdirectory(book_test)

target_link_libraries(LibraryManagementCoreTest
    INTERFACE BookTest
)