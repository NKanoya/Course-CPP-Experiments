add_library(Test INTERFACE)

add_subdirectory(csv_test)

target_link_libraries(Test
        INTERFACE CSVTest
)