//
// Created on 2025/11/16.
//

#include "core/book.hpp"

Book::Book(Book &&oth) noexcept : m_info(std::move(oth.m_info)) {}

Book &Book::operator=(Book &&oth) noexcept {
    if(&oth == this) {
        return *this;
    }
    m_info = std::move(oth.m_info);
    return *this;
}

Book::Book(BookInfo bookInfo, CopyInfo copyInfo)
    : m_info(std::move(bookInfo)) {
    m_copy.reserve(1);     // reserve space for 1 copy entry
    m_copy.push_back(std::make_unique<CopyInfo>(std::move(copyInfo)));   // store the entry
}

Book::Book(BookInfo bookInfo, CopyEntries copyInfoEntries)
    : m_info(std::move(bookInfo)),
      m_copy(std::move(copyInfoEntries)) {}






