//
// Created on 2025/11/26.
//

#include "test_include.hpp"
#include "utils/csv/csv.hpp"

namespace test {

    void test_csv_import() {
        std::string csvPath = "test.csv";

        rapidcsv::Document csv(csvPath, rapidcsv::LabelParams(0, -1));
        std::size_t rowCount = csv.GetRowCount();

        auto intVec = csv.GetColumn<int>(0);
        auto priceVec = csv.GetColumn<Price>(1);
        auto stringVec = csv.GetColumn<std::string>(2);

        for(size_t i = 0; i < rowCount; ++i) {
            std::cout << intVec[i] << ' ' << priceVec[i].format() << ' ' << stringVec[i] << '\n';
        }

    }

}