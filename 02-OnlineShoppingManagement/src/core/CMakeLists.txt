add_library(core INTERFACE)

add_subdirectory(collections)
add_subdirectory(amount_of_money)
add_subdirectory(customer)

target_include_directories(core
        INTERFACE ../../include
)

target_link_libraries(core
        INTERFACE collections
        INTERFACE customer
        INTERFACE purchase
)



