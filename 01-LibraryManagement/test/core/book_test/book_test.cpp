//
// Created on 2025/11/21.
//

#include "test.hpp"
#include "core/book.hpp"
#include <sstream>

void Test::bookStreamTest() {

    BookInfo bookInfo = {"978-7-1234-1234-1", "Sample Name", "John Doe", "Sample Press", "2025", "Sample Summary"};
    std::cout << "Validity: " << bookInfo.valid() << std::endl;

    std::cout << "Output BookInfo object: ";
    std::cout << bookInfo << '\n';

    std::string inputString = R"("978-7-1234-1234-1","Sample Name","John Doe","Sample Press","2025","Sample Summary")";
    std::cout << "Input BookInfo object from a string:" << inputString << '\n';
    std::stringstream ss(inputString);
    std::cout << "Output BookInfo object: ";
    ss >> bookInfo;
    if(bookInfo.valid())
        std::cout << bookInfo << '\n';



}