#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <vector>

using namespace std;

struct Pizza {
    int id;
    string name;
    double price;
};

void clearScreen();
void displayAdminInterface();
void registeradmin();
void loginadmin();
void forgetadminPassword();
void displayAdminMenu();
void editPizzaMenu();
vector<Pizza> loadMenu();
void saveMenu(const vector<Pizza>& menu);
void displayCustomerOrders();
void hashSearchByOrderID(const vector<vector<string>>& orders, int searchID);
void quicksortByOrderID(vector<vector<string>>& orders, int low, int high);
int partition(vector<vector<string>>& orders, int low, int high);
void merge(vector<vector<string>>& orders, int left, int mid, int right);
void mergesortByPizzaName(vector<vector<string>>& orders, int left, int right);

void displayDailyOrder();
void viewMenu();


// Base class User
class User {
protected:
    string name;
    string email;
    string password;
public:
    User(string n, string e, string p) : name(n), email(e), password(p) {}
    virtual void displayInfo() {
        cout << "Name: " << name << "\nEmail: " << email << endl;
    }
    friend void displayEmail(User &u);
    string getEmail() { return email; }
    string getPassword() { return password; }
};

void displayEmail(User &u) {
    cout << "Friend function accessing email: " << u.email << endl;
}

// Derived class Admin
class Admin : public User {
public:
    Admin(string n, string e, string p) : User(n, e, p) {}
    void displayInfo() override {
        cout << "Admin Name: " << name << "\nEmail: " << email << endl;
    }
};

// Linked List Node
struct UserNode {
    User *user;
    UserNode *next;
    UserNode(User *u) : user(u), next(nullptr) {}
};

// Linked List
class UserList {
private:
    UserNode *head;
public:
    UserList() : head(nullptr) {}
    
    void addUser(User *u) {
        UserNode *newNode = new UserNode(u);
        newNode->next = head;
        head = newNode;
    }

    void displayUsers() {
        UserNode *current = head;
        while (current != nullptr) {
            current->user->displayInfo();
            current = current->next;
        }
    }

    ~UserList() {
        UserNode *current = head;
        while (current != nullptr) {
            UserNode *temp = current;
            current = current->next;
            delete temp->user;
            delete temp;
        }
    }
};

int main() {
    displayAdminInterface();
    return 0;
}

