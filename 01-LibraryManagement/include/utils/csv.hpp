//
// Created on 2025/11/17.
//

#ifndef LIBRARYMANAGEMENT_CSV_HPP
#define LIBRARYMANAGEMENT_CSV_HPP

#include <cinttypes>
#include <vector>
#include <string>
#include <iostream>


namespace Utils {

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

        inline unsigned int columnCount() const noexcept { return m_cols; }
    };

    class CSVReader {
        std::size_t m_cols;
    public:
        CSVReader(std::size_t columnCount) : m_cols(columnCount) {}
        CSVReader(std::istream& is);

        CSVReader(const CSVReader& oth) = delete;
        CSVReader& operator=(const CSVReader& oth) = delete;
        CSVReader(CSVReader&& oth) = delete;
        CSVReader& operator=(CSVReader&& oth) = delete;

        bool readLine(std::istream &is, const std::vector<std::string *> &inputList);

        inline bool valid() const noexcept {
            return m_cols;
        }

        inline operator bool() const noexcept {
            return m_cols;
        }

    };

    enum class ReadState {
        inQuotation,                // between quotation marks
        lookingForComma,            // after the ending quotation mark, looking for next comma
        lookingForQuotation         // after the comma, looking for next beginning quotation mark
    };




}


#endif //LIBRARYMANAGEMENT_CSV_HPP
