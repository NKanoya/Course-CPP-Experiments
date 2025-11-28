add_library(test INTERFACE)

add_subdirectory(csv)
add_subdirectory(collection_test)

target_include_directories(test
        INTERFACE ../test
        INTERFACE ../include
)

target_link_libraries(test
        INTERFACE test_csv
        INTERFACE collection_test
)