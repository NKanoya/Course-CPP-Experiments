//
// Created on 2025/11/22.
//

#ifndef LIBRARYMANAGEMENT_CORE_TYPES_HPP
#define LIBRARYMANAGEMENT_CORE_TYPES_HPP

#include "utils/data_struct.hpp"

template <class EnumClass_>
using StringEntryConst = Utils::InfoEntry<
        const std::string,
        EnumClass_,
        Utils::GetEmptyString
>;

template <class EnumClass_>
using StringEntry = Utils::InfoEntry<
        std::string,
        EnumClass_,
        Utils::GetEmptyString
>;

#endif //LIBRARYMANAGEMENT_CORE_TYPES_HPP
