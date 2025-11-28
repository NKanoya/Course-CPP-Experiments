add_library(collections
        item_collection.cpp
        member_collection.cpp
        purchase_collection.cpp
)

target_include_directories(collections
        PUBLIC ../../../include
)

target_link_libraries(collections
        PUBLIC amount_of_money
)