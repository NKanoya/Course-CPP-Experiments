add_library(core INTERFACE)

add_subdirectory(amount_of_money)

target_include_directories(core
        INTERFACE ../../include
)

target_link_libraries(core
        INTERFACE purchase
)



