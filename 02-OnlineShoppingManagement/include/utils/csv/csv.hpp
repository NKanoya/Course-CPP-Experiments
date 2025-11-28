//
// Created by pilip on 2025/11/26.
//

#ifndef ONLINE_SHOPPING_MANAGEMENT_CSV_HPP
#define ONLINE_SHOPPING_MANAGEMENT_CSV_HPP

#include "rapidcsv.h"
#include "core/amount_of_money.hpp"

namespace rapidcsv {

    template<>
    struct Converter<Price> {
        Converter(const rapidcsv::ConverterParams& param) {}

        void ToVal(const std::string& str, AmountOfMoney& val) const {
            val = Price::convertFromString(str);
        }

        void ToStr(const Price& item, std::string& str) const {
            str = item.format();
        }
    };

}

#endif //ONLINE_SHOPPING_MANAGEMENT_CSV_HPP
