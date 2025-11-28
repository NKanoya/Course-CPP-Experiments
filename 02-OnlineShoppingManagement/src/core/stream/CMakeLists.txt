add_library(stream
        member_stream.cpp
        item_stream.cpp
        amount_of_money_stream.cpp
)

target_include_directories(stream
        PUBLIC ../../../include
)

target_link_libraries(stream
        PUBLIC customer
        PUBLIC purchase
        PUBLIC amount_of_money
)
