add_library(LibraryManagementUtilsTest INTERFACE)

add_subdirectory(csv_test)
add_subdirectory(data_struct_test)

target_link_libraries(LibraryManagementUtilsTest
        INTERFACE CSVTest
        INTERFACE DataStructTest
)