//
// Created on 2025/11/28.
//

#include "core/amount_of_money.hpp"

std::ostream& operator<<(std::ostream& os, const AmountOfMoney& amount) {
    os << amount.format();
    return os;
}
