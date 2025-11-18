add_library(CSVParser
        csv_writer.cpp
        csv_reader.cpp
)

target_include_directories(CSVParser
    PUBLIC ../../include/
)