add_library(DataStructTest
    data_struct_test.cpp
)

target_include_directories(DataStructTest
        PUBLIC ../../include/
        PUBLIC ../
)