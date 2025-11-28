//
// Created on 2025/11/27.
//

#include "core/collections/purchase_collection.hpp"
#include "utils/csv/csv.hpp"
#include <iomanip>

constexpr int propertyCountBrief = 6;
constexpr int propertyCountDetails = 9;

static std::chrono::system_clock::time_point stringToTimePoint(const std::string& datetimeStr) {
    // YYYY-MM-DD HH:MM:SS
    if (datetimeStr.length() < 19) {
        throw std::runtime_error("Errors on String Format of Date-Time!");
    }

    std::tm tm = {};

    tm.tm_year = std::stoi(datetimeStr.substr(0, 4)) - 1900;  // 年（从1900开始）
    tm.tm_mon = std::stoi(datetimeStr.substr(5, 2)) - 1;      // 月（0-11）
    tm.tm_mday = std::stoi(datetimeStr.substr(8, 2));         // 日
    tm.tm_hour = std::stoi(datetimeStr.substr(11, 2));        // 时
    tm.tm_min = std::stoi(datetimeStr.substr(14, 2));         // 分
    tm.tm_sec = std::stoi(datetimeStr.substr(17, 2));         // 秒

    std::time_t tt = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(tt);
}

bool PurchaseCollection::importFromCSV() {
    try {
        rapidcsv::Document csv(m_csvPath, rapidcsv::LabelParams(0, -1));

        if (csv.GetColumnCount() < propertyCountDetails) {
            return false;
        }
        std::size_t rowCount = csv.GetRowCount();
        if (rowCount == 0) {
            return true;
        }

        m_vec.clear();
        m_vec.reserve(rowCount);

        std::string lastId;
        std::string readDate;
        std::string readTime;
        std::string readCustomerID;
        Purchase* current = nullptr;

        for (std::size_t i = 0; i < rowCount; ++i) {
            try {
                auto id = csv.GetCell<std::string>(2, i);
                if (id.empty()) {
                    continue;
                }
                if(id != lastId) {
                    readDate = csv.GetCell<std::string>(0, i);
                    readTime = csv.GetCell<std::string>(1, i);
                    readCustomerID = csv.GetCell<std::string>(3, i);
                    std::string dateTimeString;
                    dateTimeString += readDate;
                    dateTimeString += ' ';
                    dateTimeString += readTime;
                    auto timePoint = stringToTimePoint(dateTimeString);

                    auto& emplaced = m_vec.emplace_back(timePoint, id, readCustomerID);
                    current = &emplaced;

                }

                auto currentSumPrice = csv.GetCell<Price>(8, i);
                auto currentRealPrice = csv.GetCell<Price>(9, i);

                Purchase::PurchasedItem item(
                        csv.GetCell<std::string>(5, i),
                        csv.GetCell<std::string>(4, i),
                        csv.GetCell<Price>(6, i),
                        csv.GetCell<unsigned int>(7, i),
                        currentSumPrice, currentRealPrice
                );
                current -> setPurchaseItem().emplace_back(item);

                current -> setDiscount() += currentSumPrice - currentRealPrice;
                current -> setTotalPrice() += currentRealPrice;

                if(id != lastId) {

                    lastId = id;
                }

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

bool PurchaseCollection::exportToCSV() {
    try {

        std::vector<std::string> dates;
        std::vector<std::string> times;
        std::vector<std::string> ids;
        std::vector<std::string> customerIds;

        std::vector<std::string> itemIds;
        std::vector<std::string> itemNames;
        std::vector<unsigned int> itemCounts;
        std::vector<Price> itemUnitPrices;
        std::vector<Price> itemSumPrices;
        std::vector<Price> itemRealPrices;

        std::vector<Price> totalPrices;
        std::vector<Price> discounts;

        std::vector<unsigned short> itemCountPerPurchases;


        dates.reserve(m_vec.size());
        times.reserve(m_vec.size());
        ids.reserve(m_vec.size());
        customerIds.reserve(m_vec.size());
        totalPrices.reserve(m_vec.size());
        discounts.reserve(m_vec.size());

        for (auto& purchase : m_vec) {
            std::time_t purchaseTime_t = std::chrono::system_clock::to_time_t(purchase.getTime());
            std::tm* timePtr = std::localtime(&purchaseTime_t);

            char dateBuffer[11];  // YYYY-MM-DD + null
            char timeBuffer[9];   // HH:MM:SS + null

            std::strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", timePtr);
            std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", timePtr);

            dates.emplace_back(dateBuffer);
            times.emplace_back(timeBuffer);

            ids.emplace_back(purchase.getID());
            customerIds.emplace_back(purchase.getCustomerID());
            totalPrices.emplace_back(purchase.getTotalPrice());
            discounts.emplace_back(purchase.getDiscount());

            const auto& purchasedItems = purchase.getPurchaseItem();
            itemCountPerPurchases.emplace_back(purchasedItems.size());
            for(const auto& item : purchasedItems) {
                itemIds.emplace_back(item.ID);
                itemNames.emplace_back(item.name);
                itemCounts.emplace_back(item.count);
                itemUnitPrices.emplace_back(item.unitPrice);
                itemSumPrices.emplace_back(item.sumPrice);
                itemRealPrices.emplace_back(item.realPrice);
            }
        }

        rapidcsv::Document csvDetails;

        csvDetails.SetColumnName(0, "Date");
        csvDetails.SetColumnName(1, "Time");
        csvDetails.SetColumnName(2, "Purchase ID");
        csvDetails.SetColumnName(3, "Customer ID");
        csvDetails.SetColumnName(4, "Item Name");
        csvDetails.SetColumnName(5, "Item ID");
        csvDetails.SetColumnName(6, "Unit Price");
        csvDetails.SetColumnName(7, "Count");
        csvDetails.SetColumnName(8, "Sum Price");
        csvDetails.SetColumnName(9, "Real Price");

        std::size_t itemEntriesCount = m_vec.size();   // ????
        std::size_t rowCount = 0;
        for(std::size_t i = 0; i < itemEntriesCount; ++i) {
            for(unsigned short j = 0; j < itemCountPerPurchases[i]; ++j) {
                csvDetails.SetCell<std::string>(0, rowCount, dates[i]);
                csvDetails.SetCell<std::string>(1, rowCount, times[i]);
                csvDetails.SetCell<std::string>(2, rowCount, ids[i]);
                csvDetails.SetCell<std::string>(3, rowCount, customerIds[i]);
                ++rowCount;
            }

        }

        csvDetails.SetColumn(4, itemNames);
        csvDetails.SetColumn(5, itemIds);
        csvDetails.SetColumn(6, itemUnitPrices);
        csvDetails.SetColumn(7, itemCounts);
        csvDetails.SetColumn(8, itemSumPrices);
        csvDetails.SetColumn(9, itemRealPrices);

        csvDetails.Save(m_csvPath);
        csvDetails.Clear();
        itemNames.clear();
        itemIds.clear();
        itemCounts.clear();
        itemSumPrices.clear();
        itemRealPrices.clear();

        rapidcsv::Document csvBrief;

        csvBrief.SetColumnName(0, "Date");
        csvBrief.SetColumnName(1, "Time");
        csvBrief.SetColumnName(2, "Purchase ID");
        csvBrief.SetColumnName(3, "Customer ID");
        csvBrief.SetColumnName(4, "Total Price");
        csvBrief.SetColumnName(5, "Discount");

        csvBrief.SetColumn(0, dates);
        csvBrief.SetColumn(1, times);
        csvBrief.SetColumn(2, ids);
        csvBrief.SetColumn(3, customerIds);
        csvBrief.SetColumn(4, totalPrices);
        csvBrief.SetColumn(5, discounts);

        csvBrief.Save(m_purchaseBriefCSVPath);

        return true;

    } catch (const std::exception& e) {
        std::cerr << "Fail to export to the CSV file:" << e.what() << std::endl;
        return false;
    }
}
