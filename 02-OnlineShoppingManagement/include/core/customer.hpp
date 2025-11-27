//
// Created on 2025/11/26.
//

#ifndef ONLINESHOPPINGMANAGEMENT_CUSTOMER_HPP
#define ONLINESHOPPINGMANAGEMENT_CUSTOMER_HPP

#include <string>
#include "core/amount_of_money.hpp"

class Customer {
    std::string m_ID;
public:
    Customer(const std::string& ID) : m_ID(ID) {}

     virtual Price realPrice(Price& price) {
        return price;
    }

    const auto& getID() const {
        return m_ID;
    }

};

class Member : public Customer {
    std::string m_name;
    std::string m_tel;
    unsigned int m_points;
public:
    Member(const std::string& ID, const std::string& name, const std::string tel, unsigned int points)
        : Customer(ID), m_name(name), m_tel(tel), m_points(points) {}

    inline Price realPrice(Price& price) override {
        return price.discount(2);
    }

    void getPurchaseList();

    const auto& getName() const {
        return m_name;
    }

    const auto& getTel() const {
        return m_tel;
    }

    const auto& getPoints() const {
        return m_points;
    };

    auto& setName()  {
        return m_name;
    }

    auto& setTel()  {
        return m_tel;
    }

    auto& setPoints()  {
        return m_points;
    };

    virtual bool isPremier() const noexcept;


};

class PremierMember : public Member {
    std::string m_secondaryID;
public:
    PremierMember(const std::string& ID, const std::string& name, const std::string tel, unsigned int points,
                  const std::string& secondaryID)
        : Member(ID, name, tel, points), m_secondaryID(secondaryID) {}

    inline Price realPrice(Price &price) override {
        return price.discount(5);
    }

    virtual bool isPremier() const noexcept override;

    auto& getSecondaryID() const {
        return m_secondaryID;
    };

    auto& setSecondaryID() {
        return m_secondaryID;
    }
};

#endif //ONLINESHOPPINGMANAGEMENT_CUSTOMER_HPP
