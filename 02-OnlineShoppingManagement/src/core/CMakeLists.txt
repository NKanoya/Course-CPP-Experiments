add_library(core INTERFACE)

add_subdirectory(collections)
add_subdirectory(amount_of_money)
add_subdirectory(customer)
add_subdirectory(purchase)
add_subdirectory(shop)
add_subdirectory(stream)

target_include_directories(core
        INTERFACE ../../include
)

target_link_libraries(core
        INTERFACE collections
        INTERFACE amount_of_money
        INTERFACE customer
        INTERFACE purchase
        INTERFACE shop
        INTERFACE stream
)



