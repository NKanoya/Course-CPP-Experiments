//
// Created on 2025/11/26.
//

#include "core/amount_of_money.hpp"
#include <string>

AmountOfMoney AmountOfMoney::convertFromString(const std::string& str) {
    AmountOfMoney amount{0};
    if(str.empty())
        return 0;

    size_t dotPos = str.find('.');

    if(dotPos == std::string::npos) {
        AmountOfMoney a;
        a.m_amount = std::stoll(str) * 100;
        return a;
    }

    std::string integerStr = str.substr(0, dotPos);
    std::string decimalStr = str.substr(dotPos + 1);

    amount.m_amount += std::stoll(integerStr) * 100;

    if(decimalStr.length() == 1) {
        amount.m_amount += (decimalStr[0] - '0') * 10;
    } else if(decimalStr.length() >= 2) {
        amount.m_amount += (decimalStr[0] - '0') * 10 + (decimalStr[1] - '0');
    }

    return amount;
}

std::string AmountOfMoney::format() const {
    std::string str = std::to_string(m_amount);

    if (str.length() <= 2) {
        str.insert(0, 3 - str.length(), '0');
    }

    str.insert(str.end() - 2, '.');
    return str;
}
