//
// Created on 2025/11/26.
//

#ifndef ONLINESHOPPINGMANAGEMENT_MEMBER_COLLECTION_HPP
#define ONLINESHOPPINGMANAGEMENT_MEMBER_COLLECTION_HPP

#include "core/customer.hpp"
#include "core/collections/collection.hpp"
#include <vector>
#include <memory>

using MemberPointer = std::shared_ptr<Member>;

class MemberCollection : public Collection<MemberPointer> {
public:
    MemberCollection(std::string csvPath) : Collection<MemberPointer>(std::move(csvPath)) {}

    virtual bool exportToCSV() override;
    virtual bool importFromCSV() override;
};

#endif //ONLINESHOPPINGMANAGEMENT_MEMBER_COLLECTION_HPP
