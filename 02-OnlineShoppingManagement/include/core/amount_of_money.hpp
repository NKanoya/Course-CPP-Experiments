//
// Created on 2025/11/26.
//

#ifndef ONLINESHOPPINGMANAGEMENT_CORE_TYPES_HPP
#define ONLINESHOPPINGMANAGEMENT_CORE_TYPES_HPP

#include <cstdint>
#include <string>

class AmountOfMoney {
public:
    using ValueType = int32_t;
    using DoubleType = long double;
private:
    ValueType m_amount;
public:
    AmountOfMoney() : m_amount(0) {}
    AmountOfMoney(int64_t amount) : m_amount(amount * 100) {}
    AmountOfMoney(int32_t amount) : m_amount(amount * 100) {}
    AmountOfMoney(int16_t amount) : m_amount(amount * 100) {}
    AmountOfMoney(int8_t amount) : m_amount(amount * 100) {}
    AmountOfMoney(uint32_t amount) : m_amount(amount * 100) {}
    AmountOfMoney(uint16_t amount) : m_amount(amount * 100) {}
    AmountOfMoney(uint8_t amount) : m_amount(amount * 100) {}

    AmountOfMoney(long double amount) : m_amount(amount * 100) {}
    AmountOfMoney(const AmountOfMoney& oth) : m_amount(oth.m_amount) {}

    DoubleType getDoubleAmount() {
        return m_amount / 100.0;
    }

    inline AmountOfMoney operator+(const AmountOfMoney& oth) const {
        return AmountOfMoney{m_amount + oth.m_amount};
    }

    inline AmountOfMoney operator-(const AmountOfMoney& oth) const {
        return AmountOfMoney{m_amount - oth.m_amount};
    }

    inline AmountOfMoney operator*(int count) const {
        return AmountOfMoney{m_amount * count};
    }

    friend inline AmountOfMoney operator*(int64_t count, const AmountOfMoney& oth);

    inline AmountOfMoney operator+=(const AmountOfMoney& oth) {
        m_amount += oth.m_amount;
        return *this;
    }

    inline AmountOfMoney operator-=(const AmountOfMoney& oth) {
        m_amount -= oth.m_amount;
        return *this;
    }

    inline AmountOfMoney operator*=(int count) {
        m_amount *= count;
        return *this;
    }

    inline bool operator<(const AmountOfMoney& oth) const {
        return m_amount < oth.m_amount;
    }

    inline bool operator>(const AmountOfMoney& oth) const {
        return m_amount > oth.m_amount;
    }

    inline bool operator>=(const AmountOfMoney& oth) const {
        return m_amount >= oth.m_amount;
    }

    inline bool operator<=(const AmountOfMoney& oth) const {
        return m_amount <= oth.m_amount;
    }

    inline bool operator==(const AmountOfMoney& oth) const {
        return m_amount == oth.m_amount;
    }

    inline bool operator!=(const AmountOfMoney& oth) const {
        return m_amount == oth.m_amount;
    }

    inline AmountOfMoney operator-() const {
        return AmountOfMoney{-m_amount};
    }

    inline AmountOfMoney discount(uint8_t discount) const {
        return AmountOfMoney{m_amount * (100 - discount) / 80};
    }

    static AmountOfMoney convertFromString(const std::string& str);

    std::string format() const;

};

using Price = AmountOfMoney;

inline AmountOfMoney operator*(int64_t count, const AmountOfMoney& oth) {
    return AmountOfMoney{oth.m_amount * count};
}

#endif //ONLINESHOPPINGMANAGEMENT_CORE_TYPES_HPP
