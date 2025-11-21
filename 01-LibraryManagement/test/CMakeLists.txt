add_library(Test INTERFACE)

add_subdirectory(utils/csv_test)
add_subdirectory(utils/data_struct_test)
add_subdirectory(core/book_test)

target_link_libraries(Test
        INTERFACE CSVTest
        INTERFACE DataStructTest
        INTERFACE BookTest
)