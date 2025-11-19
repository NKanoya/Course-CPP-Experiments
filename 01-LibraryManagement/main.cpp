//
// Created on 2025/11/16.
//

#include <iostream>
#include "core/book.hpp"
#include "utils/csv.hpp"

#include "test.hpp"

int main() {
    Test::CSVWriterTest();
    Test::csvReaderTest();

    std::cout << std::endl;
    return 0;
}