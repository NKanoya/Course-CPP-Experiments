//
// Created by pilip on 2025/11/28.
//

#include "core/purchase.hpp"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Purchase& purchase) {
    std::time_t purchaseTime_t = std::chrono::system_clock::to_time_t(purchase.m_time);
    std::tm* timePtr = std::localtime(&purchaseTime_t);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timePtr);
    os << " [" << buffer << "] ";
    os << "ID | " << purchase.m_ID << "    ";
    os << "Customer ID | " << purchase.m_customerID << "    ";
    os << "Total Price | " << purchase.m_totalPrice << " ";
    os << "(Discount: " << purchase.m_discount << ")\n";

    os << "\t\tDetails: \n";
    for(const auto& item: purchase.m_purchasedItems) {
        os << "\t\t - [" << item.ID << "] ";
        os << item.name << " x " << item.count << "    ";
        os << "<Unit Price> " << item.unitPrice << "    ";
        os << "<Total> " << item.realPrice << " ";
        os << "(Discount: " << item.sumPrice - item.realPrice << ")\n";
    }

    return os;
}
