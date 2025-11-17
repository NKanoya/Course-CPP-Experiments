add_library(CSVTest
    csv_test.cpp
)

target_include_directories(CSVTest
        PUBLIC ../../include
        PUBLIC ../
)

target_link_libraries(CSVTest
        PUBLIC CSVParserCore
)