void displayAdminInterface() {
    int choice;
    do {
        cout << "======================================================" << endl;
        cout << "\tWelcome to G20 Pizza System" << endl;
        cout << "======================================================" << endl;
        cout << endl << endl << "Hello Admin." << endl << endl;
        cout << "[1] Register" << endl;
        cout << "[2] Login" << endl;
        cout << "[3] Forget Password" << endl;
        cout << "[0] Back" << endl << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearScreen();
        switch (choice) {
            case 1:
                registeradmin();
                clearScreen();
                break;
            case 2:
                loginadmin();
                clearScreen();
                break;
            case 3:
                forgetadminPassword();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void registeradmin() {
    string name, email, password;
    cout << "======================================================" << endl;
        cout << "\tWelcome to G20 Pizza System" << endl;
        cout << "======================================================" << endl;
        cout << endl << endl << "Hello Admin." << endl << endl;
        cout << "Enter name: ";
    cin >> name;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    ofstream outfile("admin.txt", ios::app); // Append mode
    if (outfile.is_open()) {
        outfile << name << " " << email << " " << password << endl;
        outfile.close();
        cout << "User registered successfully!\n";
    } else {
        cout << "Error opening file for writing.\n";
    }
    
    cin.ignore();
    cin.get();
}

void loginadmin() {
    string name, password, fileName, fileEmail, filePassword;
    bool loginSuccess = false;

    cout << "======================================================" << endl;
        cout << "\tWelcome to G20 Pizza System" << endl;
        cout << "======================================================" << endl;
        cout << endl << endl << "Hello Admin." << endl << endl;
        
        cout << "Enter name: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> password;

    ifstream infile("admin.txt");
    if (infile.is_open()) {
        while (infile >> fileName >> fileEmail >> filePassword) {
            if (name == fileName && password == filePassword) {
                cout << "Login successful! Welcome, " << fileName << "\n";
                loginSuccess = true;
                cin.ignore();
                cin.get();
                clearScreen();
                break;
            }
        }
        infile.close();
        if (!loginSuccess) {
            cout << "Invalid name or password.\n";
        } else {
            displayAdminMenu();
        }
    } else {
        cout << "Error opening file for reading.\n";
    }

    cin.ignore();
    cin.get();
}

void forgetadminPassword() {
    string name;
    string line;
    bool found = false;

    cout << "======================================================" << endl;
    cout << "\tAdmin Forget Password" << endl;
    cout << "======================================================" << endl << endl;
    cout << "Enter your name to get your register details: ";
    cin >> name;

    ifstream inFile("admin.txt");

    if (!inFile) {
        cerr << "Error: Unable to open file for reading." << endl;
        return;
    }

    while (getline(inFile, line)) {
        stringstream ss(line);
        string userName, email, password;

        ss >> userName >> email >> password;

        if (userName == name) {
            cout << "\nYour password is found.\n";
            cout << "Your current password is: " << password << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Username not found. Please try again." << endl;
    }

    inFile.close();

    cout << "\nEnter [0] to back : ";
    int choice;
    cin >> choice;
    if (choice == 0) {
        clearScreen();
        displayAdminInterface();
    }
}

void displayAdminMenu() {
    int choice;
    do {
    	clearScreen();
        cout << "======================================================" << endl;
        cout << "\tAdmin Menu" << endl;
        cout << "======================================================" << endl;
        cout << "[1] Edit Pizza Menu" << endl;
        cout << "[2] Display Customer Order" << endl;
        cout << "[3] Summarize Daily Income Bill" << endl;
        cout << "[0] Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                editPizzaMenu();
                break;
            case 2:
                displayCustomerOrders();
                break;
            case 3:
                displayDailyOrder();
                break;
            case 0:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

vector<Pizza> loadMenu() {
    vector<Pizza> menu;
    ifstream infile("menu.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            Pizza pizza;
            ss >> pizza.id;
            ss.ignore(); // Ignore the comma
            getline(ss, pizza.name, ',');
            ss >> pizza.price;
            menu.push_back(pizza);
        }
        infile.close();
    } else {
        cout << "Error opening file for reading.\n";
    }
    return menu;
}

void saveMenu(const vector<Pizza>& menu) {
    ofstream outfile("menu.txt");
    if (outfile.is_open()) {
        for (const auto& pizza : menu) {
            outfile << pizza.id << "," << pizza.name << "," << pizza.price << endl;
        }
        outfile.close();
    } else {
        cout << "Error opening file for writing.\n";
    }
}

void editPizzaMenu() {
    vector<Pizza> menu = loadMenu();
    int choice;
    do {
        clearScreen();
        cout << "======================================================" << endl;
        cout << "\tEdit Pizza Menu" << endl;
        cout << "======================================================" << endl;
        cout << "[1] Add Pizza" << endl;
        cout << "[2] Edit Pizza Details" << endl;
        cout << "[3] Delete Pizza" << endl;
        cout << "[4] View Menu" <<endl;
        cout << "[0] Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearScreen();
        switch (choice) {
            case 1: {
                Pizza newPizza;
                cout << "Enter Pizza ID: ";
                cin >> newPizza.id;
                cout << "Enter Pizza Name: ";
                cin.ignore();
                getline(cin, newPizza.name);
                cout << "Enter Pizza Price: ";
                cin >> newPizza.price;
                menu.push_back(newPizza);
                saveMenu(menu);
                cout << "Pizza added successfully.\n";
                break;
            }
            case 2: {
                int id;
                cout << "Enter Pizza ID to edit: ";
                cin >> id;
                bool found = false;
                for (auto& pizza : menu) {
                    if (pizza.id == id) {
                        found = true;
                        cout << "Enter new Pizza Name: ";
                        cin.ignore();
                        getline(cin, pizza.name);
                        cout << "Enter new Pizza Price: ";
                        cin >> pizza.price;
                        saveMenu(menu);
                        cout << "Pizza details updated successfully.\n";
                        break;
                    }
                }
                if (!found) {
                    cout << "Pizza with ID " << id << " not found.\n";
                }
                break;
            }
            case 3: {
                int id;
                cout << "Enter Pizza ID to delete: ";
                cin >> id;
                bool found = false;
                for (size_t i = 0; i < menu.size(); ++i) {
                    if (menu[i].id == id) {
                        menu.erase(menu.begin() + i);
                        saveMenu(menu);
                        found = true;
                        cout << "Pizza deleted successfully.\n";
                        break;
                    }
                }
                if (!found) {
                    cout << "Pizza with ID " << id << " not found.\n";
                }
                break;
            }
            case 4:
    		viewMenu();
    		break;

            case 0:
            	displayAdminMenu();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        cin.ignore();
        cin.get();
    } while (choice != 0);
}

void displayCustomerOrders() {
    clearScreen();

    ifstream confirmFile("confirm.txt");
    if (!confirmFile) {
        cerr << "Error: Unable to open confirm.txt for reading." << endl;
        return;
    }

    string line;
    vector<vector<string>> orders;

    // Read data from file
    while (getline(confirmFile, line)) {
        stringstream ss(line);
        vector<string> order(4);
        getline(ss, order[0], ','); // Read Order ID
        getline(ss, order[1], ','); // Read Pizza ID
        getline(ss, order[2], ','); // Read Pizza Name
        getline(ss, order[3], ','); // Read Quantity
        orders.push_back(order);
    }
    confirmFile.close();

    int choice;
    cout << "Choose action:\n";
    cout << "[1] Sort by Order ID\n";
    cout << "[2] Sort by Pizza Name\n";
    cout << "[3] Search by Order ID\n";
    cout << "[0] Back\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        quicksortByOrderID(orders, 0, orders.size() - 1);
    } else if (choice == 2) {
        mergesortByPizzaName(orders, 0, orders.size() - 1);
    } else if (choice == 3) {
        int searchID;
        cout << "Enter Order ID to search: ";
        cin >> searchID;
        hashSearchByOrderID(orders, searchID);
    }else if (choice == 0) {
    	displayAdminMenu();
    }
    	

    // Display header for sorted or searched data
    clearScreen();
    cout << "===================================================================" << endl;
    cout << "\t\tCustomer Orders" << endl;
    cout << "===================================================================" << endl;
    cout << left << setw(10) << "Order ID" << setw(10) << "Pizza ID" << setw(30) << "Pizza Name" << setw(10) << "Quantity" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    // Display sorted or searched data
    for (const auto& order : orders) {
        cout << left << setw(10) << order[0] << setw(10) << order[1] << setw(30) << order[2] << setw(10) << order[3] << endl;
    }

    cout << "===================================================================" << endl;
    cin.ignore();
    cin.get();
    displayCustomerOrders();
}

void hashSearchByOrderID(const vector<vector<string>>& orders, int searchID) {
    unordered_map<int, vector<vector<string>>> orderHash;

    // Populate the hash table
    for (const auto& order : orders) {
        int orderId = stoi(order[0]);
        orderHash[orderId].push_back(order);
    }

    // Search for the order
    auto it = orderHash.find(searchID);
    if (it != orderHash.end()) {
        // Display header
        cout << "===================================================================" << endl;
        cout << "\t\tSearch Result by Order ID: " << searchID << endl;
        cout << "===================================================================" << endl;
        cout << left << setw(10) << "Order ID" << setw(10) << "Pizza ID" << setw(30) << "Pizza Name" << setw(10) << "Quantity" << endl;
        cout << "-------------------------------------------------------------------" << endl;

        // Print found orders
        for (const auto& order : it->second) {
            cout << left << setw(10) << order[0] << setw(10) << order[1] << setw(30) << order[2] << setw(10) << order[3] << endl;
        }
    } else {
        cout << "Order with ID " << searchID << " not found." << endl;
    }

    cout << "===================================================================" << endl;
    
    cin.ignore();
    cin.get();
    displayCustomerOrders();
}

void quicksortByOrderID(vector<vector<string>>& orders, int low, int high) {
    if (low < high) {
        int pi = partition(orders, low, high);
        quicksortByOrderID(orders, low, pi - 1);
        quicksortByOrderID(orders, pi + 1, high);
    }
}

int partition(vector<vector<string>>& orders, int low, int high) {
    int pivot = stoi(orders[high][0]);
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (stoi(orders[j][0]) < pivot) {
            i++;
            swap(orders[i], orders[j]);
        }
    }
    swap(orders[i + 1], orders[high]);
    return (i + 1);
}

void merge(vector<vector<string>>& orders, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<vector<string>> leftArr(n1);
    vector<vector<string>> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = orders[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = orders[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i][2] <= rightArr[j][2]) {
            orders[k] = leftArr[i];
            i++;
        } else {
            orders[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        orders[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        orders[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergesortByPizzaName(vector<vector<string>>& orders, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesortByPizzaName(orders, left, mid);
        mergesortByPizzaName(orders, mid + 1, right);
        merge(orders, left, mid, right);
    }
    
}

void displayDailyOrder() {
    clearScreen();
	
	ifstream dailyFile("daily.txt");

    if (!dailyFile) {
        cerr << "Error: Unable to open daily file for reading." << endl;
        return;
    }

    double totalDailySales = 0.0;
    string line;

    cout << "=================================================================================================" << endl;
    cout << "\t\t\tG20 Pizza Shop - Daily Income By Price" << endl;
    cout << "=================================================================================================" << endl;
    cout << left << setw(40) << "Order ID " << setw(20) << "Total Price (RM)" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

    while (getline(dailyFile, line)) {
        istringstream iss(line);
        string orderNumber, totalPriceStr;

        if (getline(iss, orderNumber, ',') && getline(iss, totalPriceStr)) {
            double totalPrice = stod(totalPriceStr);  // Convert string to double
            totalDailySales += totalPrice;
            cout << left << setw(40) << orderNumber << setw(20) << fixed << setprecision(2) << totalPrice << endl;
        } else {
            cerr << "Error reading line: " << line << endl;
        }
    }

    dailyFile.close();

    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << right << setw(40) << "Total Daily Income (RM): " << fixed << setprecision(2) << totalDailySales << endl;
    cout << "=================================================================================================" << endl;

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    clearScreen();
}

void viewMenu() {
    clearScreen();
    vector<Pizza> menu = loadMenu();

    cout << "======================================================" << endl;
    cout << "\t\tG20 Pizza Menu" << endl;
    cout << "======================================================" << endl;
    cout << left << setw(5) << "ID" << setw(40) << "Pizza Name" << setw(10) << "Price" << endl;
    cout << "------------------------------------------------------" << endl;

    for (const auto& pizza : menu) {
        cout << left << setw(5) << pizza.id << setw(40) << pizza.name << setw(10) << fixed << setprecision(2) << pizza.price << endl;
    }

    cout << "======================================================" << endl;

    cin.ignore();
    cin.get();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
