//
// Created on 2025/11/26.
//

#ifndef ONLINESHOPPINGMANAGEMENT_COLLECTION_HPP
#define ONLINESHOPPINGMANAGEMENT_COLLECTION_HPP

#include <vector>
#include <string>

struct CSVIOInterface {
    std::string m_csvPath;

    CSVIOInterface(std::string csvPath) : m_csvPath(std::move(csvPath)) {}
    virtual bool exportToCSV() = 0;
    virtual bool importFromCSV() = 0;
};

template<class T_>
class Collection : public CSVIOInterface {
protected:
    std::vector<T_> m_vec;
public:
    using EntryPtrs = std::vector<T_* const>;
    explicit Collection(std::string csvPath) : CSVIOInterface(std::move(csvPath)) {}

    bool addEntry(T_ newEntry);

    template<class IDType_>
    bool deleteEntry(const IDType_& ID);

    template<class IDType_>
    T_* const getEntry(const IDType_& ID);

    template <class Func>
    EntryPtrs getEntries(Func&& condition);

    auto begin() {
        return m_vec.begin();
    }

    auto end() {
        return m_vec.end();
    }

    auto begin() const {
        return m_vec.begin();
    }

    auto end() const {
        return m_vec.end();
    }

};




#include "impl/collection.tpp"

#endif //ONLINESHOPPINGMANAGEMENT_COLLECTION_HPP
