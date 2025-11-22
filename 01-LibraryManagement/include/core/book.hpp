//
// Created on 2025/11/16.
//

#ifndef LIBRARYMANAGEMENT_BOOK_HPP
#define LIBRARYMANAGEMENT_BOOK_HPP

#include <string>
#include <vector>
#include <memory>
#include <array>
#include "core/core_types.hpp"
#include "core/record_collection.hpp"


// internal enum
namespace Impl {
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

using BookInfo = StringEntry<Impl::BookInfoKey_>;

using BookCollection = RecordCollection<Impl::BookInfoKey_>;

// internal enum
namespace Impl {
    enum class CopyInfoKey_ {
        IDENTIFIER_CODE,
        ISBN,
        STATUS,
        BORROWER_CODE,
        KEY_COUNT
    };
}

using CopyInfo = StringEntry<Impl::CopyInfoKey_>;

using CopyCollection = RecordCollection<Impl::CopyInfoKey_>;


class Book {
    using CopyEntries = std::vector<std::unique_ptr<CopyInfo>>;
    BookInfo m_info;

    CopyEntries m_copyPointers;
public:
    // original Book constructor: construct an empty Book object
    Book() : m_info(), m_copyPointers() {}

    Book(BookInfo info, CopyInfo copyInfo);
    Book(BookInfo info, CopyEntries copyInfoEntries);

    Book(const Book& oth) = delete;
    Book& operator=(const Book& oth) = delete;

    Book(Book&& oth) noexcept;
    Book& operator=(Book&& oth) noexcept;

    inline BookInfo& setInfo() noexcept {
        return m_info;
    }

    const BookInfo& readInfo() const noexcept {
        return m_info;
    }

    inline bool valid() const noexcept {
        return m_info.valid() && !m_copyPointers.empty();
    }

    inline operator bool() const noexcept {
        return m_info.valid() && !m_copyPointers.empty();
    }

    inline std::size_t copyCount() const noexcept {
        return m_copyPointers.size();
    }

    friend std::ostream& operator<<(std::ostream& os, Book& book) noexcept;
    friend std::istream& operator>>(std::istream& is, Book& book) noexcept;
};


// interaction with streams

// struct BookInfo
std::ostream& operator<<(std::ostream& os, const BookInfo& bookInfo);
std::istream& operator>>(std::istream& is, BookInfo& bookInfo);

// struct CopyEntry
std::ostream& operator<<(std::ostream& os, const CopyInfo& copyEntry);
std::istream& operator>>(std::istream& is, CopyInfo& copyEntry);


#endif //LIBRARYMANAGEMENT_BOOK_HPP
