//
// Created on 2025/11/26.
//

#include "core/shop.hpp"
#include "utils/random/random_id.hpp"
#include <chrono>
#include <thread>

Shop::Shop() : m_itemCollection("item.csv"), m_memberCollection("member.csv"),
               m_purchaseCollection("purchase_brief.csv", "purchase_details.csv")
{
    auto importMembers = [this]() {
        this -> m_memberCollection.importFromCSV();
    };
    auto importItems = [this]() {
        this -> m_itemCollection.importFromCSV();
    };
    auto importPurchase = [this]() {
        this -> m_purchaseCollection.importFromCSV();
    };

    std::thread member(importMembers);
    std::thread item(importItems);
    std::thread purchase(importPurchase);

    member.join();
    item.join();
    purchase.join();
}

Shop::~Shop() {
    auto exportMembers = [this]() {
        this -> m_memberCollection.exportToCSV();
    };
    auto exportItems = [this]() {
        this -> m_itemCollection.exportToCSV();
    };
    auto exportPurchase = [this]() {
        this -> m_purchaseCollection.exportToCSV();
    };

    std::thread member(exportMembers);
    std::thread item(exportItems);
    std::thread purchase(exportPurchase);

    member.join();
    item.join();
    purchase.join();
}

using Clock = std::chrono::system_clock;

Purchase* Shop::transaction(const std::vector<CartItem> &items) {
    Customer customer{randomId()};
    Purchase purchase(&customer, items, Clock::now());

    if(purchase.getTotalPrice() >= 2000) {
        Price realPrice = purchase.getTotalPrice().discount(5);
        auto member = registerMember(true, realPrice.getInteger());

        Purchase newPurchase(member, items, Clock::now());
        auto id = newPurchase.getID();
        m_purchaseCollection.addEntry(std::move(purchase));
        return m_purchaseCollection.getEntry(id);
    } else if (purchase.getTotalPrice() >= 1000) {
        Price realPrice = purchase.getTotalPrice().discount(2);
        auto premier = registerMember(false, realPrice.getInteger());

        Purchase newPurchase(premier, items, Clock::now());
        auto id = newPurchase.getID();
        m_purchaseCollection.addEntry(std::move(purchase));
        return m_purchaseCollection.getEntry(id);
    }

    auto id = purchase.getID();
    m_purchaseCollection.addEntry(std::move(purchase));
    return m_purchaseCollection.getEntry(id);
}

Purchase* Shop::transaction(const std::string& memberID, const std::vector<CartItem>& items) {
    MemberPointer* member = m_memberCollection.getEntry(memberID);
    if(!member) {
        std::cerr << "Member not found! Transaction Falied!";
        return nullptr;
    }

    Purchase purchase(&(**member), items, Clock::now());
    auto id = purchase.getID();
    m_purchaseCollection.addEntry(std::move(purchase));
    return m_purchaseCollection.getEntry(id);
}

Customer* Shop::registerMember(bool isPremier, unsigned int points) {
    std::string name, tel;
    std::shared_ptr<Member> memberPtr;

    if(isPremier)
        std::cout << "Your consumption exceeds 2000. You can input your name to become a premier member!\n" << std::endl;
    else
        std::cout << "Your consumption exceeds 1000. You can input your name to become a member!\n" << std::endl;

    std::cin >> name;
    std::cin.clear();
    std::cout << "Please input your phone number:\n" << std::endl;
    std::cin >> tel;
    std::cin.clear();

    if(isPremier) {
        memberPtr = std::make_shared<PremierMember>(
                    randomId("PREM"),
                    name, tel, points, randomId("SCND")
                );
    } else {
        memberPtr = std::make_shared<Member>(
                randomId("MMBR"),
                name, tel, points
                );
    }

    m_memberCollection.addEntry(memberPtr);

}

Item& Shop::addItem(std::string name, Price price, unsigned int stock) {
    Item* ptr = nullptr;

    std::string id = randomId("ITEM");
    while(m_itemCollection.addEntry(Item{id, std::move(name), price, stock}));
    auto added = m_itemCollection.getEntry(id);

    return *added;
}

void Shop::displayMembers(std::ostream& os) {
    int i = 1;
    for(auto& ptr: m_memberCollection) {
        if(!ptr -> isPremier()) {
            os << i << "\t| " << *ptr << '\n';
            i++;
        }
    }
}

void Shop::displayPremiers(std::ostream &os) {
    int i = 1;
    for(auto& ptr: m_memberCollection) {
        if(ptr -> isPremier()) {
            os << i << "\t| " << *ptr << '\n';
            i++;
        }
    }
}

void Shop::displayItems(std::ostream& os) {
    int i = 1;
    for(auto& item: m_itemCollection) {
        os << i << "\t| " << item << '\n';
        i++;
    }
}

void Shop::displayPurchases(std::ostream& os) {
    int i = 1;
    for(auto& item: m_purchaseCollection) {
        os << i << "\t| " << item << '\n';
        i++;
    }
}

void Shop::displayItems(std::ostream& os, const std::vector<std::string>& ids) {
    std::vector<Item*> vec = {};
    vec.reserve(ids.size());
    for(auto& id: ids) {
        auto ptr = m_itemCollection.getEntry(id);
        if(ptr) {
            vec.emplace_back(ptr);
        }
    }

    int i = 1;
    for(auto& itemPtr: vec) {
        std::cout << i << " | " << *itemPtr << '\n';
        ++i;
    }
}


