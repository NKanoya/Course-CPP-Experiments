//
// Created on 2025/11/16.
//

#include "core/book.hpp"

BookInfo::BookInfo(Utils::EntryRange range) {
    if(range.size() != keyCount) {
        m_info[0] = "";
        return;
    }
    // use the contents in the range to initialize the infomation array
    for(int i = 0; i < keyCount; ++i) {
        m_info[i] = *(range.begin + i);
    }
}

const std::string &BookInfo::operator[](BookInfo::BookInfoKeys key) {
    switch (key) {
        case BookInfoKeys::ISBN:        return m_info[0];
        case BookInfoKeys::title:       return m_info[1];
        case BookInfoKeys::author:      return m_info[2];
        case BookInfoKeys::publisher:   return m_info[3];
        case BookInfoKeys::year:        return m_info[4];
        case BookInfoKeys::summary:     return m_info[5];
        default:                        return "";
    }
}

Utils::EntryRange BookInfo::getRange() const {
    return Utils::EntryRange(m_info);
}


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



