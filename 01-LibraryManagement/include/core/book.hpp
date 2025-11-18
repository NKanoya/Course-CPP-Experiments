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

class BookInfo {
public:
    enum class BookInfoKeys {
        ISBN,
        title,
        author,
        publisher,
        year,
        summary,
        keyCount_
    };
    static constexpr std::size_t keyCount = static_cast<std::size_t>(BookInfoKeys::keyCount_);
private:
    using InfoArrays = std::array<std::string, keyCount>;
    InfoArrays m_info;
public:
    BookInfo(Utils::EntryRange range);

    const std::string& operator[](BookInfoKeys key);
    Utils::EntryRange getRange() const;

};

enum class CopyStatus {
    available,
    borrowed,
    onLoan
};

struct CopyInfo {
    std::string innerNumber;
    // TODO: fill me
};

using CopyEntry = std::unique_ptr<CopyInfo>;
using CopyEntries = std::vector<CopyEntry>;


class Book {
    BookInfo m_info;

    CopyEntries m_copy;
public:
    // original Book constructor: construct an empty Book object
    Book() : m_info({{},{},{},{}, {}, {}}) {}

    Book(BookInfo info, CopyInfo copyInfo);
    Book(BookInfo info, CopyEntries copyInfoEntries);

    Book(const Book& oth) = delete;
    Book& operator=(const Book& oth) = delete;

    Book(Book&& oth) noexcept;
    Book& operator=(Book&& oth) noexcept;

    BookInfo& getInfo() noexcept;
    const BookInfo& getInfo() const noexcept;

    inline bool valid() const noexcept {
        return !m_info.ISBN.empty();
    }

    inline operator bool() const noexcept {
        return !m_info.ISBN.empty();
    }

    friend std::ostream& operator<<(std::ostream& os, Book& book) noexcept;
    friend std::istream& operator>>(std::istream& is, Book& book) noexcept;
};


// interaction with streams

// struct BookInfo
std::ostream& operator<<(std::ostream& os, const BookInfo& bookInfo) noexcept;
std::istream& operator>>(std::istream& is, BookInfo& bookInfo) noexcept;

// struct CopyEntry
std::ostream& operator<<(std::ostream& os, const CopyEntry& copyEntry) noexcept;
std::istream& operator>>(std::istream& is, CopyEntry& copyEntry) noexcept;

#endif //LIBRARYMANAGEMENT_BOOK_HPP
