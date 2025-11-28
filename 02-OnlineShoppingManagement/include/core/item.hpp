//
// Created on 2025/11/26.
//

#ifndef ONLINESHOPPINGMANAGEMENT_GOODS_HPP
#define ONLINESHOPPINGMANAGEMENT_GOODS_HPP

#include <string>
#include "core/amount_of_money.hpp"

class Item {
    std::string m_ID;
    std::string m_name;
    Price m_price;
    unsigned int m_stock;
public:

    Item(const std::string& ID, const std::string& name, const Price& price, unsigned int stock)
            : m_ID(ID), m_name(name), m_price(price), m_stock(stock) {}

    const std::string& getID() const {
        return m_ID;
    }

    const std::string& getName() const {
        return m_name;
    }

    const Price& getPrice() const {
        return m_price;
    }

    unsigned int getStock() const {
        return m_stock;
    }

    std::string& setID() {
        return m_ID;
    }

    std::string& setName() {
        return m_name;
    }

    Price& setPrice() {
        return m_price;
    }

    unsigned int& setStock() {
        return m_stock;
    }

    friend std::ostream& operator<<(std::ostream& os, const Item& item);

};

#endif //ONLINESHOPPINGMANAGEMENT_GOODS_HPP
