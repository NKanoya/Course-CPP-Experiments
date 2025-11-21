add_library(Test INTERFACE)

add_subdirectory(utils)
add_subdirectory(core)

target_link_libraries(Test
        INTERFACE LibraryManagementCoreTest
        INTERFACE LibraryManagementUtilsTest
)