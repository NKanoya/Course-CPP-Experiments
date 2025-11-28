//
// Created on 2025/11/26.
//

#include "core/shop.hpp"
#include "utils/random/random_id.hpp"
#include <chrono>
#include <thread>
#include <limits>

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static std::string readString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;

    std::getline(std::cin >> std::ws, input);
    return input;
}

Shop::Shop() : m_itemCollection("item.csv"), m_memberCollection("member.csv"),
               m_purchaseCollection("purchase_brief.csv", "purchase_details.csv")
{
    importFromCSV();
}

Shop::~Shop() {
    exportToCSV();
}

using Clock = std::chrono::system_clock;

Purchase* Shop::transaction(const std::vector<CartItem> &items) {
    Customer customer{randomId()};
    Purchase purchase(&customer, items, Clock::now());

    if(purchase.getTotalPrice() >= 2000) {
        Price realPrice = purchase.getTotalPrice().discount(5);
        auto member = registerMemberWhenPurchasing(true, realPrice.getInteger());

        Purchase newPurchase(member, items, Clock::now());
        auto id = newPurchase.getID();
        m_purchaseCollection.addEntry(std::move(purchase));
        return m_purchaseCollection.getEntry(id);
    } else if (purchase.getTotalPrice() >= 1000) {
        Price realPrice = purchase.getTotalPrice().discount(2);
        auto premier = registerMemberWhenPurchasing(false, realPrice.getInteger());

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

Customer* Shop::registerMemberWhenPurchasing(bool isPremier, unsigned int points) {
    std::string name;
    std::shared_ptr<Member> memberPtr;

    if(isPremier)
        name = readString("Your consumption exceeds 2000. You can input your name to become a premier member!\n");
    else
        name = readString("Your consumption exceeds 1000. You can input your name to become a member!\n");

    std::cin.clear();
    std::string tel = readString("Please input your phone number: ");
    std::cin.clear();

    if(isPremier) {
        memberPtr = std::make_shared<PremierMember>(
                    randomId("PREM"),
                    name, tel, points, randomId("SCND")
                );
        std::cout << "\nMember registered! Type: PREMIER, ID: " << memberPtr->getID() << "\n";
    } else {
        memberPtr = std::make_shared<Member>(
                randomId("MMBR"),
                name, tel, points
                );
        std::cout << "\nMember registered! Type: REGULAR, ID: " << memberPtr->getID() << "\n";
    }

    m_memberCollection.addEntry(memberPtr);

    auto x = *(m_memberCollection.end() - 1);
    return &(*x);
}

Customer* Shop::registerMember(std::string name, std::string tel, unsigned int points, bool isPremier) {
    std::shared_ptr<Member> member;

    std::string id;

    if(isPremier == 1) {
        id = randomId("PREM");
        std::string secId = randomId("SCND");
        member = std::make_shared<PremierMember>(std::move(id), std::move(name), std::move(tel),
                                                 points, std::move(secId));
    } else {
        id = randomId("MMBR");
        member = std::make_shared<Member>(std::move(id), std::move(name), std::move(tel), points);
    }

    m_memberCollection.addEntry(member);
    auto it = *(m_memberCollection.end() - 1);
    auto& newAdded = *it;     // fix it!
    return &newAdded;
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

void Shop::importFromCSV() {
    using namespace std::chrono;
    auto begin = system_clock::now();

    auto importMembers = [this]() {
        auto begin = system_clock::now();

        this -> m_memberCollection.importFromCSV();

        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - begin);
        std::string log;
        log += "Successfully Importing Data From 'member.csv'! Timing: ";
        log += std::to_string(duration.count() / 1000.0);
        log += "ms\n";
        std::cout << log;
    };
    auto importItems = [this]() {
        auto begin = system_clock::now();

        this -> m_itemCollection.importFromCSV();

        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - begin);
        std::string log;
        log += "Successfully Importing Data From 'item.csv'! Timing: ";
        log += std::to_string(duration.count() / 1000.0);
        log += "ms\n";
        std::cout << log;
    };
    auto importPurchase = [this]() {
        auto begin = system_clock::now();

        this -> m_purchaseCollection.importFromCSV();

        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - begin);
        std::string log;
        log += "Successfully Importing Data From 'purchase_details.csv'! Timing: ";
        log += std::to_string(duration.count() / 1000.0);
        log += "ms\n";
        std::cout << log;
    };

    std::thread member(importMembers);
    std::thread item(importItems);
    std::thread purchase(importPurchase);

    member.join();
    item.join();
    purchase.join();

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - begin);
    std::cout << "Successfully Importing Data From CSV Files! Total Timing: " << duration.count() / 1000.0 << "ms\n";
}

void Shop::exportToCSV() {
    using namespace std::chrono;
    auto begin = system_clock::now();

    auto exportMembers = [this]() {
        auto begin = system_clock::now();

        this -> m_memberCollection.exportToCSV();

        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - begin);
        std::string log;
        log += "Successfully Exporting Data To 'member.csv'! Timing: ";
        log += std::to_string(duration.count() / 1000.0);
        log += "ms\n";
        std::cout << log;
    };
    auto exportItems = [this]() {
        auto begin = system_clock::now();

        this -> m_itemCollection.exportToCSV();

        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - begin);
        std::string log;
        log += "Successfully Exporting Data To 'item.csv'! Timing: ";
        log += std::to_string(duration.count() / 1000.0);
        log += "ms\n";
        std::cout << log;
    };
    auto exportPurchase = [this]() {
        auto begin = system_clock::now();

        this -> m_purchaseCollection.exportToCSV();

        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - begin);
        std::string log;
        log += "Successfully Exporting Data To 'purchase_details.csv' & 'purchase_brief.csv'! Timing: ";
        log += std::to_string(duration.count() / 1000.0);
        log += "ms\n";
        std::cout << log;
    };

    std::thread member(exportMembers);
    std::thread item(exportItems);
    std::thread purchase(exportPurchase);

    member.join();
    item.join();
    purchase.join();


    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - begin);
    std::cout << "Successfully Exporting Data To CSV Files! Total Timing: " << duration.count() / 1000.0 << "ms\n";
}

