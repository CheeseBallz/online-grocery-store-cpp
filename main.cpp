
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 20;  // global variable

// Global variables for user account (Module 1)
string name, email, username, password;

// Global variables for shopping cart (Module 2)
string cart[SIZE];
float qty[SIZE] = {0};
int itemIndex[SIZE];
int cartCount = 0;
int loyaltyPoints = 0;

// Store inventory (Module 2)
string items[SIZE] = {"apple","banana","milk","bread","rice","eggs","chicken","tomato","tea","oil","sugar","salt","butter","cheese","onion","potato","orange","coffee","fish","meat"};
int prices[SIZE] = {200,210,220,180,400,300,310,600,1100,450,120,50,500,800,70,60,150,1300,700,900};
string units[SIZE] = {"kg","dozen","liter","packet","kg","dozen","kg","kg","packet","liter","kg","kg","kg","kg","kg","kg","kg","packet","kg","kg"};

// ========== MODULE 1: USER ACCOUNT MANAGEMENT ==========

//to check password strength
bool passwordstrength(string pass) {
    bool hasdigit = false, hasspecial = false;
    for (int i = 0; i < pass.length(); i++) {
        if (pass[i] >= '0' && pass[i] <= '9') {
            hasdigit = true;
        }
        if (pass[i] == '!' || pass[i] == '@' || pass[i] == '#' ||pass[i] == '$' || pass[i] == '%' || pass[i] == '&') {
            hasspecial = true;
        }
    }
    if (hasdigit && hasspecial) {
        return true;
    }
    else {
        return false;
    }
}

// create new account
void newaccount() {
    cout << "\n--- create new account ---\n";
    cout << "enter name: ";
    getline(cin, name);
    cout << "enter email: ";
    getline(cin, email);
    cout << "enter username: ";
    getline(cin, username);
    while (true) {
        cout << "enter password: ";
        getline(cin, password);
        if (passwordstrength(password)) {
            cout << "account created successfully\n";
            break;
        }
        else {
            cout << "weak password. must contain digit and special character\n";
        }
    }
}

// login system
bool login() {
    string u, p;
    int attempts = 3;
    while (attempts > 0) {
        cout << "\n--- login ---\n";
        cout << "enter username: ";
        getline(cin, u);
        cout << "enter password: ";
        getline(cin, p);
        if (u == username && p == password) {
            cout << "login successful\n";
            return true;
        }
        else {
            attempts--;
            cout << "incorrect credentials. attempts left: " << attempts << endl;
        }
    }
    return false;
}

// account recovery
void recoverpassword() {
    string mail;
    cout << "\n--- account recovery ---\n";
    cout << "enter registered email: ";
    getline(cin, mail);
    if (mail == email) {
        cout << "your password is: " << password << endl;
    }
    else {
        cout << "email not found\n";
    }
}

// change password
void changepassword() {
    string oldpass, newpass;
    cout << "\n--- change password ---\n";
    cout << "enter old password: ";
    getline(cin, oldpass);
    if (oldpass == password) {
        while (true) {
            cout << "enter new password: ";
            getline(cin, newpass);
            if (passwordstrength(newpass)) {
                password = newpass;
                cout << "password changed successfully\n";
                break;
            }
            else {
                cout << "weak password. try again\n";
            }
        }
    }
    else {
        cout << "incorrect old password\n";
    }
}

// display profile
void displayprofile() {
    cout << "\n--- user profile ---\n";
    cout << "name: " << name << endl;
    cout << "email: " << email << endl;
    cout << "username: " << username << endl;
}

// ========== MODULE 2: SHOPPING CART MANAGEMENT ==========

