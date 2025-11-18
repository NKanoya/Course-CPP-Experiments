//
// Created on 2025/11/18.
//

#ifndef LIBRARYMANAGEMENT_DATA_STRUCT_HPP
#define LIBRARYMANAGEMENT_DATA_STRUCT_HPP

#include <vector>
#include <array>

namespace Utils {

    template <class T>
    struct PointerRange {
        T* begin;
        T* end;

        PointerRange(std::vector<T> vector) : begin(vector.begin().base()), end(vector.end().base()) {}

        template <std::size_t size>
        PointerRange(std::array<T,size> array) : begin(array.begin().base()), end(array.end().base()) {}

        PointerRange(T* array, std::size_t size) : begin(array), end(array + size) {}
    };

}

#endif //LIBRARYMANAGEMENT_DATA_STRUCT_HPP
