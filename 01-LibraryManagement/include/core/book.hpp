//
// Created on 2025/11/16.
//

#ifndef LIBRARYMANAGEMENT_BOOK_HPP
#define LIBRARYMANAGEMENT_BOOK_HPP

#include <string>
#include <vector>
#include <memory>
#include <array>
#include "utils/data_struct.hpp"


// internal enum
namespace {
    enum class BookInfoKey_ {
        ISBN,
        TITLE,
        AUTHOR,
        PUBLISHER,
        YEAR,
        SUMMARY,
        KEY_COUNT
    };
}

using BookInfo = Utils::InfoEntry<std::string, BookInfoKey_>;

// internal enum
namespace {
    enum class CopyInfoKey_ {
        IDENTIFIER_CODE,
        ISBN,
        STATUS,
        BORROWER_CODE,
        KEY_COUNT
    };
}

using CopyInfo = Utils::InfoEntry<std::string, BookInfoKey_>;


//class Book {
//    BookInfo m_info;
//
//    CopyEntries m_copy;
//public:
//    // original Book constructor: construct an empty Book object
//    Book() : m_info() {}
//
//    Book(BookInfo info, CopyInfo copyInfo);
//    Book(BookInfo info, CopyEntries copyInfoEntries);
//
//    Book(const Book& oth) = delete;
//    Book& operator=(const Book& oth) = delete;
//
//    Book(Book&& oth) noexcept;
//    Book& operator=(Book&& oth) noexcept;
//
//    BookInfo& getInfo() noexcept;
//    const BookInfo& getInfo() const noexcept;
//
//    inline bool valid() const noexcept {
//        return !m_info[BookInfo::Key::ISBN].empty();
//    }
//
//    inline operator bool() const noexcept {
//        return !m_info[BookInfo::Key::ISBN].empty();
//    }
//
//    friend std::ostream& operator<<(std::ostream& os, Book& book) noexcept;
//    friend std::istream& operator>>(std::istream& is, Book& book) noexcept;
//};
//
//
//// interaction with streams
//
//// struct BookInfo
//std::ostream& operator<<(std::ostream& os, const BookInfo& bookInfo) noexcept;
//std::istream& operator>>(std::istream& is, BookInfo& bookInfo) noexcept;
//
//// struct CopyEntry
//std::ostream& operator<<(std::ostream& os, const CopyEntry& copyEntry) noexcept;
//std::istream& operator>>(std::istream& is, CopyEntry& copyEntry) noexcept;

#endif //LIBRARYMANAGEMENT_BOOK_HPP
