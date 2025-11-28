//
// Created on 2025/11/28.
//

#include "core/item.hpp"
#include "core/amount_of_money.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << "ID: " << item.m_ID << "   ";
    os << "Name: " <<  item.m_name << "   ";
    os << "Price: " <<  item.m_price << "   ";
    os << "Stock: " <<  item.m_stock;

    return os;
}