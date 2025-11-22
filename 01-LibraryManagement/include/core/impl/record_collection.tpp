template <class EnumClass_, class SubsidiaryDataType_>
RecordCollection<EnumClass_, SubsidiaryDataType_>::RecordCollection(const StringEntry<EnumClass_>& keyList)
// TODO: add validity check
    : m_map(), m_buffer(), m_keyList(keyList) { }

// Add Entry With Empty subsidiary Data
template <class EnumClass_, class SubsidiaryDataType_>
RecordCollection<EnumClass_, SubsidiaryDataType_>::iterator
    RecordCollection<EnumClass_, SubsidiaryDataType_>::
    addEntry(const Utils::CSVReader& csvReader, std::istream& is)
{

    // read from CSV stream, parse the strings into buffer
    bool readSuccessfully = csvReader.readLine(is,m_buffer.getRange());

    // return false if failing to read
    if(!readSuccessfully) return end();
    // return false if the buffer is invalid
    if(!m_buffer.valid()) {
        return end();
    }

    // copy the main key as the key of the map element
    auto key = m_buffer.getMainKey();
    // insert the full key-buffer-subsidiaryData value into the map
    // get the status pair from the return value
    auto insertStatus = m_map.emplace(
            std::move(key),
            ValueType{std::move(m_buffer), {}}
    );

    // set the buffer to invalid again
    m_buffer[static_cast<EnumClass_>(0)] = "";
    return insertStatus.first;     // return the map::iterator, implicitly conversed to ::iterator

}

template <class EnumClass_, class SubsidiaryDataType_>
RecordCollection<EnumClass_, SubsidiaryDataType_>::iterator
    RecordCollection<EnumClass_, SubsidiaryDataType_>::
    addEntry(EntryType entry)
{
    // return false if the buffer is invalid
    if(!entry.valid()) {
        return end();
    }

    // copy the main key as the key of the map element
    auto key = entry.getMainKey();
    // insert the full key-buffer-subsidiaryData value into the map
    // get the status pair from the return value
    auto insertStatus = m_map.emplace(
            std::move(key),
            ValueType{std::move(m_buffer), {}}
    );

    // get the status pair from the retuen value
    m_buffer[static_cast<EnumClass_>(0)] = "";
    return insertStatus.first;      // return the map::iterator, implicitly conversed to ::iterator
}

template <class EnumClass_, class SubsidiaryDataType_>
RecordCollection<EnumClass_, SubsidiaryDataType_>::EntryType*
RecordCollection<EnumClass_, SubsidiaryDataType_>::getEntryPointer(const std::string& mainKey) {
    auto it = m_map.find(mainKey);

    if(it == m_map.end()) {
        return nullptr;       // invalid value
    }
    return &(it -> second.entryContent);
}

template <class EnumClass_, class SubsidiaryDataType_>
const RecordCollection<EnumClass_, SubsidiaryDataType_>::EntryType*
RecordCollection<EnumClass_, SubsidiaryDataType_>::getEntryConstPointer(const std::string& mainKey) {
    auto it = m_map.find(mainKey);

    if(it == m_map.end()) {
        return nullptr;       // invalid value
    }
    return &(it -> second.entryContent);
}

template <class EnumClass_, class SubsidiaryDataType_>
bool RecordCollection<EnumClass_, SubsidiaryDataType_>::
outputCollection(Utils::CSVWriter& csvWriter, std::ostream& os) const {
    if(csvWriter.newKeys(m_keyList.getRange())) {
        return false;
    }

    csvWriter.writeHeader(os);

    for(auto& entry: m_map) {
        csvWriter.addEntry(os, entry.second.getRange());
    }

    return true;
}

