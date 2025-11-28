//
// Created on 2025/11/26.
//

#include "core/purchase.hpp"
#include "utils/random/random_id.hpp"
#include <numeric>

Purchase::Purchase(Customer *customer, const std::vector<CartItem>& items, Purchase::PurchaseTime time) : m_time(time) {
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

    if(m_purchasedItems.empty()) {
        m_ID = "";
        return;
    }

    m_time = time;
    m_ID = randomId("PRCH");
    m_customerID = customer -> getID();

    auto totalRealPrice = std::accumulate(m_purchasedItems.begin(),
                                      m_purchasedItems.end(),
                                      Price{0},
                                      [](const Price& price, const PurchasedItem& item) -> Price {
                                          return price + item.realPrice;
                                      });

    auto totalSumPrice = std::accumulate(m_purchasedItems.begin(),
                                      m_purchasedItems.end(),
                                      Price{0},
                                      [](const Price& price, const PurchasedItem& item) -> Price {
                                          return price + item.sumPrice;
                                      });

    m_totalPrice = totalRealPrice;
    m_discount = totalSumPrice - m_totalPrice;
}

