//
// Created on 2025/11/17.
//

#include "core/book.hpp"
#include "Utils/csv.hpp"

std::ostream& operator<<(std::ostream& os, BookInfo& bookInfo) noexcept {
    Utils::CSVWriter writer(bookInfo.KEYCOUNT);

    writer.addEntry(os, bookInfo.getRange());
}



std::istream& operator>>(std::istream& is, BookInfo& bookInfo) noexcept {
    Utils::CSVReader reader(bookInfo.KEYCOUNT);

    reader.readLine(is, bookInfo.getRange());
}


//std::ostream& operator<<(std::ostream& os, const CopyEntry& copyEntry) noexcept {
//
//}
//
//std::istream& operator>>(std::istream& is, CopyEntry& copyEntry) noexcept {
//
//}

