//
// Created on 2025/11/17.
//

#include "test.hpp"
#include "utils/csv.hpp"
#include "utils/data_struct.hpp"
#include <iostream>
#include <sstream>
#include <array>

namespace Test {

    using namespace Utils;

    void CSVWriterTest() {
        // list of keys
        std::vector<std::string> keys = {"ISBN", "Title", "Author", "Publisher", "Year", "Summary"};
        // use the keys to construct a CSV Parser
        CSVWriter parser(keys);

        // output the column count
        std::cout << "Column:" << parser.readColumnCount() << '\n';

        // output the header
        parser.writeHeader(std::cout);

        // output a normal list
        std::vector<std::string> list1 = {"123",
                                          "Sample Title",
                                          "John Doe",
                                          "Sample Press",
                                          "2025",
                                          "Sample Summary with \"Quotation Marks\" and comma \",\"!"};

        parser.addEntry(std::cout, Utils::makePointerRange(list1));

        // output a list with inadequate columns
        std::vector<std::string> list2 = {"123",
                                          "Lack Columns"};
        parser.addEntry(std::cout, Utils::makePointerRange(list2));

        // output a list with too many columns
        std::vector<std::string> list3 = {"123",
                                          "Sample Title",
                                          "John Doe",
                                          "Sample Press",
                                          "2025",
                                          "Sample Summary with \"Quotation Marks\" and comma \",\"!",
                                          "Additional Columns"};
        parser.addEntry(std::cout, Utils::makePointerRange(list3));
    }

    static void printStringArray(const std::array<std::string, 5>& arr) {
        for(int i = 0; i < 5; ++i) {
            std::cout << "string " << i << " \t| ";
            std::cout << arr[i] << "\n";
        }
    }


    void csvReaderTest() {

        std::array<std::string, 5> arr = {};        // string vector

        CSVReader reader(5);      // construct reader line
        bool readingState;

        ///////////////////////////////////////////////////////////////////////
        // test1: read a normal list of 5 columns
        std::string line1 = R"("str1","str2","str3","str4","str5")";       // raw line
        std::stringstream ss1(line1);                                  // add the line into a stream

        std::cout << separation << "Test 2: Parsing [" << line1 << "]" << std::endl;

        readingState = reader.readLine(ss1, Utils::makePointerRange(arr));         // read the line from the stream

        std::cout << "Reading State: " << readingState << '\n';         // output reading state
        std::cout << "Parsed result strings:\n";
        // print the parsing results
        printStringArray(arr);

        ///////////////////////////////////////////////////////////////////////
        // test2: read a list with escaped `""` or comma `,` in the quotation
        std::string line2 = R"("Comma,Comma","""EscapedComma""","Empty","","")";
        std::stringstream ss2(line2);
        std::cout << separation << "Test 2: Parsing [" << line2 << "]" << std::endl;

        readingState = reader.readLine(ss2, Utils::makePointerRange(arr));

        std::cout << "Reading State: " << readingState << '\n';
        // print the parsing results
        printStringArray(arr);

    };

}