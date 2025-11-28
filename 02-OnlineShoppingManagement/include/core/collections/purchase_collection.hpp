//
// Created by pilip on 2025/11/27.
//

#ifndef ONLINE_SHOPPING_MANAGEMENT_PURCHASE_COLLECTION_HPP
#define ONLINE_SHOPPING_MANAGEMENT_PURCHASE_COLLECTION_HPP

#include "core/purchase.hpp"
#include "core/collections/collection.hpp"

class PurchaseCollection : public Collection<Purchase> {
    std::string m_purchaseBriefCSVPath;
public:
    PurchaseCollection(std::string briefCSVPath, std::string detailsCSVPath)
        : Collection<Purchase>(std::move(detailsCSVPath)),
          m_purchaseBriefCSVPath(std::move(briefCSVPath)) {}

    virtual bool exportToCSV() override;
    virtual bool importFromCSV() override;
};


#endif //ONLINE_SHOPPING_MANAGEMENT_PURCHASE_COLLECTION_HPP
