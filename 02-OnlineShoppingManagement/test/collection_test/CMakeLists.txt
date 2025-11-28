add_library(collection_test
        test_purchase_collection.cpp
)

target_include_directories(collection_test
        PUBLIC ../../include
        PUBLIC ../
)

target_link_libraries(collection_test
        PUBLIC purchase
        PUBLIC collections
        PUBLIC amount_of_money
)