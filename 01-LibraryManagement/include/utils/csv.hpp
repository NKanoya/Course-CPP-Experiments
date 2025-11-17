//
// Created on 2025/11/17.
//

#ifndef LIBRARYMANAGEMENT_CSV_HPP
#define LIBRARYMANAGEMENT_CSV_HPP

#include <cinttypes>
#include <vector>
#include <string>


class CSVParser {
    std::vector<std::string> m_keys;
    unsigned int m_cols;
public:
    explicit CSVParser(std::vector<std::string> m_keys);

    CSVParser(const CSVParser& oth) = delete;
    CSVParser& operator=(const CSVParser& oth) = delete;
    CSVParser(CSVParser&& oth) = delete;
    CSVParser& operator=(CSVParser&& oth) = delete;

    void writeHeader(std::ostream& os) const;
    bool addEntry(std::ostream& os, const std::vector<std::string>& contents) const;

    inline unsigned int rowCount() const noexcept { return m_cols; }
};

#endif //LIBRARYMANAGEMENT_CSV_HPP
