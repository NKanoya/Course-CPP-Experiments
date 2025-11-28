//
// Created on 2025/11/28.
//

#include "core/shop.hpp"
#include <limits>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string readString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;

    std::getline(std::cin >> std::ws, input);
    return input;
}

template<typename T>
T readNumeric(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInput();
            return value;
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
        }
    }
}

void Shop::operation() {
    std::string buf;
    char ch;

    while (true) {
        std::cout << "\n========================================\n";
        std::cout << "Shop Main Menu:\n";
        std::cout << "\t[a] Item Management\n";
        std::cout << "\t[b] Member Management & Registration\n";
        std::cout << "\t[c] New Transaction (Purchase)\n";
        std::cout << "\t[d] Display Purchases History\n";
        std::cout << "\t[q] Quit\n";
        std::cout << "Enter operation choice: ";

        if (!(std::cin >> buf) || buf.empty()) {
            clearInput();
            continue;
        }
        ch = std::tolower(buf[0]);

        clearInput();

        switch (ch) {
            case 'a':
                // Item Management Sub-Menu
            {
                std::cout << "\n--- Item Management ---\n";
                std::cout << "\t[1] Add New Item\n";
                std::cout << "\t[2] Display All Items\n";
                std::cout << "\t[b] Back to Main Menu\n";
                std::cout << "Enter item operation: ";
                if (!(std::cin >> buf) || buf.empty()) { clearInput(); break; }
                char item_ch = std::tolower(buf[0]);
                clearInput();

                if (item_ch == '1') {
                    std::string name = readString("Enter Item Name: ");
                    std::string price_val = readNumeric<std::string>("Enter Unit Price: ");
                    Price price = Price::convertFromString(price_val);

                    unsigned int stock = readNumeric<unsigned int>("Enter Initial Stock: ");

                    Item& newItem = addItem(name, price, stock);
                    std::cout << "\nItem added successfully! ID: " << newItem.getID() << "\n";
                } else if (item_ch == '2') {
                    std::cout << "\n--- All Items ---\n";
                    displayItems(std::cout);
                }
            }
                break;

            case 'b':
                // Member Management Sub-Menu
            {
                std::cout << "\n--- Member Management ---\n";
                std::cout << "\t[1] Register New Member\n";
                std::cout << "\t[2] Display All Members\n";
                std::cout << "\t[3] Display All Premier Members\n";
                std::cout << "\t[b] Back to Main Menu\n";
                std::cout << "Enter member operation: ";
                if (!(std::cin >> buf) || buf.empty()) { clearInput(); break; }
                char member_ch = std::tolower(buf[0]);
                clearInput();

                if (member_ch == '1') {
                    int type = readNumeric<int>("Enter type (0 for Regular, 1 for Premier): ");
                    bool isPremier = (type == 1);
                    unsigned int points = readNumeric<unsigned int>("Enter Initial Points: ");

                    Customer* newMember = registerMember(isPremier, points);
                    std::cout << "\nMember registered! Type: " << (isPremier ? "PREMIER" : "REGULAR") << ", ID: " << newMember->getID() << "\n";
                } else if (member_ch == '2') {
                    std::cout << "\n--- All Members ---\n";
                    displayMembers(std::cout);
                } else if (member_ch == '3') {
                    std::cout << "\n--- Premier Members ---\n";
                    displayPremiers(std::cout);
                }
            }
                break;

            case 'c':
                // New Transaction (Simplified)
            {
                std::cout << "\n--- New Transaction ---\n";
                std::string memberID = readString("Enter Member ID (or press \'0\' for non-member): \n");

                std::vector<CartItem> cart;
                std::cout << "Starting shopping cart (Enter 'done' to finish):\n";

                while (true) {
                    std::string itemID = readString("Enter Item ID (or 'done'): ");
                    if (std::tolower(itemID[0]) == 'd') break;
                    auto itemPtr = m_itemCollection.getEntry(itemID);
                    if(!itemPtr) continue;

                    unsigned int count = readNumeric<unsigned int>("Enter Count: ");

                    cart.emplace_back( itemPtr, count);
                    std::cout << "Item added to cart.\n";
                }

                if (cart.empty()) {
                    std::cout << "Transaction cancelled.\n";
                } else if (memberID == "0") {
                    auto purchase = transaction(cart);
                    if(!purchase) {
                        break;
                    }

                    std::cout << "\nNon-member transaction completed.\n";
                    std::cout << *purchase << '\n';
                } else {
                    auto purchase = transaction(memberID, cart);
                    std::cout << "\nMember transaction completed.\n";
                    std::cout << *purchase << '\n';
                }
            }
                break;

            case 'd':
            {
                std::cout << "\n--- Purchase History ---\n";
                std::cout << "\t[1] Show member's history:\n";
                std::cout << "\t[2] Show unregistered customers' history:\n";
                std::cout << "\t[3] Show All History:\n";
                std::cout << "\t[b] Back to Main Menu\n";
                std::cout << "Enter member operation: ";
                if (!(std::cin >> buf) || buf.empty()) { clearInput(); break; }
                char member_ch = std::tolower(buf[0]);
                clearInput();

                if (member_ch == '1') {
                    std::string ID = readString("Please input your ID: ");
                    // clearInput();
                    int i = 1;
                    for(auto& purchase: m_purchaseCollection) {
                        if(purchase.getCustomerID() == ID) {
                            std::cout << i << " | " << purchase << '\n';
                            i++;
                        }
                    }
                    break;
                } else if (member_ch == '2') {
                    std::cout << "\n--- Unregistered Customers' Purchases ---\n";
                    for(auto& purchase: m_purchaseCollection) {
                        int i = 0;
                        if(purchase.getCustomerID().starts_with("CUST")) {
                            std::cout << i << " | " << purchase << '\n';
                        }
                    }
                    break;
                } else if (member_ch == '3') {
                    std::cout << "\n--- All Purchases ---\n";
                    displayPurchases(std::cout);
                    break;
                }
            }
                break;

            case 'q':
                std::cout << "\nExiting Shop Management System.\n";
                return;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}