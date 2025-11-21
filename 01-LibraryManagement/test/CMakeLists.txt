add_library(Test INTERFACE)

add_subdirectory(csv_test)
add_subdirectory(data_struct_test)
add_subdirectory(book_test)

target_link_libraries(Test
        INTERFACE CSVTest
        INTERFACE DataStructTest
        INTERFACE BookTest
)