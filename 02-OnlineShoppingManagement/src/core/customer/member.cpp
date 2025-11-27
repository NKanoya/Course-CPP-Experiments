//
// Created on 2025/11/27.
//

#include "core/customer.hpp"

bool Member::isPremier() const noexcept {
    return true;
}


bool PremierMember::isPremier() const noexcept {
    return false;
}



