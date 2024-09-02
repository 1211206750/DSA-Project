#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

struct Customer {
    string username;
    string password;
    string fullname;
    string gender;
    string phoneNumber;
    string email;
};

struct Pizza {
    int id;
    string name;
    double price;

    // Constructor
    Pizza(int _id, const string& _name, double _price) : id(_id), name(_name), price(_price) {}

    // Operator overloading for sorting by name
    bool operator<(const Pizza& other) const {
        return name < other.name;
    }

    // Operator overloading for sorting by price
    bool operator>(const Pizza& other) const {
        return price > other.price;
    }

    // Operator overloading for sorting by id
    bool operator==(int _id) const {
        return id == _id;
    }
};

void clearScreen();
void displayHomePage();
void displayAdminInterface();
void displayCustomerInterface(Customer& newCustomer);
void registerCustomer(Customer& newCustomer);
void forgetPassword();
void loginCustomerInterface();
bool loginCustomer(const string& username, const string& password, Customer& loggedInCustomer);
void displayCustomerMenu(Customer& loggedInCustomer);
void editCustomerProfile(Customer& loggedInCustomer);
bool binarySearchByName(const vector<Pizza>& menu, const string& searchPizza);
void selectionSortByName(vector<Pizza>& menu);
void insertionSortByPrice(vector<Pizza>& menu);
void displayPizzaMenu();
void viewCart();
void deletecartorder();
int binarySearchById(const vector<Pizza>& menu, int searchId);
void addToOrder(const Pizza& pizza, Customer& loggedInCustomer);
void displayOrderConfirmation();
void initializeTransactionCount(int &transactionCount);

