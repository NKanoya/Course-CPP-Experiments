//
// Created on 2025/11/28.
//

#ifndef ONLINE_SHOPPING_MANAGEMENT_RANDOM_ID_HPP
#define ONLINE_SHOPPING_MANAGEMENT_RANDOM_ID_HPP

#include <random>

class RandomID {
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;
public:
    RandomID() : gen(rd()), dist(10000000, 99999999) {}

    std::string operator()(const std::string& prefix = "CUST") {
        return prefix + std::to_string(dist(gen));
    }
};

static RandomID randomId;

#endif //ONLINE_SHOPPING_MANAGEMENT_RANDOM_ID_HPP
