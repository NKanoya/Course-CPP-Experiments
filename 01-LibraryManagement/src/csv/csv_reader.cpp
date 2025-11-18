//
// Created on 2025/11/18.
//

#include "utils/csv.hpp"
#include <iostream>
#include <algorithm>

namespace Utils {

    static bool parseFromCSV(const std::string& line, std::vector<std::string_view>& strings, std::size_t columnCount) {

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


    bool CSVReader::readLine(std::istream &is, const std::vector<std::string *> &inputList) const {

        if(inputList.size() != m_cols) {
            return false;
        }

        // get the next line to be parsed
        std::string line;
        std::getline(is, line);

        // vectors of substring
        std::vector<std::string_view> strings(m_cols);

        // parse the line, looking for the separating commas
        bool sign = parseFromCSV(line, strings, m_cols);

        if(!sign) {
            return false;
        }

        for(int i = 0; i < m_cols; ++i) {
            *(inputList[i]) = strings[i];
        }

        return true;

    }

    CSVReader::CSVReader(std::istream &is) {
        std::string line;
        getline(is, line);

        // if there exists `"` in the line, the line is not the heading
        if(std::find(line.begin(),line.end(),'\"') != line.end()) {
            // construct a invalid reader object
            m_cols = 0;
            return;
        }

        // if it's the heading, count the number of commas
        auto commaCount = std::count(line.begin(), line.end(), ',');
        m_cols = commaCount + 1;
    }

    CSVReader::CSVReader(const CSVWriter &writer) : m_cols(writer.readColumnCount()) {}

}