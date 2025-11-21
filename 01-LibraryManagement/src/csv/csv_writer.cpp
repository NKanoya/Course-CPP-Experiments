//
// Created on 2025/11/17.
//

#include "utils/csv.hpp"
#include <iostream>

namespace Utils {
    CSVWriter::CSVWriter(std::size_t columnCount) : m_cols(columnCount), m_keys(columnCount) {
        for(int i = 0; i < m_cols; ++i) {
            m_keys[i] = std::to_string(i);
        }
    }

    CSVWriter::CSVWriter(std::vector<std::string> keys)
            : m_keys(std::move(keys)), m_cols(m_keys.size()) {}

    void CSVWriter::writeHeader(std::ostream &os) const {
        for (int i = 0; i < m_cols; i++) {
            os << m_keys[i];
            if (i != m_cols - 1) {
                os << ",";
            }
        }
        os << '\n';
    }

    static void outputEscapeString(std::ostream &os,
                                   CSVWriter::StringsRange& contents,
                                   const std::string* endIt) {
        // traverse assigned strings
        for (auto it = contents.p_begin; it != endIt; ++it) {
            os << '"';                 // beginning quotation mark
            for (auto &ch: *it) {
                if (ch == '\"') {
                    os << "\"\"";       // escape `"` as `""`
                } else {
                    os << ch;           // copy the original string
                }
            }

            os << '"';                 // ending quotation mark

            if (it + 1 != endIt) {
                os << ',';             // separating comma
            }
        }
    }

    bool CSVWriter::addEntry(std::ostream &os, StringsRange contents) const {
        auto endIt = contents.p_end;
        if (contents.size() >= m_cols) {
            endIt = contents.p_begin + m_cols;
            outputEscapeString(os, contents, endIt);
        } else {
            std::size_t absentColumnNumber = m_cols - contents.size();
            outputEscapeString(os, contents, endIt);
            for (int i = 0; i < absentColumnNumber; ++i) {
                os << ",\"\"";
            }

        }

        os << '\n';
        return (bool) os;
    }

    bool CSVWriter::newKeys(StringsRange keys) noexcept {
        // incompatible count of keys
        if(keys.size() == m_cols) {
            return false;
        }

        for(auto i = 0; i < m_cols; ++i) {
            m_keys[i] = keys.p_begin[i];
        }
        m_cols = m_keys.size();

        return true;
    }

}

