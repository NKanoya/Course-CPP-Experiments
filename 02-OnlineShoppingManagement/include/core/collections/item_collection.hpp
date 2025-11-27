//
// Created on 2025/11/26.
//

#ifndef ONLINESHOPPINGMANAGEMENT_ITEM_COLLECTION_HPP
#define ONLINESHOPPINGMANAGEMENT_ITEM_COLLECTION_HPP

#include "core/item.hpp"
#include "core/collections/collection.hpp"
#include <vector>

class ItemCollection : public Collection<Item> {
public:
    explicit ItemCollection(std::string csvPath) : Collection<Item>(std::move(csvPath)) {}
    virtual bool exportToCSV() override;
    virtual bool importFromCSV() override;
};

#endif //ONLINESHOPPINGMANAGEMENT_ITEM_COLLECTION_HPP
