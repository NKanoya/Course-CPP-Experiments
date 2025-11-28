//
// Created by pilip on 2025/11/27.
//

#ifndef ONLINE_SHOPPING_MANAGEMENT_PURCHASE_HPP
#define ONLINE_SHOPPING_MANAGEMENT_PURCHASE_HPP

#include <chrono>
#include <string>
#include <vector>
#include "core/amount_of_money.hpp"
#include "core/item.hpp"
#include "core/customer.hpp"

struct CartItem {
    Item* item;
    unsigned int count;
};

class Purchase {
public:
    struct PurchasedItem {
        std::string ID;
        std::string name;
        Price unitPrice;
        unsigned int count;
        Price sumPrice;
        Price realPrice;

        PurchasedItem(std::string itemID, std::string itemName, const Price& unitPrice,
                      unsigned int count, const Price& sumPrice,
                      const Price& realPrice)
            : ID(std::move(itemID)), name(std::move(itemName)), count(count),
              unitPrice(unitPrice), sumPrice(sumPrice), realPrice(realPrice) {}
    };

    using PurchaseTime = std::chrono::system_clock::time_point;
protected:
    PurchaseTime m_time;
    std::string m_ID;   // purchase ID
    std::string m_customerID;
    std::vector<PurchasedItem> m_purchasedItems;
    Price m_discount;
    Price m_totalPrice;

public:
    Purchase(Customer* customer, const std::vector<CartItem>& items, PurchaseTime time);
    Purchase(PurchaseTime time, std::string ID, std::string customerId)
        : m_time(time), m_ID(std::move(ID)), m_customerID(std::move(customerId)) {}

    const std::vector<PurchasedItem>& getPurchaseItem() const {
        return m_purchasedItems;
    }

    const std::string& getID() const {
        return m_ID;
    }

    std::vector<PurchasedItem>& setPurchaseItem() {
        return m_purchasedItems;
    }

    const PurchaseTime& getTime() const {
        return m_time;
    }

    const std::string& getCustomerID() const {
        return m_customerID;
    }

    const Price& getDiscount() const {
        return m_discount;
    }

    const Price& getTotalPrice() const {
        return m_totalPrice;
    }

    Price& setDiscount() {
        return m_discount;
    }

    Price& setTotalPrice() {
        return m_totalPrice;
    }

    friend std::ostream& operator<<(std::ostream& os, const Purchase& purchase);

};

#endif //ONLINE_SHOPPING_MANAGEMENT_PURCHASE_HPP
