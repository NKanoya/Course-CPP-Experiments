//
// Created on 2025/11/16.
//

#include "core/book.hpp"

Book::Book(BookInfo info, CopyInfo copyInfo)
    : m_info(std::move(info)),
      m_copyPointers(std::move(copyInfo)) {}

Book::Book(BookInfo info, Book::CopyEntries copyInfoEntries)
    : m_info(std::move(info)),
      m_copyPointers(std::move(copyInfoEntries)) {}

Book::Book(Book &&oth) noexcept
    : m_info(std::move(oth.m_info)), m_copyPointers(std::move(oth.m_copyPointers)) {}

Book& Book::operator=(Book &&oth) noexcept {
    if(&oth == this) {
        return *this;
    }

    m_info = std::move(oth.m_info);
    m_copyPointers = std::move(oth.m_copyPointers);
    return *this;
}