// ---------- SEARCH AND ADD ----------
void searchAndAdd(string items[], int prices[], string units[], string cart[], float qty[], int itemIndex[], int &cartCount, int &loyaltyPoints)
{
    string search;
    cout << "\nEnter item name to search: ";
    cin >> search;

    bool found = false;

    // Search all 20 items
    for (int i = 0; i < 20 ; i++)
    {
        if (items[i] == search)
        {
            found = true;
            cout << items[i] << " is available! Price: Rs." << prices[i] << " per " << units[i] << endl;

            // Check if item already in cart
            bool alreadyInCart = false;
            int cartIndex = -1;   //-1 is impossible as a valid array index
            
            // Check cart items
            for (int j = 0; j < cartCount; j++)
            {
                if (cart[j] == items[i])
                {
                    alreadyInCart = true;
                    cartIndex = j;  // Store cart position
                    break;
                }
            }

            // If already in cart ask to add more
            if (alreadyInCart)
            {
                cout << "You already have this item in cart (Current quantity: " << qty[cartIndex] << " " << units[i] << ")\n";
                cout << "Do you still want to add more? (y/n): ";
                char choice;
                cin >> choice;

                if (choice == 'y' || choice == 'Y')
                {
                    float quantity;
                    cout << "Enter quantity to add (" << units[i] << "): ";
                    cin >> quantity;
                    qty[cartIndex] += quantity;  // Add to existing quantity
                    cout << "Quantity updated in cart.\n";
                }
            }
            else
            {
                // Item not in cart, add new
                char choice;
                cout << "Add to cart? (y/n): ";
                cin >> choice;

                if (choice == 'y' || choice == 'Y')
                {
                    float quantity;
                    cout << "Enter quantity (" << units[i] << "): ";
                    cin >> quantity;

                    cart[cartCount] = items[i];       // add item name
                    qty[cartCount] = quantity;        // add quantity
                    itemIndex[cartCount] = i;         // store original index
                    cartCount++;                      // increment cart count
                    loyaltyPoints += 5;               // loyality points
                    cout << "Item added to cart.\n";
                }
            }
            break;
        }
    }

    if (!found)
        cout << "Item not found!\n"; // searched item not found
}

// ---------- ADD FROM MENU ----------
void addFromMenu(string items[], int prices[], string units[], string cart[], float qty[], int itemIndex[], int &cartCount, int &loyaltyPoints)
{
    // Display all items
    cout << "\nAvailable Items:\n";
    for (int i = 0; i < 20; i++)  // display all 20 items
        cout << i + 1 << ". " << items[i] << " - Rs." << prices[i] << " per " << units[i] << endl;

    int itemNo;
    cout<<endl;
    cout << "Enter item number to add: ";
    cin >> itemNo;

    if (itemNo < 1 || itemNo > SIZE)  // valid item no
    {
        cout << "Invalid item number!\n";
        return;
    }

    int idx = itemNo - 1;  // Convert to array index  

    bool alreadyInCart = false;   // Check if item already in cart 
    int cartIndex = -1;
    
    for (int i = 0; i < cartCount; i++)  // Loop through cart
    {
        if (cart[i] == items[idx])
        {
            alreadyInCart = true;
            cartIndex = i; // remains same
            break;
        }
    }

    if (alreadyInCart) // if still want's to add
    {
        cout << "You already have this item in cart (Current quantity: " << qty[cartIndex] << " " << units[idx] << ")\n";
        cout << "Do you still want to add more? (y/n): ";
        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            float quantity;
            cout << "Enter quantity to add (" << units[idx] << "): ";
            cin >> quantity;
            qty[cartIndex] += quantity;  // Update quantity
            cout << "Quantity updated in cart.\n";
        }
    }
    else
    {
        // Add new item
        float quantity; // float if not whole portion
        cout << "Enter quantity (" << units[idx] << "): ";
        cin >> quantity;

        cart[cartCount] = items[idx];    // add item name
        qty[cartCount] = quantity;       // add quantity
        itemIndex[cartCount] = idx;      // store original
        cartCount++;                     // increment cart count
        loyaltyPoints += 5;              // loyality points
        cout << "Item added to cart.\n";
    }
}

// ---------- VIEW CART ----------
void viewCart(string cart[], float qty[], string units[], int itemIndex[], int cartCount)
{
    if (cartCount == 0)  //empty cart
    {
        cout << "\nCart is empty!\n";
        return;
    }

    cout << "\n===== YOUR CART =====\n";

    for (int i = 0; i < cartCount; i++)  // Loop through cart items only
    {
        int idx = itemIndex[i];  // Get original item index
        cout << i + 1 << ". " << cart[i] << " - " << qty[i] << " " << units[idx] << endl;
    }
}

// ---------- REMOVE ITEM ----------
void removeItem(string cart[], float qty[], int itemIndex[], int &cartCount, int &loyaltyPoints)
{
    if (cartCount == 0)  // empty cart
    {
        cout << "\nCart is empty!\n"; 
        return;
    }

    // Show current cart
    cout << "\nYour Cart:\n";
    for (int i = 0; i < cartCount; i++) //remains withint cart items
        cout << i + 1 << ". " << cart[i] << " - " << qty[i] << endl;

    int removeIndex;
    cout << "Enter item number to remove: ";
    cin >> removeIndex; 

    // Validate input
    if (removeIndex < 1 || removeIndex > cartCount) //check item no
    {
        cout << "Invalid item number!\n";
        return;
    }

    // Shift items left to remove selected item
    for (int i = removeIndex - 1; i < cartCount - 1; i++) 
    {
        cart[i] = cart[i + 1];      // Move next item to current position
        qty[i] = qty[i + 1];
        itemIndex[i] = itemIndex[i + 1];
    }

    cartCount--;             // decrease cart count
    loyaltyPoints -= 5;      // deduct loyality ponts
    if (loyaltyPoints < 0) 
        loyaltyPoints = 0;  // Ensure points never go negative

    cout << "Item removed from cart.\n";
}

