//
// Created on 2025/11/18.
//

#ifndef LIBRARYMANAGEMENT_DATA_STRUCT_HPP
#define LIBRARYMANAGEMENT_DATA_STRUCT_HPP

#include <vector>
#include <array>
#include <string>
#include <stdexcept>
#include <iostream>

namespace Utils {

    template <class T>
    struct PointerRange {
        T* begin;
        T* end;

        PointerRange(std::vector<T>& vector) : begin(&vector[0]), end(begin + vector.size()) {}

        template <std::size_t size>
        PointerRange(std::array<T,size>& array) : begin(&array[0]), end(begin + size) {}

        PointerRange(T* array, std::size_t size) : begin(array), end(array + size) {}

        inline std::ptrdiff_t size() const noexcept {
            return end - begin;
        }
    };

    using EntryRange = PointerRange<std::string>;

    template <class Array>
    struct DoMainKeyExist {
        inline bool operator() (const Array& arr) const {
            return !arr[0].empty();
        }
    };


    template <class T_,
              class EnumClass_,
              class ValidChecker_ = DoMainKeyExist<std::array<T_, static_cast<std::size_t>(EnumClass_::COUNT)>> >
    class InfoEntry {
    public:
        using Key = EnumClass_;
        static constexpr std::size_t KEYCOUNT = static_cast<std::size_t>(Key::COUNT);
        static_assert(KEYCOUNT > 0, "The number of key should be at least 1!");
        static const ValidChecker_ checker;

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
            return checker(m_arr);
        }
    };

#include "impl/info_entry.tpp"

}

#endif //LIBRARYMANAGEMENT_DATA_STRUCT_HPP
