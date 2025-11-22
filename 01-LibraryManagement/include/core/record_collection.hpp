//
// Created on 2025/11/21.
//

#ifndef LIBRARYMANAGEMENT_COLLECTION_HPP
#define LIBRARYMANAGEMENT_COLLECTION_HPP

#include <map>
#include "core/core_types.hpp"
#include "utils/csv.hpp"

// -------------------------------------------------------------
//  Internal implement struct
// -------------------------------------------------------------

namespace Impl {

    /**
     * @brief An empty utility class for the default template parameter of the subsidiary data type
     */
    struct Empty {};

}

// -------------------------------------------------------------
//  class RecordCollection
// -------------------------------------------------------------

/**
 * @brief A collection of records, each of which composed of an string entry and a subsidiary data.
 *
 * <p>The collection is to stored large number of entries with its relations or other subsidiary information. The two
 * part of data constitutes a @b record. In every record, the subsidiary data is one-to-one corresponding with the entry
 * (adjacent physically) in a record.</p>
 *
 * @tparam KeyEnumClass_ The enum class of keys of the string entry. The first enum member is identified as the main key
 * and the numeric value of @c KEY_COUNT member is identified as the count of keys.
 * @tparam SubsidiaryDataType_ The type of the subsidiary data. By default it will be @c Impl::Empty , an empty struct.
 * 
 * <p>For example, the collection of books owns the entry of book information, together with the pointers to its copies'
 * entries. So the class @c BookCollection can implement the template with the key enum and the string and the
 * <b>pointers of the copies' entries as the subsidiary data type</b>.</p>
 */
template <class KeyEnumClass_, class SubsidiaryDataType_ = Impl::Empty>
class RecordCollection {
public:

    // -------------------------------------------------------------
    //  The Alias in the scope of RecordCollection
    // -------------------------------------------------------------

    /** @brief Alias for the type of every Entry. */
    using EntryType = StringEntry<KeyEnumClass_>;

    /** @brief Alias for the type of every Entry in const context. */
    using EntryConstType = StringEntryConst<KeyEnumClass_>;

    /** @biref Alias for the key enum of the entry. */
    using KeyType = KeyEnumClass_;

    /** @biref Alias for the subsidiary data followed with every entry. */
    using SubsidiaryDataType = SubsidiaryDataType_;

    /**
     * @brief A combination struct of the entry type and the subsidiary data.
     *
     * <p>Serves as the underlying value type in the map, composed of an entry and an subsidiary data.</p>
     *
     * <p>The struct is derived from @c EntryType , so the methods and operators are inherited. The subsidiary data is
     * stored as the member @c subsidiaryData .</p>
     */
    using Record = struct Pack_ : public EntryType {
        SubsidiaryDataType_ subsidiaryData;
    };

protected:

    // -------------------------------------------------------------
    //  The protected member of RecordCollection
    // -------------------------------------------------------------

    /** @brief The internal map containers, using the main key string as key and storing the entry and subsidiary data
     * as value. */
    std::map<std::string, Record> m_map;

    /**
     * @brief Records the name list of the string keys.
     */
    EntryType m_keyList;

    /**
     * @brief The buffer of the the entry. If a entry is input, the data will be first written in the buffer, and
     * inserted together with the map key into the map subsequently.
     */
    EntryType m_buffer;

public:

    // -------------------------------------------------------------
    //  The iterator of RecordCollection
    // -------------------------------------------------------------

    /**
     * @brief The bidirectional iterator pointing at the record (a pack of entry and the subsidiary data).
     */
    class iterator {

        // inner map::iterator
        typename std::map<std::string, Record>::iterator m_currentIt;

    public:

        // Aliases adhering to the iterator standard
        using iterator_category = std::bidirectional_iterator_tag;
        using different_type = std::ptrdiff_t;
        using value_type = Pack_;
        using pointer = Pack_*;
        using reference = Pack_&;

        // conversion constructor: conversed from map::iterator
        iterator(typename std::map<std::string, Record>::iterator it) : m_currentIt(it) {}

        // operator-- (const)
        const reference operator*() const {
            return m_currentIt -> second;
        };

        // operator*
        reference operator*() {
            return m_currentIt -> second;
        }

        // operator-> (const)
        const pointer operator->() const {
            return *(m_currentIt -> second);
        }

        // operator->
        pointer operator->() {
            return *(m_currentIt -> second);
        }

        // operator++
        iterator& operator++() {
            ++m_currentIt;
            return *this;
        }

