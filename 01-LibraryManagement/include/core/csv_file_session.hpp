//
// Created on 2025/11/21.
//

#ifndef LIBRARYMANAGEMENT_CSV_SESSION_HPP
#define LIBRARYMANAGEMENT_CSV_SESSION_HPP

#include "utils/data_struct.hpp"

/**
 * @brief An utility class to converse the data between CSV Files and a record collection.
 * @tparam RecordCollection_ The record collection class to operate
 */
template <class RecordCollection_>
class CSVFileSession {

    /**
     * @brief The file path of target CSV file.
     * @note @c CSVFileSession only holds a path of target file in string form. It will open the file only during I/O
     * operations.
     */
    std::string m_path;

public:

    /**
     * @brief The Constructor of the class
     * @param path the target CSV file path
     */
    explicit CSVFileSession(std::string path);

    /**
     * @brief modify the path of target CSV file
     * @param path <code>const std::string&</code>: The new CSV file path
     */
    inline void setPath(const std::string& path);

    /**
     * @brief to get current target CSV file path
     * @return <code>const std::string&</code> : the const reference of current target path
     */
    inline const std::string& readPath() const;

    /**
     * @brief Reads the contents of the CSV file, parses the CSV lines, and writes the parsed data to the record
     * collections.
     * @param recordCollection The reference of record collection.
     * @param clearAll @c bool : The record collection will be clear if the sign is @c true . The default argument is
     * @c false
     * @return @c bool : @c false if the input operations fails.
     *
     * @note When the input operations fails, the data in the collection will not be cleared even if @c clearAll is set
     * to @c true.
     */
    bool readToCollection(RecordCollection_& recordCollection, bool clearAll = false);

    /**
     * @brief Output the entries in the record Collection.
     * @param recordCollection The const reference of record collection.
     * @return @c bool : @c false if the input operations fails
     */
    bool writeFromCollection(const RecordCollection_& recordCollection) const;

};

#include "core/impl/csv_file_session.tpp"

#endif //LIBRARYMANAGEMENT_CSV_SESSION_HPP
