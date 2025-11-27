add_library(utils INTERFACE)

add_subdirectory(rapidcsv)

target_include_directories(utils
        INTERFACE ../../include
)

target_link_libraries(utils
        INTERFACE rapidcsv
)



