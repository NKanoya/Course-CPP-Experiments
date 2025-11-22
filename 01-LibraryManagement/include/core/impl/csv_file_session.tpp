#include <fstream>

template <class RecordCollection_>
CSVFileSession<RecordCollection_>::CSVFileSession(std::string path) : m_path(path) {}

template <class RecordCollection_>
inline void CSVFileSession<RecordCollection_>::setPath(const std::string& path) {
    m_path = path;
}

template <class RecordCollection_>
inline const std::string& CSVFileSession<RecordCollection_>::readPath() const {
    return m_path;
}

template <class RecordCollection_>
bool CSVFileSession<RecordCollection_>::readToCollection(RecordCollection_& recordCollection, bool clearAll) {
    std::fstream fs(m_path);
    if(!fs.is_open())
        return false;

    // read header line
    Utils::CSVReader reader(fs);
    if(reader.readColumnCount() != static_cast<std::size_t>(RecordCollection_::KeyType::KEY_COUNT)) {
        return false;
    }

    if(clearAll)
        recordCollection.clear();      // clear the collection

    auto endIt = recordCollection.end();
    while(recordCollection.addEntry(reader, fs) != endIt);

    return true;
}

template <class RecordCollection_>
bool CSVFileSession<RecordCollection_>::writeFromCollection(const RecordCollection_& recordCollection) const {
    std::fstream fs(m_path);
    if(!fs.is_open())
        return false;

    Utils::CSVWriter writer{{}};

    while(recordCollection.outputCollection(writer, fs));
    return true;
}