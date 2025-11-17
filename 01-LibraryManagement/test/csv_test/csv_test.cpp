//
// Created on 2025/11/17.
//

#include "test.hpp"
#include "utils/csv.hpp"
#include <iostream>

namespace Test {

    void csvTest() {
        // list of keys
        std::vector<std::string> keys = {"ISBN", "Title", "Author", "Publisher", "Year", "Summary"};
        // use the keys to construct a CSV Parser
        CSVParser parser(keys);

        // output the column count
        std::cout << "Column:" << parser.columnCount() << '\n';

        // output the header
        parser.writeHeader(std::cout);

        // output a normal list
        std::vector<std::string> list1 = {"123",
                                          "Sample Title",
                                          "John Doe",
                                          "Sample Press",
                                          "2025",
                                          "Sample Summary with \"Quotation Marks\" and comma \",\"!"};
        parser.addEntry(std::cout, list1);

        // output a list with inadequate columns
        std::vector<std::string> list2 = {"123",
                                          "Lack Columns"};
        parser.addEntry(std::cout, list2);

        // output a list with too many columns
        std::vector<std::string> list3 = {"123",
                                          "Sample Title",
                                          "John Doe",
                                          "Sample Press",
                                          "2025",
                                          "Sample Summary with \"Quotation Marks\" and comma \",\"!",
                                          "Additional Columns"};
        parser.addEntry(std::cout, list3);
    }

}