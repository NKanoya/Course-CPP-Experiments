//
// Created on 2025/11/17.
//

#include "utils/csv.hpp"
#include <iostream>

namespace Utils {
    CSVParser::CSVParser(std::vector<std::string> keys)
            : m_keys(std::move(keys)), m_cols(m_keys.size()) {}

    void CSVParser::writeHeader(std::ostream& os) const {
        for(int i = 0; i < m_cols; i++) {
            os << m_keys[i];
            if(i != m_cols - 1) {
                os << ",";
            }
        }
        os << '\n';
    }

    static void outputEscapeString(std::ostream &os,
                                   const std::vector<std::string> &contents,
                                   decltype(contents.end()) endIt) {
        // traverse assigned strings
        for(auto it = contents.begin(); it != endIt; ++it) {
            os << '"';                 // beginning quotation mark
            for(auto& ch: *it) {
                if(ch == '\"') {
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

    bool CSVParser::addEntry(std::ostream &os, const std::vector<std::string> &contents) const {
        auto endIt = contents.end();
        if(contents.size() >= m_cols) {
            endIt = contents.begin() + m_cols;
            outputEscapeString(os, contents, endIt);
        } else {
            std::size_t absentColumnNumber = m_cols - contents.size();
            outputEscapeString(os, contents, endIt);
            for(int i = 0; i < absentColumnNumber; ++i) {
                os << ",\"\"";
            }

        }

        os << '\n';
        return (bool) os;
    }


    static bool traverse(const std::string& line, std::vector<std::string_view>& strings, std::size_t columnCount) {

        ReadState state = ReadState::lookingForQuotation;    // init state: lookingForQuotation

        // the substring properties (beginChar + length)
        int substringIndex = 0;
        const char * beginChar = &line[0];
        std::size_t length = 0;

        for(auto it = line.begin(); it != line.end(); ++it) {
            auto ch = *it;
            switch(ch) {
                case '\"': {
                    
                    switch (state) {
                        case ReadState::lookingForQuotation: {
                            state = ReadState::inQuotation;    // update read state -> inQuotation
                            beginChar = &*(it + 1);       // identify next character as the beginning of a new substring
                            break;
                        }
                        case ReadState::inQuotation: {
                            // check if it's ending quotation mark or a escaped one
                            if (*(it + 1) == '\"') {   // parse a `""` inside quotation
                                it += 1;              // ignore the escaped quotation
                                length += 2;
                            } else {    // face ending quotation mark
                                // end of the substring

                                new(&strings[substringIndex]) std::string_view{beginChar, length};
                                substringIndex++;
                                length = 0;         // reinitialize

                                // parse enough substring
                                if (substringIndex == columnCount) {
                                    return true;
                                } else {
                                    state = ReadState::lookingForComma;     // looking for the next comma
                                }
                            }
                            break;
                        }
                        case ReadState::lookingForComma : {
                            // error: just pass it
                        }
                    }

                    break;
                }

                case ',': {
                    switch (state) {
                        case ReadState::lookingForComma: {
                            // ready for the next quotation mark
                            state = ReadState::lookingForQuotation;
                            break;
                        }
                        case ReadState::inQuotation: {
                            length++;      // identified as a normal string
                            break;
                        }
                        case ReadState::lookingForQuotation:
                            return false;  // error;
                    }
                    break;
                }

                case '\n': {
                    return false;     // error
                }

                default: {
                    switch (state) {
                        case ReadState::inQuotation: {
                            length++;
                            break;
                        }
                        case ReadState::lookingForComma:
                        case ReadState::lookingForQuotation:
                            break;   // just pass it
                    }
                }
            }  // end: switch (ch)

        } // end: traverse

        return false;
    }


    bool CSVReader::readLine(std::istream &is, const std::vector<std::string *> &inputList) {

        if(inputList.size() != m_cols) {
            return false;
        }

        // get the next line to be parsed
        std::string line;
        std::getline(is, line);

        // vectors of substring
        std::vector<std::string_view> strings(m_cols);

        // parse the line, looking for the separating commas
        bool sign = traverse(line, strings, m_cols);

        if(!sign) {
            return false;
        }

        for(int i = 0; i < m_cols; ++i) {
            *(inputList[i]) = strings[i];
        }

        return true;

    }


}

