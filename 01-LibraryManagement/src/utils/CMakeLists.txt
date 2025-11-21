add_library(LibraryManagementUtils INTERFACE)

add_subdirectory(csv)

target_link_libraries(LibraryManagementUtils
        INTERFACE CSVParser
)