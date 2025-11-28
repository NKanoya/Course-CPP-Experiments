//
// Created by pilip on 2025/11/28.
//

#include "core/collections/item_collection.hpp"
#include "core/collections/member_collection.hpp"
#include "core/collections/purchase_collection.hpp"
#include <iostream>

namespace test {

    void test_streams() {

        PurchaseCollection purchaseCollection("purchase_brief.csv","purchase_details.csv");
        ItemCollection itemCollection("item.csv");
        MemberCollection memberCollection("member.csv");
        purchaseCollection.importFromCSV();
        itemCollection.importFromCSV();
        memberCollection.importFromCSV();

        for(const auto& i: itemCollection) {
            std::cout << i << "\n";
        }

        std::cout << "\n\n\n";

        for(const auto& i: memberCollection) {
            std::cout << *i << "\n";
        }

        std::cout << "\n\n\n";

        for(const auto& i: purchaseCollection) {
            std::cout << i << "\n";
        }


        try {
            purchaseCollection.exportToCSV();
            itemCollection.exportToCSV();
            memberCollection.exportToCSV();
        } catch(std::exception& e) {
            std::cerr << e.what();
        }

    }

}