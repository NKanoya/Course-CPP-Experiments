//
// Created on 2025/11/26.
//

#include "core/collections/item_collection.hpp"
#include "utils/csv/csv.hpp"
#include <array>

constexpr int propertyCount = 4;

bool ItemCollection::importFromCSV() {
    try {
        rapidcsv::Document csv(m_csvPath, rapidcsv::LabelParams(0, -1));

        if (csv.GetColumnCount() < propertyCount) {
            return false;
        }
        std::size_t rowCount = csv.GetRowCount();
        if (rowCount == 0) {
            return true;
        }

        m_vec.clear();
        m_vec.reserve(rowCount);

        for (std::size_t i = 0; i < rowCount; ++i) {
            try {
                auto id = csv.GetCell<std::string>(0, i);
                auto name = csv.GetCell<std::string>(1, i);
                auto price = csv.GetCell<Price>(2, i);
                auto stock = csv.GetCell<unsigned int>(3, i);

                if (id.empty()) {
                    continue;
                }

                m_vec.emplace_back(id, name, price, stock);

            } catch (const std::exception& e) {
                std::cerr << "Error when loading items in row " << i << "\n";
                continue;
            }
        }

        return true;

    } catch (const std::exception& e) {
        std::cerr << "Failed to load the file:" << e.what() << std::endl;
        return false;
    }
}

bool ItemCollection::exportToCSV() {
    try {
        rapidcsv::Document csv;

        csv.SetColumnName(0, "ID");
        csv.SetColumnName(1, "Name");
        csv.SetColumnName(2, "Price");
        csv.SetColumnName(3, "Stock");

        std::vector<std::string> ids;
        std::vector<std::string> names;
        std::vector<Price> prices;
        std::vector<unsigned int> stocks;

        ids.reserve(m_vec.size());
        names.reserve(m_vec.size());
        prices.reserve(m_vec.size());
        stocks.reserve(m_vec.size());

        for (auto& item : m_vec) {
            ids.push_back(item.getID());
            names.push_back(item.getName());
            prices.push_back(item.getPrice());
            stocks.push_back(item.getStock());
        }

        csv.SetColumn(0, ids);
        csv.SetColumn(1, names);
        csv.SetColumn(2, prices);
        csv.SetColumn(3, stocks);

        csv.Save(m_csvPath);

        return true;

    } catch (const std::exception& e) {
        std::cerr << "Fail to export to the CSV file:" << e.what() << std::endl;
        return false;
    }
}