int main() {
    int choice;
    Customer newCustomer; // Declare newCustomer here
    static int transactionCount = 0;
    initializeTransactionCount(transactionCount);

    do {
        clearScreen();
        displayHomePage();

        cout << endl << "Enter your choice: ";
        cin >> choice;

        clearScreen();

        switch (choice) {
            case 1:
                displayAdminInterface();
                break;
            case 2:
                displayCustomerInterface(newCustomer); // Pass newCustomer by reference
                break;
            case 0:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please choose again." << endl;
                break;
        }

        // Wait for user to press Enter before clearing screen
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();

    } while (choice != 0);

    return 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayHomePage() {
    clearScreen();
	cout << "======================================================" << endl;
    cout << "\tWelcome to G20 Pizza System" << endl;
    cout << "======================================================" << endl;
    cout << endl << endl << "Hello." << endl << endl;
    cout << "[1] Admin" << endl;
    cout << "[2] Customer" << endl;
    cout << "[0] Exit Program" << endl;
}

void displayAdminInterface() {
    cout << "Admin interface coming soon..." << endl;
    // Implement admin functionality here if needed
}

void displayCustomerInterface(Customer& newCustomer) {
    int customerChoice;

    do {
        cout << "======================================================" << endl;
        cout << "\tWelcome to G20 Pizza System" << endl;
        cout << "======================================================" << endl;
        cout << endl << endl << "Hello Customer." << endl << endl;
        cout << "[1] Login" << endl;
        cout << "[2] Register" << endl;
        cout << "[3] Forget Password" << endl;
        cout << "[0] Back" << endl << endl;
        cout << "Enter your choice: ";
        cin >> customerChoice;

        clearScreen();

        switch (customerChoice) {
            case 1:
                loginCustomerInterface();
                break;
            case 2:
                registerCustomer(newCustomer);
                break;
            case 3:
                forgetPassword();
                break;
            case 0:
                cout << "[Enter] again to back to Home page." << endl;
                break;
            default:
                cout << "Invalid choice. Please choose again." << endl;
                break;
        }

    } while (customerChoice != 0);
}

void registerCustomer(Customer& newCustomer) {
    cout << "======================================================" << endl;
    cout << "\tWelcome to G20 Pizza System" << endl;
    cout << "======================================================" << endl<<endl;
    
	cout << "Customer Registration Page" << endl;

    cout << "Enter a username: ";
    cin >> newCustomer.username;

    cout << "Enter a password: ";
    cin >> newCustomer.password;

    cout << "Enter your full name: ";
    cin.ignore();
    getline(cin, newCustomer.fullname);

    cout << "Enter your gender: ";
    cin >> newCustomer.gender;

    cout << "Enter your phone number: ";
    cin >> newCustomer.phoneNumber;

    cout << "Enter your email: ";
    cin >> newCustomer.email;

    // Open file for writing
    ofstream outFile("customer.txt", ios::app); // Append mode

    // Check if the file opened successfully
    if (!outFile) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    // Write customer details to the file
    outFile << "Username: " << newCustomer.username << endl;
    outFile << "Password: " << newCustomer.password << endl;
    outFile << "Full Name: " << newCustomer.fullname << endl;
    outFile << "Gender: " << newCustomer.gender << endl;
    outFile << "Phone Number: " << newCustomer.phoneNumber << endl;
    outFile << "Email: " << newCustomer.email << endl;
    outFile << endl;

    // Close the file
    outFile.close();

    // Display registration success message
    cout << "Registration successful for " << newCustomer.username << ".\n";

    // Wait for user to press Enter
    cout << "Press Enter to continue...";
    cin.ignore(); // Ignore any characters in the buffer
    cin.get(); // Wait for Enter key

    clearScreen();

    // Go to the customer page
    displayCustomerInterface(newCustomer);
}

void forgetPassword() {
    string username;
    string line;
    bool found = false;

    cout << "======================================================" << endl;
    cout << "\tForget Password" << endl;
    cout << "======================================================" << endl << endl;
    cout << "Enter your username to retrieve your password: ";
    cin >> username;

    ifstream inFile("customer.txt");

    if (!inFile) {
        cerr << "Error: Unable to open file for reading." << endl;
        return;
    }

    while (getline(inFile, line)) {
        if (line.find("Username: " + username) != string::npos) {
            getline(inFile, line); // Move to the next line (password)
            cout << "\nYour password is found.\n";
            cout << "Your current password is: " << line.substr(line.find(": ") + 2) << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Username not found. Please try again." << endl;
    }

    inFile.close();

    cout << "\nEnter [0] to back to customer page: ";
    int choice;
    cin >> choice;
    if (choice == 0) {
        clearScreen();
        Customer newCustomer;
        displayCustomerInterface(newCustomer);
    }
}

void loginCustomerInterface() { 
    string username, password;
    Customer loggedInCustomer;

    cout << "======================================================" << endl;
    cout << "\tWelcome to G20 Pizza System" << endl;
    cout << "======================================================" << endl << endl << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (loginCustomer(username, password, loggedInCustomer)) {
        cout << "Login successful." << endl;
        // Wait for user to press Enter
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        clearScreen();
        displayCustomerMenu(loggedInCustomer); // Display customer menu after login
    } else {
        cout << "Invalid username or password. Please try again." << endl;
    }
}

bool loginCustomer(const string& username, const string& password, Customer& loggedInCustomer) {
    string line;
    ifstream inFile("customer.txt");

    // Check if the file opened successfully
    if (!inFile) {
        cerr << "Error: Unable to open file for reading." << endl;
        return false;
    }

    // Read each line of the file
    while (getline(inFile, line)) {
        // Check if the line contains the username
        if (line.find("Username: " + username) != string::npos) {
            getline(inFile, line); // Move to the next line (password)
            if (line.find("Password: " + password) != string::npos) {
                loggedInCustomer.username = username;

                // Read the rest of the customer details
                getline(inFile, line); loggedInCustomer.fullname = line.substr(line.find(": ") + 2);
                getline(inFile, line); loggedInCustomer.gender = line.substr(line.find(": ") + 2);
                getline(inFile, line); loggedInCustomer.phoneNumber = line.substr(line.find(": ") + 2);
                getline(inFile, line); loggedInCustomer.email = line.substr(line.find(": ") + 2);

                inFile.close();
                return true; // Username and password match
            }
        }
    }

    // Username or password not found
    inFile.close();
    return false;
}

void displayCustomerMenu(Customer& loggedInCustomer) {
    int customerChoice;

    do {
        cout << "======================================================" << endl;
        cout << "\tWelcome to G20 Pizza System" << endl;
        cout << "======================================================" << endl;
        cout << endl << endl << "Hello Customer." << endl << endl;
        cout << "[1] Customer Profile" << endl;
        cout << "[2] Menu" << endl;
        cout << "[0] Logout" << endl << endl;
        cout << "Enter your choice: ";
        cin >> customerChoice;

        clearScreen();

        switch (customerChoice) {
            case 1:
                 editCustomerProfile(loggedInCustomer);
                break;
            case 2:
                displayPizzaMenu();
                break;
            case 0:
                cout << "[Enter] again to log out." << endl;
                break;
            default:
                cout << "Invalid choice. Please choose again." << endl;
                break;
        }

        // Wait for user to press Enter before clearing screen
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        clearScreen();

    } while (customerChoice != 0);
}

void editCustomerProfile(Customer& loggedInCustomer) {
    int choice;

    // Display current profile details
    cout << "======================================================" << endl;
    cout << "\tWelcome to G20 Pizza System" << endl;
    cout << "======================================================" << endl;
    cout << "\nCustomer Profile: " << endl << endl;
    cout << "Username: " << loggedInCustomer.username << endl;
    cout << "Full Name: " << loggedInCustomer.fullname << endl;
    cout << "Gender: " << loggedInCustomer.gender << endl;
    cout << "Phone Number: " << loggedInCustomer.phoneNumber << endl;
    cout << "Email: " << loggedInCustomer.email << endl;

    cout << "\nDo you want to edit? [1] Yes [0] Back to customer menu\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        // Edit profile details
        cout << "Enter new full name (or press [Enter] to keep current): ";
        cin.ignore();  // Clear input buffer
        string newFullName;
        getline(cin, newFullName);
        if (!newFullName.empty()) {
            loggedInCustomer.fullname = newFullName;
        }

        cout << "Enter new gender (or press [Enter] to keep current): ";
        string newGender;
        getline(cin, newGender);
        if (!newGender.empty()) {
            loggedInCustomer.gender = newGender;
        }

        cout << "Enter new phone number (or press [Enter] to keep current): ";
        string newPhoneNumber;
        getline(cin, newPhoneNumber);
        if (!newPhoneNumber.empty()) {
            loggedInCustomer.phoneNumber = newPhoneNumber;
        }

        cout << "Enter new email (or press [Enter] to keep current): ";
        string newEmail;
        getline(cin, newEmail);
        if (!newEmail.empty()) {
            loggedInCustomer.email = newEmail;
        }

        // Update the customer.txt file with new details
        ifstream inFile("customer.txt");
        ofstream outFile("temp.txt");

        if (!inFile || !outFile) {
            cerr << "Error: Unable to open file." << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            if (line.find("Username: " + loggedInCustomer.username) != string::npos) {
                outFile << "Username: " << loggedInCustomer.username << endl;
                // Retrieve and preserve the password
                getline(inFile, line);
                outFile << line << endl;  // Write the preserved password
                outFile << "Full Name: " << loggedInCustomer.fullname << endl;
                outFile << "Gender: " << loggedInCustomer.gender << endl;
                outFile << "Phone Number: " << loggedInCustomer.phoneNumber << endl;
                outFile << "Email: " << loggedInCustomer.email << endl;
                outFile << endl;

                // Skip the next 4 lines in the original file (they are already written)
                for (int i = 0; i < 4; ++i) {
                    getline(inFile, line);
                }
            } else {
                outFile << line << endl;
            }
        }

        inFile.close();
        outFile.close();

        // Replace the old file with the new file
        remove("customer.txt");
        rename("temp.txt", "customer.txt");

        cout << "\nProfile updated successfully." << endl;
    }
}

void displayPizzaMenu() {
    ifstream menuFile("menu.txt");

    if (!menuFile) {
        cerr << "Error: Unable to open menu file." << endl;
        return;
    }

    string line;
    vector<Pizza> menu;

    // Read menu items from file
    while (getline(menuFile, line)) {
        cout << "Read line from menu file: " << line << endl; // Debugging output

        istringstream iss(line);
        int id;
        string name;
        double price;
        char comma;

        if (iss >> id >> comma && getline(iss, name, ',') && iss >> price) {
            cout << "Parsed pizza details: ID=" << id << ", Name=" << name << ", Price=" << price << endl; // Debugging output
            menu.push_back(Pizza(id, name, price));
        } else {
            cerr << "Error reading menu entry: " << line << endl;
        }
    }

    menuFile.close();


    int choice;
    do {
        clearScreen();
        cout << "======================================================" << endl;
        cout << "\tPizza Menu" << endl;
        cout << "======================================================" << endl << endl;
        cout << "------------------------------------------------------" << endl;
        cout << left << setw(4) << "ID" << setw(50) << "Choose Your Pizza" << setw(20) << "Price" << endl;
        cout << "------------------------------------------------------" << endl;

        // Display menu items
        for (size_t i = 0; i < menu.size(); ++i) {
            cout << left << setw(4) << menu[i].id << setw(50) << menu[i].name << "RM " << fixed << setprecision(2) << menu[i].price << endl;
        }

        // Additional options
        cout << "\n[1] Sort by Name" << endl;
        cout << "[2] Sort by Price" << endl;
        cout << "[3] Search Pizza ID to add order" << endl;
        cout << "[4] View Cart"<<endl;        
        cout << "[0] Back to Customer Interface" << endl;

        // Handle user choice
        cout << "\nEnter your choice : ";
        cin >> choice;
        

        switch (choice) {
            case 1:
                clearScreen();
				selectionSortByName(menu);
                break;
            case 2:
                clearScreen();
				insertionSortByPrice(menu);
                break;
            case 3: {
                int searchId;
                cout << "Enter the ID of the pizza to search: ";
                cin >> searchId;
                cout << endl;

                // Perform binary search
                int foundIndex = binarySearchById(menu, searchId);

                if (foundIndex != -1) {
                    cout << "Pizza found in the menu:" << endl;
                    cout << "ID: " << menu[foundIndex].id << endl;
                    cout << "Name: " << menu[foundIndex].name << endl;
                    cout << "Price: RM " << fixed << setprecision(2) << menu[foundIndex].price << endl;

                    // Ask user if they want to add this pizza to their order
                    cout << "\nDo you want to add this pizza to your order?" << endl;
                    cout << "[1] Yes, absolutely" << endl;
                    cout << "[0] No, go back" << endl;
                    cout << "Your Choice: ";
                    int addChoice;
                    cin >> addChoice;

                    if (addChoice == 1) {
                        // Prompt for quantity
                        int quantity;
                        cout << "Enter quantity: ";
                        cin >> quantity;
						
						if (!quantity>=1)
                        {	cout<<"Enter the number properly."<<endl;
                        	cout << "Enter quantity: ";
                        	cin >> quantity;
						}
                        // Add pizza to cart.txt with quantity
                        ofstream cartFile("cart.txt", ios::app); // Append mode

                        if (!cartFile) {
                            cerr << "Error: Unable to open cart file for writing." << endl;
                            return;
                        }

                        // Write pizza details to cart.txt
                        cartFile << "ID: " << menu[foundIndex].id<<endl;
                        cartFile << "Name: " << menu[foundIndex].name<<endl;
                        cartFile << "Price: RM " << fixed << setprecision(2) << menu[foundIndex].price<<endl;
                        cartFile << "Quantity: " << quantity<<endl;
                        cartFile << endl;

                        cartFile.close();

                        cout << "Pizza added to your cart successfully." << endl;

                        // Provide options to choose another pizza or confirm order
                        cout << "\nDo you need to try another flavour? :" << endl;
                        cout << "[1] Sounds Good. Let's choose another pizza." << endl;
                        cout << "[2] Sounds enough. Let's view cart." << endl;
                        cout << "Your Choice: ";
                        int continueChoice;
                        cin >> continueChoice;
						
						
						switch (continueChoice) {
						    case 1:
						        // Continue to choose another pizza
						        break; // Exit switch, continue do-while loop
						    case 2:
						        clearScreen();
								viewCart();
						        cout << "\nEnter your Choice :" << endl;
		                        cout << "[1] Back to menu again." << endl;
		                        cout << "[2] Remove a pizza." << endl;
		                        cout << "[3] Go to Payment." << endl;
		                        cout << "Your Choice: ";
		                        int billChoice;
		                        cin >> billChoice;
		                        switch (billChoice) {
						            case 1:
						                displayPizzaMenu();;
						                break;
						            case 2:
						                deletecartorder();
						                break;
						            case 3:
						                displayOrderConfirmation();
						                break;
						            
						            default:
						                cout << "Invalid choice. Please try again." << endl;
						                break;
						        }
		                        
						}
                        
                    }
                } else {
                    cout << "Pizza not found in the menu." << endl;
                }
                break;
            }
            case 4:
                viewCart();
                break;
                                
            case 0:
                cout << "Returning to customer interface..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        // Wait for user to press Enter before clearing screen
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        clearScreen();

    } while (choice != 0);
}

void viewCart() {
    ifstream cartFile("cart.txt");

    if (!cartFile) {
        cerr << "Error: Unable to open cart file for reading." << endl;
        return;
    }

    cout << "======================================================" << endl;
    cout << "\tYour Shopping Cart" << endl;
    cout << "======================================================" << endl << endl;

    string line;
    while (getline(cartFile, line)) {
        cout << line << endl;
    }

    cartFile.close();
}

void deletecartorder() {
    ifstream cartFile("cart.txt");

    if (!cartFile) {
        cerr << "Error: Unable to open cart file for reading." << endl;
        return;
    }

    vector<string> orders;
    string line;
    int index = 0;

    // Read all orders into a vector
    while (getline(cartFile, line)) {
        orders.push_back(line);
        
        cout << "[" << index +1<< "] " << line <<endl;
        cout << line <<endl;
        cout << line <<endl;
        cout << line <<endl;
		index++;
    }

    cartFile.close();

    if (orders.empty()) {
        cout << "Your cart is empty." << endl;
        return;
    }

    int orderNumber;
    cout << "Enter the number of the order you want to remove: ";
    cin >> orderNumber;

    if (orderNumber < 1 || orderNumber > orders.size()) {
        cout << "Invalid order number." << endl;
        return;
    }

    // Remove the selected order
    orders.erase(orders.begin() + orderNumber - 1);

    // Write the remaining orders back to the file
    ofstream outFile("cart.txt");
    if (!outFile) {
        cerr << "Error: Unable to open cart file for writing." << endl;
        return;
    }

    for (const auto& order : orders) {
        outFile << order << endl;
    }

    outFile.close();

    cout << "Order removed successfully." << endl;
}

int binarySearchById(const vector<Pizza>& menu, int searchId) {
    int left = 0;
    int right = menu.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;  // Calculate midpoint

        if (menu[mid].id == searchId) {
            return mid; // Found the pizza at index 'mid'
        } else if (menu[mid].id < searchId) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }

    return -1; // Pizza not found
    
    
    
}

void selectionSortByName(vector<Pizza>& menu) {
    size_t n = menu.size();

    for (size_t i = 0; i < n - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (menu[j].name < menu[minIndex].name) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            // Manual swap
            Pizza temp = menu[i];
            menu[i] = menu[minIndex];
            menu[minIndex] = temp;
        }
    }

    // Display sorted menu items
    cout << "======================================================" << endl;
    cout << "\tSorted Pizza Menu by Name" << endl;
    cout << "======================================================" << endl << endl;
    cout << "------------------------------------------------------" << endl;
    cout << left << setw(4) << "ID" << setw(50) << "Choose Your Pizza" << setw(20) << "Price" << endl;
    cout << "------------------------------------------------------" << endl;

    for (size_t i = 0; i < menu.size(); ++i) {
        cout << left << setw(4) << menu[i].id << setw(50) << menu[i].name << "RM " << fixed << setprecision(2) << menu[i].price << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
        cin.get();
        clearScreen();
    displayPizzaMenu();
}

void insertionSortByPrice(vector<Pizza>& menu) {
    size_t n = menu.size();

    for (size_t i = 1; i < n; ++i) {
        Pizza key = menu[i];
        size_t j = i;
        while (j > 0 && menu[j - 1].price > key.price) {
            menu[j] = menu[j - 1];
            --j;
        }
        menu[j] = key;
    }

    // Display sorted menu items
    cout << "======================================================" << endl;
    cout << "\tSorted Pizza Menu by Price" << endl;
    cout << "======================================================" << endl << endl;
    cout << "------------------------------------------------------" << endl;
    cout << left << setw(4) << "ID" << setw(50) << "Choose Your Pizza" << setw(20) << "Price" << endl;
    cout << "------------------------------------------------------" << endl;

    for (size_t i = 0; i < menu.size(); ++i) {
        cout << left << setw(4) << menu[i].id << setw(50) << menu[i].name << "RM " << fixed << setprecision(2) << menu[i].price << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
        cin.get();
        clearScreen();
    displayPizzaMenu();
}

void displayOrderConfirmation() {
    ifstream cartFile("cart.txt");

    if (!cartFile) {
        cerr << "Error: Unable to open cart file for reading." << endl;
        return;
    }

    
    
    ofstream dailyFile("daily.txt", ios::app); // Append mode

    if (!dailyFile) {
        cerr << "Error: Unable to open daily file for writing." << endl;
        cartFile.close();
        return;
    }
    
    ofstream confirmFile("confirm.txt", ios::app);

    if (!confirmFile) {
        cerr << "Error: Unable to open confirm file for writing." << endl;
        cartFile.close();
        return;
    }
    
	double totalPrice = 0.0;
    string line;
    static int transactionCount = 1000;
    transactionCount++;
    
    // Display header
    cout << "=================================================================================================" << endl;
    cout << "\t\t\tG20 Pizza Shop" << endl;
    cout << "=================================================================================================" << endl;
    cout << endl;
    cout << "Order Number : " << transactionCount<<endl<<endl;
    cout << left << setw(10) << "Pizza ID" << setw(40) << "Name" << setw(20) << "Price" << setw(10) << "Qty" << setw(20) << "Total Price" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

    // Read and display each pizza entry from cart.txt
    while (getline(cartFile, line)) {
        if (line.find("ID:") != string::npos) {
            int id;
            string name;
            double price;
            int quantity;

            // Extract pizza details
            if (sscanf(line.c_str(), "ID: %d", &id) == 1) {
                getline(cartFile, line); // Read next line (Name)
                if (line.find("Name:") != string::npos) {
                    name = line.substr(line.find(":") + 2); // Extract name
                }
                getline(cartFile, line); // Read next line (Price)
                if (line.find("Price:") != string::npos) {
                    sscanf(line.c_str(), "Price: RM %lf", &price); // Extract price
                }
                getline(cartFile, line); // Read next line (Quantity)
                if (line.find("Quantity:") != string::npos) {
                    sscanf(line.c_str(), "Quantity: %d", &quantity); // Extract quantity
                }

                // Calculate total price for this pizza
                double totalPriceForPizza = price * quantity;
                totalPrice += totalPriceForPizza;

                // Display pizza details
                cout << left << setw(10) << id << setw(40) << name << setw(20) << fixed << setprecision(2) << price << setw(10) << quantity << setw(20) << totalPriceForPizza << endl;
                confirmFile <<transactionCount<<"," << id << "," << name << "," << quantity << endl;
            }
        }
    }

    cartFile.close();
    confirmFile.close();

    // Display total price
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << right << setw(80) << "Total Price (RM) : " << fixed << setprecision(2) << totalPrice << endl;
    cout << "=================================================================================================" << endl;

    // Save total price to daily.txt
    //static int transactionCount = 1000;
    //transactionCount++;
    dailyFile << transactionCount << "," << fixed << setprecision(2) << totalPrice << endl;

    dailyFile.close();

    // Clear cart.txt by reopening it in truncate mode
    ofstream clearCartFile("cart.txt", ios::trunc);
    clearCartFile.close();
    cout << "\nThank You...";
    cin.ignore();
    cin.get();
    clearScreen();
    displayHomePage();
}

void initializeTransactionCount(int &transactionCount) {
    ifstream dailyFile("daily.txt");
    string line;
    if (dailyFile.is_open()) {
        while (getline(dailyFile, line)) {
            if (!line.empty()) {
                transactionCount++;
            }
        }
        dailyFile.close();
    }
}
