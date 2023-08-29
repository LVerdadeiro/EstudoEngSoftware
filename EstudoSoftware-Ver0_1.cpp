#include<iostream>
#include<string>
#include<vector>

class Employee{
public:
    std::string empCode = "emp01";
};

class Manager: public Employee{
public:
    std::string admCode = "adm00";
};

class Product{
public:
    std::string prod_name;
    float price;
    int productCode;
};

class Sale{
public:
    float value;
    std::string CPFconsumer;
    std::vector<Product> productList;
    std::string employeeCode;

    void addProduct(const Product& product) {
        productList.push_back(product);
    }

    double calculateTotalPrice() const {
        double total = 0.0;
        for (const Product& product : productList) {
            total += product.price;
        }
        return total;
    }
};

Employee Emp;
Manager ADM;

int closeCashier(){
    int confirmOption;
    std::cout << "Are you sure you want to close this cashier? [1] Yes | [2] No" << std::endl;
    std::cin >> confirmOption;

    if(confirmOption == 1){
        std::cout << "Closing cashier unit..." << std::endl;
        return 0;
    }
    else if(confirmOption == 2)
        return 1;
    else {
        std::cout << "[ERROR] Please insert a valid option." << std::endl;
        return 1;
    }
}

int getPaymentOption() {
    int paymentOption;
    std::cout << "Please select payment method:" << std::endl << "[1] Credit [2] Debit [3] Cash" << std::endl;
    std::cin >> paymentOption;
    return paymentOption;
}

void processPayment(int paymentOption) {
    std::string paymentMethod[3] = {"Credit", "Debit", "Cash"};
    if (paymentOption >= 1 && paymentOption <= 3) {
        std::cout << paymentMethod[paymentOption - 1] << " Option Selected. Processing Payment..." << std::endl;
        std::cout << "Payment confirmed, please come again" << std::endl;
    } else {
        std::cout << "Invalid payment option, please insert a valid option" << std::endl;
    }
}

int mainMenu() {
    int optionSelect;
    std::cout << "Select an option below:" << std::endl;
    std::cout << "[1] - Conclude a sale" << std::endl;
    std::cout << "[2] - Close cashier unit" << std::endl;
    std::cin >> optionSelect;
    return optionSelect;
}



void concludeSales() {
    Sale sale;

    char addMoreProducts;
    do {
        Product newProduct;

        std::cout << "Enter product name: ";
        std::cin.ignore();
        std::getline(std::cin, newProduct.prod_name);
        

        std::cout << "Enter product price: ";
        std::cin >> newProduct.price;
        

        std::cout << "Enter product code: ";
        std::cin >> newProduct.productCode;
        
        
        sale.addProduct(newProduct);
        
        std::cout << "Do you want to add more products? (y/n): ";
        std::cin >> addMoreProducts;

    } while (addMoreProducts == 'y' || addMoreProducts == 'Y');

    double totalPrice = sale.calculateTotalPrice();

    std::cout << "Total Price of this purchase: $" << totalPrice << std::endl;

    int paymentOption = getPaymentOption();
    processPayment(paymentOption);
}


void openCashier() {
    std::string code;
    int optionSelect;
    do {
        std::cout << "|                 GEN/ERIC SYSTEMS                  |" << std::endl;
        std::cout << "|Please, insert employee code to open this cashier: |" << std::endl;
        std::getline(std::cin, code);

        if(code == Emp.empCode){
            std::cout << "Cashier opened successfully!" << std::endl;
            do {
                optionSelect = mainMenu();
                if(optionSelect == 1)
                    concludeSales();
                else if(optionSelect == 2)
                    closeCashier();
                else
                    std::cout << "[ERROR] Invalid option detected. Please select again." << std::endl;
            } while (optionSelect != 1 && optionSelect != 2);
            
        } else if(code == ADM.admCode) {
            std::cout << "Admin section opened." << std::endl;
        } else {
            std::cout << "[ERROR] Access Denied. Please insert a valid code." << std::endl;
        }
    } while (code != Emp.empCode && code != ADM.admCode);
}

int main() {
    openCashier();
    return 0;
}
