#include <iostream>
#include <string>
using namespace std;

const int MAX_USERS = 1;
const int NUM_CATEGORIES = 6;
const int ITEMS_PER_CATEGORY = 2;

void enterUserData(long long cardNumbers[], string cardholderNames[], string expirationDates[], int cvvs[], double creditLimits[], double currentBalances[], int& numUsers);
void displayCategories();
void displayItemsInCategory(int category, string items[][ITEMS_PER_CATEGORY], double prices[][ITEMS_PER_CATEGORY]);
double getPriceOfItem(int category, int index, double prices[][ITEMS_PER_CATEGORY]);
int checkItemAvailability(int itemId, int itemStock[]);
bool processPayment(int userId, double amount, double currentBalances[], double creditLimits[]);
void updateCardBalance(int userId, double amount, double currentBalances[]);
void updateInventory(int itemId, int itemStock[]);
void addNewUser(long long cardNumbers[], string cardholderNames[], string expirationDates[], int cvvs[], double creditLimits[], double currentBalances[], int& numUsers);
void displayPurchaseHistory(int userId, int purchaseHistory[][NUM_CATEGORIES * ITEMS_PER_CATEGORY], const string items[][ITEMS_PER_CATEGORY]);



void displayMenu() {
    cout << "----- Menu -----" << endl;
        cout << "1. Add user" << endl;
        cout << "2. Make a purchase" << endl;
        cout << "3. View purchase history" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
    
}

int main() {
    long long cardNumbers[MAX_USERS];
    string cardholderNames[MAX_USERS];
    string expirationDates[MAX_USERS];
    int cvvs[MAX_USERS];
    double creditLimits[MAX_USERS];
    double currentBalances[MAX_USERS];
    int numUsers = 0;

    int itemStock[NUM_CATEGORIES * ITEMS_PER_CATEGORY] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
    int purchaseHistory[MAX_USERS][NUM_CATEGORIES * ITEMS_PER_CATEGORY] = { 0 };
    string items[NUM_CATEGORIES][ITEMS_PER_CATEGORY] = {
      {"Apples", "Bananas"},
      {"T-Shirt", "Jeans"},
      {"Aspirin", "Vitamin C"},
      {"Laptop", "Smartphone"},
      {"Milk", "Eggs"},
      {"Novel", "Magazine"}
    };


    double prices[NUM_CATEGORIES][ITEMS_PER_CATEGORY] = {
     {1.99, 0.99},
     {15.0, 50.0},
     {6.0, 12.0},
     {999.0, 799.0},
     {3.5, 2.0},
     {20.0, 5.0}
    };
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            if (numUsers < MAX_USERS) {
                int userId = numUsers;
                enterUserData(cardNumbers, cardholderNames, expirationDates, cvvs, creditLimits, currentBalances, numUsers);
                numUsers++;
            }
            else {
                cout << "User limit reached. Cannot add more users." << endl;
            }
            break;
        }
        case 2: {
            displayCategories();
            cout << "Enter the category number: ";
            int selectedCategory;
            cin >> selectedCategory;

            displayItemsInCategory(selectedCategory, items, prices);
            cout << "Enter the item number: ";
            int selectedItem;
            cin >> selectedItem;

            int itemId = (selectedCategory - 1) * ITEMS_PER_CATEGORY + (selectedItem - 1);
            if (checkItemAvailability(itemId, itemStock)) {
                cout << "Enter your user ID (1-" << numUsers << "), or type 0 to add a new user: ";
                int userId;
                cin >> userId;

                if (userId == 0) {
                    addNewUser(cardNumbers, cardholderNames, expirationDates, cvvs, creditLimits, currentBalances, numUsers);  //bonus feature
                    cout << "New user added successfully. Enter your user ID (1-" << numUsers << "): ";
                    cin >> userId;
                }

                userId--;
                double amount = getPriceOfItem(selectedCategory, selectedItem, prices);

                cout << "Enter your credit card number: ";
                long long inputCardNumber;
                cin >> inputCardNumber;

               cout << "Enter your name" << endl;
               string name;
               cin >> name;
               
               cout << "Cvv: ";
               int cv;
               cin >> cv;
               cout << "Expiration date: ";
               string date;
               cin >> date;

                bool validUser = false;
                for (int i = 0; i < numUsers; i++) {
                    if ((inputCardNumber == cardNumbers[i]) && (name==cardholderNames[i])&&(cv==cvvs[i])&&(date==expirationDates[i])) {
                        validUser = true;
                        userId = i;
                        break;
                    }
                }

                if (validUser) {
                    if (processPayment(userId, amount, currentBalances, creditLimits)) {
                        updateCardBalance(userId, amount, currentBalances);
                        updateInventory(itemId, itemStock);
                        purchaseHistory[userId][itemId]++;
                        cout << "Purchase successful. " << items[selectedCategory - 1][selectedItem - 1] << " remaining stock: " << itemStock[itemId] << endl;
                        double remainingBalance = creditLimits[userId] - currentBalances[userId];
                        cout << "Remaining credit card balance for user " << userId + 1 << ": $" << remainingBalance << endl;
                    }
                    else {
                        cout << "The selected item is not available." << endl;
                    }
                }
                else {
                    cout << "Invalid credit card credentials. Please try again." << endl;
                }
            }
            else {
                cout << "The selected item is out of stock." << endl;
            }
            break;
        }
        case 3: {
            cout << "Enter your user ID (1-" << numUsers << "): ";
            int userId;
            cin >> userId;
            userId--; 

            if (userId >= 0 && userId < numUsers) {
                displayPurchaseHistory(userId, purchaseHistory, items);
            }
            else {
                cout << "Invalid user ID." << endl;
            }

            break;
        }
        case 4: {
            cout << "Exiting the program." << endl;
            break;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    } while (choice != 4);

    return 0;
}




