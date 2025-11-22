//
// Created on 2025/11/21.
//

#ifndef LIBRARYMANAGEMENT_COLLECTION_HPP
#define LIBRARYMANAGEMENT_COLLECTION_HPP

#include <set>
#include "core/core_types.hpp"
#include "utils/csv.hpp"


namespace Impl {

    template <class EnumClass_>
    struct LessOfMainKey {
        bool operator()(const StringEntryConst<EnumClass_>& a, const StringEntryConst<EnumClass_>& b) {
            return a[static_cast<EnumClass_>(0)] < b[static_cast<EnumClass_>(0)];
        }
    };

}



template <class EnumClass_>
class RecordCollection {
public:
    using EntryType = StringEntry<EnumClass_>;
    using EntryConstType = StringEntryConst<EnumClass_>;

private:
    std::set<EntryType, Impl::LessOfMainKey<EnumClass_>> m_set;

    EntryType m_keyList;

    EntryType m_buffer;
public:

    RecordCollection(const StringEntryConst<EnumClass_>& keyList);

    bool addEntry(const Utils::CSVReader& csvReader, std::istream& is);

    bool addEntry(EntryType entry);

    const EntryConstType& getEntryConst(std::string& mainKey) const;

    EntryType& getEntry(std::string mainKey);


};

#include "core/impl/record_collection.tpp"



#endif //LIBRARYMANAGEMENT_COLLECTION_HPP
