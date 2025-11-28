//
// Created on 2025/11/27.
//

#include "core/collections/member_collection.hpp"
#include "utils/csv/csv.hpp"

constexpr int propertyCount = 5;

bool MemberCollection::importFromCSV() {
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
                auto tel = csv.GetCell<std::string>(2, i);
                auto points = csv.GetCell<unsigned int>(3, i);
                auto secondaryID = csv.GetCell<std::string>(4,i);

                if (id.empty()) {
                    continue;
                }

                if(secondaryID.empty()) {
                    m_vec.emplace_back(std::make_shared<Member>(id, name, tel, points));
                } else {
                    auto pm = std::make_shared<PremierMember>(id, name, tel, points, secondaryID);
                    m_vec.emplace_back(pm);
                }

            } catch (const std::exception& e) {
                std::cerr << "Error when loading members in row " << i << "\n";
                continue;
            }
        }

        return true;

    } catch (const std::exception& e) {
        std::cerr << "Failed to load the file:" << e.what() << std::endl;
        return false;
    }
}

bool MemberCollection::exportToCSV() {
    try {
        rapidcsv::Document csv;

        csv.SetColumnName(0, "ID");
        csv.SetColumnName(1, "Name");
        csv.SetColumnName(2, "Price");
        csv.SetColumnName(3, "Stock");

        std::vector<std::string> ids;
        std::vector<std::string> names;
        std::vector<std::string> tels;
        std::vector<unsigned int> points;
        std::vector<std::string> secondaryIDs;

        ids.reserve(m_vec.size());
        names.reserve(m_vec.size());
        tels.reserve(m_vec.size());
        points.reserve(m_vec.size());
        secondaryIDs.reserve(m_vec.size());

        for (auto& member : m_vec) {
            ids.emplace_back(member -> getID());
            names.emplace_back(member -> getName());
            tels.emplace_back(member -> getTel());
            points.emplace_back(member -> getPoints());

            if(member -> isPremier()) {
                auto premier = std::dynamic_pointer_cast<PremierMember>(member);
                secondaryIDs.emplace_back(premier -> getSecondaryID());
            } else {
                secondaryIDs.emplace_back("");
            }
        }

        csv.SetColumn(0, ids);
        csv.SetColumn(1, names);
        csv.SetColumn(2, tels);
        csv.SetColumn(3, points);
        csv.SetColumn(4, secondaryIDs);

        csv.Save(m_csvPath);

        return true;

    } catch (const std::exception& e) {
        std::cerr << "Fail to export to the CSV file:" << e.what() << std::endl;
        return false;
    }
}