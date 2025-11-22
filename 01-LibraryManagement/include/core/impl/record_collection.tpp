template <class EnumClass_>
RecordCollection<EnumClass_>::RecordCollection(const StringEntryConst<EnumClass_>& keyList)
    : m_set(), m_buffer(), m_keyList(keyList) { }

template <class EnumClass_>
bool RecordCollection<EnumClass_>::addEntry(const Utils::CSVReader& csvReader, std::istream& is) {

    bool readSuccessfully = csvReader.readLine(is,m_buffer);

    if(!readSuccessfully) return false;
    if(m_buffer.invalid()) {
        m_buffer.clear();
        return false;
    }

    auto result = m_set.insert(m_buffer);

    m_buffer.clear();
    return result.second;     // if the insertion is successful

}

template <class EnumClass_>
bool RecordCollection<EnumClass_>::addEntry(EntryType entry) {
    if(!entry.valid()) {
        return false;
    }

    auto result = m_set.insert(std::move(entry));

    m_buffer.clear();
    return result.second;     // if the insertion is successful
}

template <class EnumClass_>
const RecordCollection<EnumClass_>::EntryConstType&
RecordCollection<EnumClass_>::getEntryConst(std::string& mainKey) const {
    auto it = m_set.begin();
    for(; it != m_set.end(); ++it) {
        if(it -> getMainKey() == mainKey) {
            break;
        }
    }

    if(it == m_set.end()) {
        return m_buffer;       // invalid value
        // !! thread unsecurity
    }
    return *it;
}

template <class EnumClass_>
RecordCollection<EnumClass_>::EntryType&
RecordCollection<EnumClass_>::getEntry(std::string mainKey) {
    auto it = m_set.begin();
    for(; it != m_set.end(); ++it) {
        if(it -> getMainKey() == mainKey) {
            break;
        }
    }

    if(it == m_set.end()) {
        return m_buffer;       // invalid value
        // !! thread unsecurity
    }
    return *it;
}

