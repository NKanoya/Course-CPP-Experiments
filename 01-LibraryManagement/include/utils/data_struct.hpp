//
// Created on 2025/11/18.
//

#ifndef LIBRARYMANAGEMENT_DATA_STRUCT_HPP
#define LIBRARYMANAGEMENT_DATA_STRUCT_HPP

#include <vector>
#include <array>
#include <string>
#include <stdexcept>

namespace Utils {

    template <class T>
    struct PointerRange {
        T* begin;
        T* end;

        PointerRange(std::vector<T> vector) : begin(vector.begin().base()), end(vector.end().base()) {}

        template <std::size_t size>
        PointerRange(std::array<T,size> array) : begin(&array[0]), end(&array[size - 1]) {}

        PointerRange(T* array, std::size_t size) : begin(array), end(array + size) {}

        inline std::ptrdiff_t size() const noexcept {
            return end - begin;
        }
    };

    using EntryRange = PointerRange<std::string>;

    template <class T_, std::size_t arraySize_>
    struct isMainKeyExists {
        bool operator() (const std::array<T_ ,arraySize_>& arr) {
            return arr[0].empty;
        }
    };

    template <class T_,
              class EnumClass_,
              class ValidChecker_ = isMainKeyExists<T_, static_cast<std::size_t>(EnumClass_::COUNT)> >
    class InfoEntry {
    public:
        using Key = EnumClass_;
        static constexpr std::size_t KEYCOUNT = static_cast<std::size_t>(Key::COUNT);
        static_assert(KEYCOUNT > 0, "The number of key should be at least 1!");
        static ValidChecker_ checker;

        struct UseCopyTag {};
        struct UseMoveTag {};
    private:
        std::array<T_, static_cast<std::size_t>(Key::COUNT)> m_arr;

    public:
        InfoEntry() : m_arr() {}

        explicit InfoEntry(PointerRange<T_> pointerRange);
        InfoEntry(PointerRange<T_> pointerRange, UseCopyTag useCopy);
        InfoEntry(PointerRange<T_> pointerRange, UseMoveTag useMove);

        inline T_& operator[](Key key) noexcept;

        inline const T_& operator[](Key key) const noexcept;

        T_& at(Key key);
        const T_& at(Key key) const;

        inline PointerRange<T_> getRange();

        inline bool valid() const {
            return checker(m_arr);
        }

        inline operator bool() const {
            return check(m_arr);
        }
    };

    template<class T_, class EnumClass_, class ValidChecker_>
    InfoEntry<T_, EnumClass_, ValidChecker_>::
            InfoEntry(PointerRange<T_> pointerRange) {
        // use copy mode
        if(pointerRange.size() != KEYCOUNT) {
            m_arr[0] = "";      // construct an invalid object
            return;
        }

        // copy the elements to inner array
        for(int i = 0; i < KEYCOUNT; ++i) {
            m_arr[i] = pointerRange.begin[i];
        }
    }

    template<class T_, class EnumClass_, class ValidChecker_>
    InfoEntry<T_, EnumClass_, ValidChecker_>::
            InfoEntry(PointerRange<T_> pointerRange, InfoEntry::UseCopyTag useCopy)
            : InfoEntry(pointerRange) {}

    template<class T_, class EnumClass_, class ValidChecker_>
    InfoEntry<T_, EnumClass_, ValidChecker_>::
            InfoEntry(PointerRange<T_> pointerRange, InfoEntry::UseMoveTag useMove) {
        // use copy mode
        if(pointerRange.size() != KEYCOUNT) {
            m_arr[0] = "";      // construct an invalid object
            return;
        }

        // move the elements to inner array
        for(int i = 0; i < KEYCOUNT; ++i) {
            m_arr[i] = std::move(pointerRange.begin[i]);
        }
    }



    template <class T_, class EnumClass_, class ValidChecker_>
    inline T_& InfoEntry<T_, EnumClass_, ValidChecker_>::
            operator[](InfoEntry<T_, EnumClass_, ValidChecker_>::Key key) noexcept {
        return m_arr[static_cast<std::size_t>(key)];
    }

    template <class T_, class EnumClass_, class ValidChecker_>
    inline const T_& InfoEntry<T_, EnumClass_, ValidChecker_>::
            operator[](InfoEntry<T_, EnumClass_, ValidChecker_>::Key key) const noexcept {
        return m_arr[static_cast<std::size_t>(key)];
    }

    template<class T_, class EnumClass_, class ValidChecker_>
    T_& InfoEntry<T_, EnumClass_, ValidChecker_>::
            at(InfoEntry<T_, EnumClass_, ValidChecker_>::Key key) {
        auto index = static_cast<std::size_t>(key);
        if(key >= Key::COUNT) {
            if(key == Key::COUNT) {
                // use Key::COUNT as key
                throw std::out_of_range("Out of range! DO NOT use Key::COUNT as key!");
            }
            throw std::out_of_range("Out of range! Invalid Key!");
        }
        return m_arr[index];
    }

    template<class T_, class EnumClass_, class ValidChecker_>
    const T_& InfoEntry<T_, EnumClass_, ValidChecker_>::
            at(InfoEntry<T_, EnumClass_, ValidChecker_>::Key key) const {
        auto index = static_cast<std::size_t>(key);
        if(key >= Key::COUNT) {
            if(key == Key::COUNT) {
                // use Key::COUNT as key
                throw std::out_of_range("Out of range! DO NOT use Key::COUNT as key!");
            }
            throw std::out_of_range("Out of range! Invalid Key!");
        }
        return m_arr[index];
    }

    template<class T_, class EnumClass_, class ValidChecker_>
    inline PointerRange<T_> InfoEntry<T_, EnumClass_, ValidChecker_>::
            getRange() {
        return PointerRange<T_>(m_arr);
    }

}

#endif //LIBRARYMANAGEMENT_DATA_STRUCT_HPP
