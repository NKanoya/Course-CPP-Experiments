add_library(customer
        member.cpp
)

target_include_directories(customer
        PUBLIC ../../../include
)
