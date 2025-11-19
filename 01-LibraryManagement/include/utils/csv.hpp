//
// Created on 2025/11/17.
//

#ifndef LIBRARYMANAGEMENT_CSV_HPP
#define LIBRARYMANAGEMENT_CSV_HPP

#include <cinttypes>
#include <vector>
#include <string>
#include <iostream>
#include "utils/data_struct.hpp"


namespace Utils {

    class CSVWriter {
        std::vector<std::string> m_keys;
        std::size_t m_cols;
    public:
        explicit CSVWriter(std::size_t columnCount);
        explicit CSVWriter(std::vector<std::string> m_keys);

        CSVWriter(const CSVWriter& oth) = delete;
        CSVWriter& operator=(const CSVWriter& oth) = delete;
        CSVWriter(CSVWriter&& oth) = delete;
        CSVWriter& operator=(CSVWriter&& oth) = delete;

        using StringsRange = Utils::PointerRange<std::string>;

        void writeHeader(std::ostream& os) const;
        bool addEntry(std::ostream& os, StringsRange contents) const;

        bool newKeys(StringsRange keys) noexcept;
        const std::vector<std::string>& readKeys() const noexcept { return m_keys; }
        inline const std::size_t& readColumnCount() const noexcept { return m_cols; }
    };

    class CSVReader {
        std::size_t m_cols;
    public:
        explicit CSVReader(std::size_t columnCount) : m_cols(columnCount) {}
        explicit CSVReader(std::istream& is);
        explicit CSVReader(const CSVWriter& writer);

        CSVReader(const CSVReader& oth) = delete;
        CSVReader& operator=(const CSVReader& oth) = delete;
        CSVReader(CSVReader&& oth) = delete;
        CSVReader& operator=(CSVReader&& oth) = delete;

        using StringsRange = Utils::PointerRange<std::string>;

        bool readLine(std::istream &is, StringsRange inputList) const;

        inline bool valid() const noexcept {
            return m_cols;
        }

        inline operator bool() const noexcept {
            return m_cols;
        }

        inline std::size_t& getColumnCount() noexcept { return m_cols; }
        inline const std::size_t& readColumnCount() const noexcept { return m_cols; }

    };

    enum class ReadState {
        inQuotation,                // between quotation marks
        lookingForComma,            // after the ending quotation mark, looking for next comma
        lookingForQuotation         // after the comma, looking for next beginning quotation mark
    };




}


#endif //LIBRARYMANAGEMENT_CSV_HPP
