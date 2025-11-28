//
// Created by pilip on 2025/11/28.
//

#include "core/collections/purchase_collection.hpp"
#include <iostream>

namespace test {

    void test_purchase_collection() {

        PurchaseCollection purchaseCollection("purchase_brief.csv","purchase_details.csv");
        purchaseCollection.importFromCSV();

        for(const auto& item : purchaseCollection) {
            std::cout << item << '\n';
        }

        try {
            purchaseCollection.exportToCSV();
        } catch(std::exception& e) {
            std::cerr << e.what();
        }



    }

}