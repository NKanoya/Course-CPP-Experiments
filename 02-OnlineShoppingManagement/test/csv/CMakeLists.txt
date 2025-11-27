add_library(test_csv
        test_csv.cpp
)

target_include_directories(test_csv
        PUBLIC ../../include
        PUBLIC ../
)

target_link_libraries(test_csv
        PUBLIC amount_of_money
)
