add_library(stream_test
        test_stream.cpp
)

target_include_directories(stream_test
        PUBLIC ../../include
        PUBLIC ../
)

target_link_libraries(stream_test
        PUBLIC purchase
        PUBLIC collections
        PUBLIC amount_of_money
        PUBLIC stream
)