        // operator++
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        // operator--
        iterator& operator--() {
            --m_currentIt;
            return *this;
        }

        // operator--
        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        // operator==
        bool operator==(const iterator& oth) const {
            return m_currentIt == oth.m_currentIt;
        }

        // operator!=
        bool operator!=(const iterator& oth) const {
            return m_currentIt != oth.m_currentIt;
        }


    };

    // -------------------------------------------------------------
    //  The constructor of RecordCollection
    // -------------------------------------------------------------

    /**
     * @brief The constructor to create a record Collection.
     *
     * @param keyList <code>const StringEntry&lt;KeyEnumClass_></code> : The string entry with the same key enum class,
     * recording the names of the keys.
     *
     * <p>The collection object will use the @c keyList as the string-formed key.</p>
     */
    explicit RecordCollection(const StringEntry<KeyEnumClass_>& keyList);

    // -------------------------------------------------------------
    //  Methods of Access to the elements (through pointers)
    // -------------------------------------------------------------

    /**
     * @brief gets the pointer of the record.
     * @param mainKey <code>const String&</code> : the appointed main key to find the record.
     * @return @c Record* : The pointer of the corresponding record, @c nullptr when failing to find.
     */
    Record* getRecordPointer(const std::string& mainKey);

    /**
     * @brief gets the const pointer of the entry (subsidiary data not included).
     * @param mainKey <code>const String&</code> : the appointed main key to find the entry  within the record (in const
     * context).
     * @return <code>const Record*</code> : The const pointer of the corresponding record, @c nullptr when failing to
     * find.
     */
    const Record* getRecordConstPointer(const std::string& mainKey) const;

    /**
     * @brief gets the pointer of the entry (subsidiary data not included).
     * @param mainKey <code>const String&</code> : the appointed main key to find the entry within the record.
     * @return @c EntryType* : The pointer of the corresponding entry, @c nullptr when failing to find.
     *
     * @see @c getRecordPointer() / @c getRecordConstPointer() for pointers of the whole record including the entry and
     * the subsidiary.
     */
    EntryType* getEntryPointer(const std::string& mainKey);

    /**
     * @brief gets the const pointer of the entry (subsidiary data not included).
     * @param mainKey <code>const String&</code> : the appointed main key to find the entry  within the record (in const
     * context).
     * @return <code>const EntryType*</code> : The const pointer of the corresponding entry, @c nullptr when failing to
     * find.
     *
     * @see @c getRecordPointer() / @c getRecordConstPointer() for pointers of the whole record including the entry and
     * the subsidiary.
     */
    const EntryType* getEntryConstPointer(const std::string& mainKey) const;

    // -------------------------------------------------------------
    //  I/O-related Methods of RecordCollection
    // -------------------------------------------------------------

    /**
     * @brief Add an constructed entry directly to the collection.
     *
     * @param Entry <code>EntryType</code> : The entry to be added
     * @return @c ::iterator : the iterator of the inserted record, or @c end() when the insertion fails.
     *
     * @note the @c subsidiaryData will be constructed empty in the new-created entry element.
     * If the entry needs please traverse
     */
    iterator addEntry(EntryType entry);

    /**
     * @brief Writes one CSV line, and parse it as an entry and add it to the collection.
     *
     * @param csvReader <code>const Utils::CSVReader&</code> : the constant reference of the @c CSVReader utility object.
     * The method will use it to parse CSV strings and input the result.
     * @param is @c std::istream& : The source input stream.
     * @return @c ::iterator : the iterator of the inserted record, or @c end() when the insertion
     * fails.
     *
     * @note the @c subsidiaryData will be constructed empty in the new-created entry element.
     */
    iterator addEntry(const Utils::CSVReader& csvReader, std::istream& is);

    /**
     * @brief Outputs the whole collection with a injected @c CSVWriter and a output stream
     * @param csvWriter @c Utils::CSVWriter& : a CSV writer utility
     * @param os @c std::ostream : the target output stream
     * @return @c bool : @c true if the CSVWriter is compatible to the collection (having the same count of keys)
     */
    bool outputCollection(Utils::CSVWriter& csvWriter, std::ostream& os) const;

    /** @return @c iterator : the begin iterator  */
    inline iterator begin() {
        return m_map.begin();
    }

    /** @return @c iterator : the end iterator  */
    inline iterator end() {
        return m_map.end();
    }

};

// the implementation of the template methods
#include "core/impl/record_collection.tpp"



#endif //LIBRARYMANAGEMENT_COLLECTION_HPP
