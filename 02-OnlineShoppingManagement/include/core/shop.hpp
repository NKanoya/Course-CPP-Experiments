//
// Created on 2025/11/26.
//

#ifndef ONLINESHOPPINGMANAGEMENT_SHOP_HPP
#define ONLINESHOPPINGMANAGEMENT_SHOP_HPP

#include <iostream>
#include "core/collections/member_collection.hpp"
#include "core/collections/item_collection.hpp"
#include "core/collections/purchase_collection.hpp"

class Shop {
    MemberCollection m_memberCollection;
    ItemCollection m_itemCollection;
    PurchaseCollection m_purchaseCollection;

public:
    Shop();
    ~Shop();

    void operation();

    Item& addItem(std::string name, Price price, unsigned int stock);

    void displayMembers(std::ostream& os);

    void displayPremiers(std::ostream& os);

    void displayItems(std::ostream& os);

    void displayPurchases(std::ostream& os);

    void displayItems(std::ostream& os, const std::vector<std::string>& ids);

    template <class Func>
    void displayItems(std::ostream& os, Func&& condition);

    template <class Func>
    void displayPurchases(std::ostream& os, Func&& condition);

    Customer* registerMember(std::string name, std::string tel, unsigned int points, bool isPremier);

    Customer* registerMemberWhenPurchasing(bool isPremier, unsigned int points);

    Purchase* transaction(const std::vector<CartItem>& items);
    Purchase* transaction(const std::string& memberID, const std::vector<CartItem>& items);

    void importFromCSV();
    void exportToCSV();
};

template<class Func>
void Shop::displayItems(std::ostream &os, Func &&condition) {
    auto ptrs = m_itemCollection.getEntries(condition);
    int i = 1;
    for(auto& ptr: ptrs) {
        std::cout << i << " | " << *ptr << '\n';
        ++i;
    }
}

template <class Func>
void Shop::displayPurchases(std::ostream& os, Func&& condition) {
    auto ptrs = m_purchaseCollection.getEntries(condition);
    int i = 1;
    for(auto& ptr: ptrs) {
        std::cout << i << " | " << *ptr << '\n';
    }
}

#endif //ONLINESHOPPINGMANAGEMENT_SHOP_HPP
