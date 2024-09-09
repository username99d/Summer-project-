#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <limits>  // For input validation

using namespace std;

// Base class: FoodItem
class FoodItem {
protected:
    string name;
    double price;

public:
    FoodItem(string n, double p) : name(n), price(p) {}

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }
};

// Derived classes
class MainCourse : public FoodItem {
public:
    MainCourse(string n, double p) : FoodItem(n, p) {}
};

class Dessert : public FoodItem {
public:
    Dessert(string n, double p) : FoodItem(n, p) {}
};

class Beverage : public FoodItem {
public:
    Beverage(string n, double p) : FoodItem(n, p) {}
};

// Class for managing the order
class Order {
private:
    unordered_map<string, pair<FoodItem*, int>> items;
    double total;

public:
    Order() : total(0) {}

    ~Order() {
        for (auto& item : items) {
            delete item.second.first;
        }
    }

    void addItem(FoodItem* item, int quantity) {
        string name = item->getName();
        if (items.find(name) != items.end()) {
            items[name].second += quantity;
        } else {
            items[name] = make_pair(item, quantity);
        }
        total += item->getPrice() * quantity;
    }

    void displayBill() const {
        const int nameWidth = 30;
        const int qtyWidth = 10;
        const int priceWidth = 15;
        const int totalWidth = 15;

        // Restaurant Information
        string restaurantName = "SXC KITCHEN";
        string restaurantAddress = "Address: Maitighar, Kathmandu";
        int totalWidthHeader = max(nameWidth, (int)restaurantName.length()) + qtyWidth +
            priceWidth + totalWidth;

        // Print Restaurant Information
        cout << endl;
        cout << string(totalWidthHeader, '*') << endl;
        cout << setw(totalWidthHeader) << setfill(' ') << right << restaurantName << endl;
        cout << setw(totalWidthHeader) << setfill(' ') << right << restaurantAddress << endl;
        cout << string(totalWidthHeader, '*') << endl;

        // Bill Header
        cout << "\nItemized Bill\n";
        cout << string(nameWidth + qtyWidth + priceWidth + totalWidth, '-') << endl;
        cout << left << setw(nameWidth) << "Item Name"
            << setw(qtyWidth) << "Quantity"
            << setw(priceWidth) << "Unit Price(₹)"
            << setw(totalWidth) << "Total Price(₹)" << endl;
        cout << string(nameWidth + qtyWidth + priceWidth + totalWidth, '-') << endl;

        // Display each item
        for (const auto& item : items) {
            cout << left << setw(nameWidth) << item.first
                << setw(qtyWidth) << item.second.second
                << setw(priceWidth) << fixed << setprecision(2) << item.second.first->getPrice()
                << setw(totalWidth) << fixed << setprecision(2) << item.second.first->getPrice() *
                item.second.second << endl;
        }

        cout << string(nameWidth + qtyWidth + priceWidth + totalWidth, '-') << endl;
        cout << right << setw(nameWidth + qtyWidth + priceWidth) << "Overall Total: ₹" <<
            fixed << setprecision(2) << total << endl;
        cout << endl;

        // Thank You Message
        cout << string(totalWidthHeader, '*') << endl;
        cout << setw(totalWidthHeader) << setfill(' ') << right << "Thank you for dining with us!" << endl;
        cout << setw(totalWidthHeader) << setfill(' ') << right << "We look forward to serving you again." << endl;
        cout << string(totalWidthHeader, '*') << endl;
    }
};

// Function to print restaurant header for menus
void printRestaurantHeader() {
    string restaurantName = "SXC KITCHEN";
    string restaurantAddress = "Address: Maitighar, Kathmandu";
    int totalWidthHeader = 50; // Adjust width as needed

    cout << endl;
    cout << string(totalWidthHeader, '*') << endl;
    cout << setw(totalWidthHeader) << setfill(' ') << right << restaurantName << endl;
    cout << setw(totalWidthHeader) << setfill(' ') << right << restaurantAddress << endl;
    cout << string(totalWidthHeader, '*') << endl;
}

