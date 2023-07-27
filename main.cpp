#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Product structure
struct Product {
    string name;
    int quantity;
    double price;
};

// Function to calculate the total amount
double calculateTotal(const vector<Product>& cart) {
    double total = 0.0;
    for (const auto& product : cart) {
        total += product.price * product.quantity;
    }
    return total;
}

// Function to display the receipt
void printReceipt(const vector<Product>& cart, double totalAmount) {
    cout << "-------------------------" << endl;
    cout << "         RECEIPT         " << endl;
    cout << "-------------------------" << endl;

    for (const auto& product : cart) {
        cout << product.name << " x " << product.quantity << " : Ksh" << product.price * product.quantity << endl;
    }

    cout << "-------------------------" << endl;
    cout << "Total amount: Ksh" << totalAmount << endl;
    cout << "-------------------------" << endl;
}

class Interface {
public:
    Interface(const vector<Product>& catalog) : catalog_(catalog) {}

    char getUserRole();

    void displaySellerMenu() const;

    void displaySupplierMenu() const;

    int getProductChoice() const;

    int getQuantity() const;

    void displayLowStockMessage() const;

    void displayReceipt(const vector<Product>& cart, double totalAmount) const;

private:
    const vector<Product>& catalog_;
};

char Interface::getUserRole() {
    char userRole;
    cout << "Welcome to Raze Agrovet POS Terminal!" << endl;
    cout << "Are you a Buyer (B), Seller (S), or Supplier (P)? Enter 'B', 'S', or 'P': ";
    cin >> userRole;
    return userRole;
}

void Interface::displaySellerMenu() const {
    cout << "-------------------------" << endl;
    cout << "       SELLER'S MENU      " << endl;
    cout << "-------------------------" << endl;
    cout << "Code  Product           Price     Remaining" << endl;
    cout << "-----------------------------------------" << endl;

    for (int i = 0; i < catalog_.size(); i++) {
        cout << setw(2) << i << "    " << setw(15) << catalog_[i].name << " Ksh7" << setw(6) << fixed << setprecision(2) << catalog_[i].price << "   " << catalog_[i].quantity << endl;
    }
}

void Interface::displaySupplierMenu() const {
    cout << "-------------------------" << endl;
    cout << "       SUPPLIER'S MENU      " << endl;
    cout << "-------------------------" << endl;
    cout << "Contact Information: Zetechsuppliers@gmail.com" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Product           Price     Available" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Fertilizer         Ksh1400   1400" << endl;
    cout << "Pesticide          Ksh2100   600" << endl;
    cout << "Bean seeds         Ksh700    900" << endl;
    cout << "Poultry Feed       Ksh1500   1800" << endl;
    cout << "Maize seeds        Ksh1600   1500" << endl;
    cout << "Acaricides         Ksh2000   2000" << endl;
    cout << "Herbicides         Ksh300    2000" << endl;
    cout << "Aqua feed premix   Ksh600    1400" << endl;
    cout << "Animal supplements Ksh350    1900" << endl;
    cout << "Pig feed           Ksh1450   1700" << endl;
    cout << "Horse feed         Ksh2200   800" << endl;
}

int Interface::getProductChoice() const {
    int productCode;
    cout << "Enter the product code: ";
    cin >> productCode;
    return productCode;
}

int Interface::getQuantity() const {
    int quantity;
    cout << "Enter the quantity: ";
    cin >> quantity;
    return quantity;
}

void Interface::displayLowStockMessage() const {
    cout << "Warning: Low stock! Please contact the supplier for restocking." << endl;
}

void Interface::displayReceipt(const vector<Product>& cart, double totalAmount) const {
    printReceipt(cart, totalAmount);
}

int main() {
    vector<Product> cart;
    char choice;

    vector<Product> catalog = {
        {"Fertilizer", 50, 1400},
        {"Pesticide", 30, 2100},
        {"Bean seeds", 100, 700},
        {"Livestock Feed", 20, 1200},
        {"Poultry Feed", 80, 1700},
        {"Maize seeds", 150, 1800},
        {"Acaricides", 40, 2300},
        {"Herbicides", 50, 500},
        {"Aqua feed premix", 80, 900},
        {"Animal supplements", 110, 600},
        {"Pig feed", 50, 1600},
        {"Horse feed", 30, 2200},
    };

    Interface interface(catalog);

    char userRole = interface.getUserRole();

    if (userRole == 'S') {
        // Seller's menu
        interface.displaySellerMenu();
    } else if (userRole == 'P') {
        // Supplier's menu
        interface.displaySupplierMenu();
    } else if (userRole != 'B') {
        cout << "Invalid choice. Exiting the program." << endl;
        return 0;
    }

    do {
        // Display the product menu and get user input for product code and quantity
        int productCode = interface.getProductChoice();
        int quantity = interface.getQuantity();

        if (productCode >= 0 && productCode < catalog.size() && quantity > 0 && quantity <= catalog[productCode].quantity) {
            Product selectedProduct = catalog[productCode];
            selectedProduct.quantity = quantity;
            cart.push_back(selectedProduct);
            catalog[productCode].quantity -= quantity;
            cout << "Product added to the cart successfully!" << endl;

            if (catalog[productCode].quantity < 5) {
                interface.displayLowStockMessage();
            }
        } else {
            cout << "Invalid product code or quantity. Please try again." << endl;
        }

        cout << "Do you want to add more products? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y');

    double totalAmount = calculateTotal(cart);

    interface.displayReceipt(cart, totalAmount);

    return 0;
}

