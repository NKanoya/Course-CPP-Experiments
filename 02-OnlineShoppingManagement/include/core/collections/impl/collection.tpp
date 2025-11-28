#include <algorithm>

template<class T_>
bool Collection<T_>::addEntry(T_ newEntry) {
    auto it = std::find(m_vec.begin(), m_vec.end(), [&newEntry](const T_& entry) -> bool {
        return entry.m_ID == newEntry.m_ID;
    });
    if(it != m_vec.end())
        return false;

    m_vec.emplace_back(std::move(newEntry));
    return true;
}

template<class T_>
template<class IDType_>
bool Collection<T_>::deleteEntry(const IDType_ &ID) {
    auto it = std::find(m_vec.begin(), m_vec.end(), [&ID](const T_& entry) -> bool {
        return entry.m_ID == ID;
    });

    if(it == m_vec.end())
        return false;

    m_vec.erase(it);
}

template<class T_>
template<class IDType_>
T_ * const Collection<T_>::getEntry(const IDType_ &ID) {
    auto it = std::find_if(m_vec.begin(), m_vec.end(), [&ID](const T_& entry) -> bool {
        return entry.getID() == ID;
    });

    if(it == m_vec.end())
        return nullptr;

    return &(*it);
}

template<class T_>
template<class Func>
Collection<T_>::EntryPtrs Collection<T_>::getEntries(Func &&condition) {
    EntryPtrs ptrs;
    for(auto& entry : m_vec) {
        if(condition(entry)) {
            ptrs.emplace_back(&entry);
        }
    }

    return ptrs;
}