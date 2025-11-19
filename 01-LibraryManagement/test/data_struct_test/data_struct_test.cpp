//
// Created on 2025/11/19.
//

#include "test.hpp"
#include "utils/data_struct.hpp"
#include <string>
#include <iostream>
#include <array>

using namespace Test;
using namespace Utils;

void Test::infoEntryTest() {

    enum class TempEnum {
        MAIN_KEY,
        PROPERTY_1,
        PROPERTY_2,
        COUNT
    };

    using TestedEntry = InfoEntry<std::string, TempEnum>;

    //////////////////////////////////////////////////////////////////
    std::cout << Test::separation;
    std::cout << "Create a normal entry object obj1:\n";

    std::array<std::string, TestedEntry::KEYCOUNT> strings = {"Main", "Value1", "Value2"};
    PointerRange<std::string> range(strings);          // create a pointer range for the valuearray

    // create a through string
    TestedEntry obj1(range);
    std::cout << "Is obj1 valid: " << obj1.valid() << '\n';

    std::cout << "MAIN_KEY \t| " << obj1[TestedEntry::Key::MAIN_KEY] << '\n';
    std::cout << "PROPERTY_1 \t| " << obj1[TestedEntry::Key::PROPERTY_1] << '\n';
    std::cout << "PROPERTY_2 \t| " << obj1[TestedEntry::Key::PROPERTY_2] << '\n';

    std::cout << "elements:\n";
    strings[0] = "New Main Key";
    strings[1] = "New Value1";
    strings[2] = "New Value2";


    //////////////////////////////////////////////////////////////////
    std::cout << Test::separation;
    std::cout << "Use move semantics to create an entry object obj2:\n";

    // create a entry using move tag
    TestedEntry obj2(range, TestedEntry::UseMoveTag{});
    std::cout << "Is obj2 valid: " << obj2.valid() << '\n';

    std::cout << "elements:\n";
    std::cout << "MAIN_KEY \t| " << obj2[TestedEntry::Key::MAIN_KEY] << '\n';
    std::cout << "PROPERTY_1 \t| " << obj2[TestedEntry::Key::PROPERTY_1] << '\n';
    std::cout << "PROPERTY_2 \t| " << obj2[TestedEntry::Key::PROPERTY_2] << '\n';
    std::cout << strings[0] << '\n';

    std::cout << "Check if the original strings are moved: " << strings[0].empty() << '\n';

    //////////////////////////////////////////////////////////////////
    std::cout << Test::separation;
    std::cout << "Get the inner range of an entry, and use it to traverse the entry:\n\n";

    auto obj2Range = obj2.getRange();

    for(int i = 0; i < obj2Range.size(); ++i) {
        std::cout << i << "  | " << obj2Range.begin[i] << "\n";
    }

    //////////////////////////////////////////////////////////////////
    std::cout << Test::separation;

    std::cout << "Test if the out of range execption from `at()` method is correctly thrown:";
    std::cout << std::endl;

    try {
        obj2.at(TestedEntry::Key::COUNT);
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

    try {
        obj2.at(static_cast<TestedEntry::Key>(100));
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

    //////////////////////////////////////////////////////////////////
    std::cout << Test::separation;
    std::cout << "Use incompatible size (too few elements) of range to create object obj3:\n";

    std::array<std::string, 2> too_few_strings = {"Main", "Value1"};
    PointerRange<std::string> range_too_few(too_few_strings);          // create a pointer range for the valuearray
    TestedEntry obj3(range_too_few);
    std::cout << "Is obj3 valid: " << obj3.valid() << '\n';

    //////////////////////////////////////////////////////////////////
    std::cout << Test::separation;
    std::cout << "Use incompatible size (too few elements) of range to create Object obj4:\n";

    std::array<std::string, 4> too_many_strings = {"Main", "Value1"};
    PointerRange<std::string> range_too_many(too_many_strings);          // create a pointer range for the valuearray
    TestedEntry obj4(range_too_many);
    std::cout << "Is obj4 valid: " << obj4.valid() << '\n';





}