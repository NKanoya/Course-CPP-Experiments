cmake_minimum_required(VERSION 3.29)
project(GrayScaleImage)

set(CMAKE_CXX_STANDARD 20)

set(OpenCV_DIR "D:/Libraries/mixed/opencv/build_mingw/install")
find_package(OpenCV REQUIRED COMPONENTS imgcodecs core)

add_executable(GrayScaleImage
        main.cpp
        src/imread.cpp
        src/image.cpp
)

set_target_properties(GrayScaleImage PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/exe"
)

target_include_directories(GrayScaleImage
        PUBLIC include/
        PRIVATE ${OpenCV_INCLUDE_DIRS}
)


target_link_libraries(GrayScaleImage ${OpenCV_LIBS})



