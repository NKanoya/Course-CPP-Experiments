//
// Created on 2025/11/17.
//

#include "core/book.hpp"
#include "utils/csv.hpp"

std::ostream& operator<<(std::ostream& os, const BookInfo& bookInfo) {
    Utils::CSVWriter writer(BookInfo::KEYCOUNT);
    writer.addEntry(os, bookInfo.getRange());
    return os;
}

std::istream& operator>>(std::istream& is, BookInfo& bookInfo) {
    Utils::CSVReader reader(BookInfo::KEYCOUNT);
    reader.readLine(is, bookInfo.getRange());
    return is;
}

std::ostream& operator<<(std::ostream& os, const CopyInfo& copyInfo) {
    Utils::CSVWriter writer(BookInfo::KEYCOUNT);
    writer.addEntry(os, copyInfo.getRange());
    return os;
}

std::istream& operator>>(std::istream& is, CopyInfo& copyInfo) {
    Utils::CSVReader reader(BookInfo::KEYCOUNT);
    reader.readLine(is, copyInfo.getRange());
    return is;
}