// ========== MODULE 3: BILLING, SUPPORT & FEEDBACK ==========

int calculateBill() {
    int total = 0;
    for (int i = 0; i < cartCount; i++) {
        int idx = itemIndex[i];
        total += prices[idx] * qty[i];
    }
    cout << "\nTotal Bill: Rs." << total << endl;
    return total;
}

int applyDiscount(int bill) {
    if (bill > 1000) {
        bill -= bill * 0.025;
        cout << "2.5% discount applied!\n";
    }
    cout << "Final Bill: Rs." << bill << endl;
    return bill;
}

bool isAllDigits(const string &s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

void paymentMethod() {
    int choice;
    string cardNumber;
    int pin;
    string cvv;

    cout << "\nSelect Payment Method:\n";
    cout << "1. Cash on Delivery (COD)\n";
    cout << "2. Card Payment\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Payment method selected: Cash on Delivery (COD)\n";
    }
    else if (choice == 2) {
        while (true) {
            cout << "Enter 16-digit Card Number: ";
            cin >> cardNumber;

            if (cardNumber.length() != 16 || !isAllDigits(cardNumber)) {
                cout << "Wrong Card Number! Must be 16 digits.\n";
            } else {
                break;
            }
        }

        cout << "Enter PIN: ";
        cin >> pin;

        while (true) {
            cout << "Enter 3-digit CVV: ";
            cin >> cvv;

            if (cvv.length() != 3 || !isAllDigits(cvv)) {
                cout << "Wrong CVV! Must be exactly 3 digits.\n";
            } else {
                break;
            }
        }

        cout << "Card payment successful!\n";
    }
    else {
        cout << "Invalid choice! Defaulting to COD.\n";
    }
}

void submitComplaint() {
    char text[100];
    cout << "Enter Complaint/Query: ";
    cin.ignore();
    cin.getline(text, 100);
    cout << "Complaint submitted!\n";
}

void showFAQ() {
    cout << "\n----- FAQ -----\n";
    cout << "Q1: What payment methods are available?\n";
    cout << "A: Cash on Delivery and Card Payment\n\n";
    cout << "Q2: What card details are required?\n";
    cout << "A: 16-digit card number, PIN, and 3-digit CVV\n\n";
    cout << "Q3: Is there any discount?\n";
    cout << "A: 2.5% discount on bills above Rs.1000\n";
}

void ratingSystem() {
    int rating;
    cout << "Rate your experience (1-5): ";
    cin >> rating;
    cout << "Thank you for rating!\n";
}

// ========== MODULE 4: SHIPMENT ==========

// ---------- SHIPMENT MODULE ----------
void shipment(string cart[], float qty[], int prices[],
              int itemIndex[], int cartCount)
{
    if (cartCount == 0)
        return;

    cout << "\n===== ORDER SUMMARY =====\n";
    cout << "Item\tQty\tPrice\tTotal\n";

    float grandTotal = 0;

    for (int i = 0; i < cartCount; i++)
    {
        int idx = itemIndex[i];
        float total = qty[i] * prices[idx];
        grandTotal += total;

        cout << cart[i] << "\t"
             << qty[i] << "\t"
             << prices[idx] << "\t"
             << total << endl;
    }

    cout << "----------------------------\n";
    cout << "Grand Total: Rs." << grandTotal << endl;

    string delivery, billing;
    cin.ignore();

    cout << "Enter Delivery Address: ";
    getline(cin, delivery);

    cout << "Enter Billing Address: ";
    getline(cin, billing);

    // Address validation
    if (delivery.length() < 5 || billing.length() < 5)
    {
        cout << "Invalid address!\n";
        return;
    }

    int trackingID = 1000 + rand() % 9000;
    cout << "Tracking ID: TRK" << trackingID << endl;

    float distance;
    cout << "Enter distance (km): ";
    cin >> distance;

    float deliveryFee;
    if (distance <= 5)
        deliveryFee = 100;
    else if (distance <= 10)
        deliveryFee = 200;
    else
        deliveryFee = 300;

    cout << "Delivery Charges: Rs." << deliveryFee << endl;
    cout << "Final Payable: Rs." << (grandTotal + deliveryFee) << endl;

    cout << "\nOrder shipped successfully.\n";
    cout << "Order is now LOCKED.\n";
}

