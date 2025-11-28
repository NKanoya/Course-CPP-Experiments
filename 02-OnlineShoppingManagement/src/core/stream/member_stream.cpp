//
// Created on 2025/11/28.
//

#include "core/customer.hpp"

std::ostream& operator<<(std::ostream& os, const Member& member) {
    os << "ID: " << member.getID() << "   ";
    os << "Name: " << member.m_name << "   ";
    os << "Tel: " << member.m_tel << "   ";
    os << "Points: " << member.m_points;

    return os;
}

std::ostream& operator<<(std::ostream& os, const PremierMember& premier) {
    os << "ID: " << premier.getID() << "   ";
    os << "Name: " << premier.getName() << "   ";
    os << "Tel: " << premier.getTel() << "   ";
    os << "Points: " << premier.getPoints() << "   ";
    os << "Secondary ID: " << premier.getSecondaryID();

    return os;
}