// Function for input validation
void clearInvalidInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to take user input for main courses
void takeMainCourseOrder(Order& order) {
    int choice, quantity;
    do {
        printRestaurantHeader();
        cout << "\nMain Course Menu\n";
        cout << string(50, '-') << endl;
        cout << "1. Pizza - ₹350.00\n";
        cout << "2. Momo - ₹120.00\n";
        cout << "3. Burger - ₹200.00\n";
        cout << "0. Done with Main Course\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (!cin) {
            clearInvalidInput();
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (choice >= 1 && choice <= 3) {
            cout << "Enter quantity: ";
            cin >> quantity;

            if (!cin) {
                clearInvalidInput();
                cout << "Invalid input. Please enter a valid number.\n";
                continue;
            }

            switch (choice) {
            case 1:
                order.addItem(new MainCourse("Pizza", 350.00), quantity);
                cout << "Pizza added to order.\n";
                break;
            case 2:
                order.addItem(new MainCourse("Momo", 120.00), quantity);
                cout << "Momo added to order.\n";
                break;
            case 3:
                order.addItem(new MainCourse("Burger", 200.00), quantity);
                cout << "Burger added to order.\n";
                break;
            }
        } else if (choice == 0) {
            cout << "Finished ordering Main Course.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Function to take user input for desserts
void takeDessertOrder(Order& order) {
    int choice, quantity;
    do {
        printRestaurantHeader();
        cout << "\nDessert Menu\n";
        cout << string(50, '-') << endl;
        cout << "1. Chocolate Cake - ₹150.00\n";
        cout << "2. Tiramisu - ₹200.00\n";
        cout << "3. Creme Brulee - ₹250.00\n";
        cout << "0. Done with Desserts\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (!cin) {
            clearInvalidInput();
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (choice >= 1 && choice <= 3) {
            cout << "Enter quantity: ";
            cin >> quantity;

            if (!cin) {
                clearInvalidInput();
                cout << "Invalid input. Please enter a valid number.\n";
                continue;
            }

            switch (choice) {
            case 1:
                order.addItem(new Dessert("Chocolate Cake", 150.00), quantity);
                cout << "Chocolate Cake added to order.\n";
                break;
            case 2:
                order.addItem(new Dessert("Tiramisu", 200.00), quantity);
                cout << "Tiramisu added to order.\n";
                break;
            case 3:
                order.addItem(new Dessert("Creme Brulee", 250.00), quantity);
                cout << "Creme Brulee added to order.\n";
                break;
            }
        } else if (choice == 0) {
            cout << "Finished ordering Desserts.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Function to take user input for beverages
void takeBeverageOrder(Order& order) {
    int choice, quantity;
    do {
        printRestaurantHeader();
        cout << "\nBeverage Menu\n";
        cout << string(50, '-') << endl;
        cout << "1. Coffee - ₹50.00\n";
        cout << "2. Coke - ₹40.00\n";
        cout << "3. Virgin Mojito - ₹100.00\n";
        cout << "0. Done with Beverages\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (!cin) {
            clearInvalidInput();
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (choice >= 1 && choice <= 3) {
            cout << "Enter quantity: ";
            cin >> quantity;

            if (!cin) {
                clearInvalidInput();
                cout << "Invalid input. Please enter a valid number.\n";
                continue;
            }

            switch (choice) {
            case 1:
                order.addItem(new Beverage("Coffee", 50.00), quantity);
                cout << "Coffee added to order.\n";
                break;
            case 2:
                order.addItem(new Beverage("Coke", 40.00), quantity);
                cout << "Coke added to order.\n";
                break;
            case 3:
                order.addItem(new Beverage("Virgin Mojito", 100.00), quantity);
                cout << "Virgin Mojito added to order.\n";
                break;
            }
        } else if (choice == 0) {
            cout << "Finished ordering Beverages.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Main function
int main() {
    Order myOrder;

    // Take orders for each category
    takeMainCourseOrder(myOrder);
    takeDessertOrder(myOrder);
    takeBeverageOrder(myOrder);

    // Display the final bill
    myOrder.displayBill();

    return 0;
}