// ========== MAIN FUNCTION ==========

int main() {
    srand(time(0)); // Initialize random seed for tracking ID
    
    int choice;
    bool loggedin = false;
    bool accountExists = false;
    
    while (true) {
        cout << "\n===== online grocery store =====\n";
        cout << "1. create new account\n";
        cout << "2. login\n";
        cout << "3. recover password\n";
        cout << "4. exit\n";
        cout << "enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if (choice == 1) {
            newaccount();
            accountExists = true;
        }
        else if (choice == 2) {
            if (!accountExists) {
                cout << "No account found! Please create an account first.\n";
                continue;
            }
            
            loggedin = login();
            
            if (loggedin) {
                int option;
                do {
                    cout << "\n--- account menu ---\n";
                    cout << "1. view profile\n";
                    cout << "2. change password\n";
                    cout << "3. start shopping\n";
                    cout << "4. logout\n";
                    cout << "enter option: ";
                    cin >> option;
                    cin.ignore();
                    
                    if (option == 1) {
                        displayprofile();
                    }
                    else if (option == 2) {
                        changepassword();
                    }
                    else if (option == 3) {
                        // Shopping module starts here
                        int shopChoice;
                        do {
                            cout << "\n==============================\n";
                            cout << "         GROCERY STORE        \n";
                            cout << "==============================\n";
                            cout << "1. Search and Add Item\n";
                            cout << "2. Add from Menu\n";
                            cout << "3. View Cart\n";
                            cout << "4. Remove Item from Cart\n";
                            cout << "5. Proceed to Checkout\n";
                            cout << "6. Back to Account Menu\n";
                            cout << "------------------------------\n";
                            cout << "Enter choice: ";
                            cin >> shopChoice;
                            
                            if (shopChoice == 1)
                                searchAndAdd(items, prices, units, cart, qty, itemIndex, cartCount, loyaltyPoints);
                            
                            else if (shopChoice == 2)
                                addFromMenu(items, prices, units, cart, qty, itemIndex, cartCount, loyaltyPoints);
                            
                            else if (shopChoice == 3)
                                viewCart(cart, qty, units, itemIndex, cartCount);
                            
                            else if (shopChoice == 4)
                                removeItem(cart, qty, itemIndex, cartCount, loyaltyPoints);
                            
                            else if (shopChoice == 5) {
                                if (cartCount == 0) {
                                    cout << "\nCart is empty! Add items before checkout.\n";
                                }
                                else {
                                    // Calculate and display bill
                                    int totalBill = calculateBill();
                                    int finalBill = applyDiscount(totalBill);
                                    
                                    // Payment method
                                    paymentMethod();
                                    
                                    // Shipment process
                                    shipment(cart, qty, prices, itemIndex, cartCount);
                                    
                                    // Support and feedback options
                                    int supportChoice;
                                    cout << "\n--- Support & Feedback ---\n";
                                    cout << "1. Submit Complaint/Query\n";
                                    cout << "2. View FAQ\n";
                                    cout << "3. Rate Shopping Experience\n";
                                    cout << "4. Continue Shopping\n";
                                    cout << "Enter choice: ";
                                    cin >> supportChoice;
                                    
                                    if (supportChoice == 1)
                                        submitComplaint();
                                    else if (supportChoice == 2)
                                        showFAQ();
                                    else if (supportChoice == 3)
                                        ratingSystem();
                                    
                                    cout << "\nThank you for shopping with us!\n";
                                    
                                    // Reset cart after successful checkout
                                    cartCount = 0;
                                    loyaltyPoints = 0;
                                }
                            }
                            
                            else if (shopChoice == 6)
                                break;
                            
                            else
                                cout << "Invalid choice! Try again.\n";
                                
                        } while (shopChoice != 6);
                    }
                } while (option != 4);
                
                loggedin = false;
            }
        }
        else if (choice == 3) {
            if (!accountExists) {
                cout << "No account found! Please create an account first.\n";
                continue;
            }
            recoverpassword();
        }
        else if (choice == 4) {
            cout << "thank you for using the system\n";
            break;
        }
        else {
            cout << "invalid choice\n";
        }
    }
    
    return 0;
}