void enterUserData(long long cardNumbers[], string cardholderNames[], string expirationDates[], int cvvs[], double creditLimits[], double currentBalances[], int& numUsers) 
{
    
    for (int i = 0; i < MAX_USERS; i++) {
        cout << "Enter details for user " << (i + 1) << ":\n";
        cout << "Card number: ";
        cin >> cardNumbers[i];
        cin.ignore();
        cout << "Cardholder name: ";
        getline(cin, cardholderNames[i]);
        cout << "Expiration date: ";
        getline(cin, expirationDates[i]);
        cout << "CVV: ";
        cin >> cvvs[i];
        cout << "Credit limit: ";
        cin >> creditLimits[i];
        currentBalances[i] = 0;
        numUsers++;
    }
}

void displayCategories() {
    cout << "Categories:\n";
    cout << "1. FRUITS\n";
    cout << "2. CLOTHING\n";
    cout << "3. MEDICINE\n";
    cout << "4. TECHNOLOGY\n";
    cout << "5. DAIRY\n";
    cout << "6. BOOKS\n";
}

void displayItemsInCategory(int category, string items[][ITEMS_PER_CATEGORY], double prices[][ITEMS_PER_CATEGORY]) {
    cout << "Items in Category " << category << ":\n";
    for (int i = 0; i < ITEMS_PER_CATEGORY; i++) {
        cout << (i + 1) << ". " << items[category - 1][i] << " - $" << prices[category - 1][i] << endl;
    }
}

double getPriceOfItem(int category, int index, double prices[][ITEMS_PER_CATEGORY]) {
    return prices[category - 1][index - 1];
}

int checkItemAvailability(int itemId, int itemStock[]) {
    
	
	return itemStock[itemId] > 0;
}

bool processPayment(int userId, double amount, double currentBalances[], double creditLimits[]) {
    if (currentBalances[userId] + amount <= creditLimits[userId]) {
        return true;
    }
    else {
        cout << "Insufficient balance!" << endl;
        return false;
    }
}

void updateCardBalance(int userId, double amount, double currentBalances[]) {
    currentBalances[userId] += amount;
    cout << "Card balance updated successfully!" << endl;
}

void updateInventory(int itemId, int itemStock[]) {
    itemStock[itemId]--;
    cout << "Inventory updated successfully!" << endl;
}

void addNewUser(long long cardNumbers[], string cardholderNames[], string expirationDates[], int cvvs[], double creditLimits[], double currentBalances[], int& numUsers) {  //BONUS FEATURE
    if (numUsers >= MAX_USERS) {
        cout << "User limit reached. Cannot add a new user." << endl;
        return;
    }
    cout << "Enter the following details for the new user:" << endl;
    enterUserData(cardNumbers, cardholderNames, expirationDates, cvvs, creditLimits, currentBalances, numUsers);
}
void displayPurchaseHistory(int userId, int purchaseHistory[][NUM_CATEGORIES * ITEMS_PER_CATEGORY], const string items[][ITEMS_PER_CATEGORY]) {  //Bonus feature
    cout << "Purchase history for user " << userId + 1 << ":" << endl;

    for (int i = 0; i < NUM_CATEGORIES * ITEMS_PER_CATEGORY; i++) {
        if (purchaseHistory[userId][i] > 0) {
            cout << items[i / ITEMS_PER_CATEGORY][i % ITEMS_PER_CATEGORY] << ": " << purchaseHistory[userId][i] << endl;
        }
    }
}

