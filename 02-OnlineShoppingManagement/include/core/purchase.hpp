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
        std::string m_itemID;
        std::string m_itemName;
        unsigned int m_count;
        Price m_unitPrice;
        Price m_sumPrice;
        Price m_realPrice;

        PurchasedItem(std::string itemID, std::string itemName, unsigned int count,
                      const Price& unitPrice, const Price& sumPrice,
                      const Price& finalPrice)
            : m_itemID(std::move(itemID)), m_itemName(std::move(itemName)), m_count(count),
              m_unitPrice(unitPrice), m_sumPrice(sumPrice), m_realPrice(finalPrice) {}
    };

    using PurchaseTime = std::chrono::system_clock::time_point;
protected:
    PurchaseTime m_time;
    std::string m_purchaseID;
    std::string m_customerID;
    std::vector<PurchasedItem> m_purchasedItems;
    Price m_discount;
    Price m_totalPrice;

public:
    Purchase(Customer* customer, std::vector<CartItem> items, PurchaseTime time);

    const std::vector<PurchasedItem>& getPurchaseItem() const {
        return m_purchasedItems;
    }

    std::vector<PurchasedItem>& setPurchaseItem() {
        return m_purchasedItems;
    }

    const PurchaseTime& getTime() const {
        return m_time;
    }

    const std::string& getPurchaseID() const {
        return m_purchaseID;
    }

    const Price getDiscount() const {
        return m_discount;
    }

    const Price getTotalPrice() const {
        return m_totalPrice;
    }

};

#endif //ONLINE_SHOPPING_MANAGEMENT_PURCHASE_HPP
