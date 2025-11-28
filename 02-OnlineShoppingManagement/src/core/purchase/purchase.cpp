//
// Created on 2025/11/26.
//

#include "core/purchase.hpp"
#include <numeric>

Purchase::Purchase(Customer *customer, std::vector<CartItem> items, Purchase::PurchaseTime time) {
    for(auto& cartItem: items) {
        auto item = *(cartItem.item);
        if(cartItem.count > item.getStock()) {
            // [WARN INFO]: NO ENOUGH ITEMS
            continue;
        }

        // THREAD SAFETY!
        cartItem.item -> setStock() -= cartItem.count;
        Price totalPriceOfItem = cartItem.count * item.getPrice();

        m_purchasedItems.emplace_back(item.getID(), item.getName(),
                                      item.getPrice(), cartItem.count,
                                      totalPriceOfItem,
                                      customer -> realPrice(totalPriceOfItem));
    }

    if(!m_purchasedItems.empty()) {
        m_ID = "";
        return;
    }

    m_time = time;
    m_customerID = customer -> getID();

    auto totalPrice = std::accumulate(m_purchasedItems.begin(),
                                      m_purchasedItems.end(),
                                      Price{0},
                                      [](const Price& price, const PurchasedItem& item) -> Price {
                                          return price + item.realPrice;
                                      });

    m_totalPrice = totalPrice;
    m_discount = m_totalPrice - totalPrice;
}

