/*
    Hi, I'm Junaid Babar.
    Let's create a simple cafe management system using C++.

    layout of the code
    - File handling
    - File reader
    - Welcome and exit function
    - Load and store items from file to array
    - Display items
    - Owner panel
        - Login
        - Add item
        - Remove item
        - Update item
        - View record
    - Customer panel
        - Get customer data
        - Bill generation
        - Buy item
        - Store customer data
    - Main function
*/

#include <iostream>
//  for input and output
#include <string>
//  for string operations
#include <fstream>
//  for file handling
#include <conio.h>
//  for _getch() function
#include <windows.h>
//  for Sleep() system call
#include <vector>
//  for dynamic array
#include <sstream>
//  for string stream to avoid issues with getline
#include <ctime>
//  for time functions

using namespace std;

//  Structure for items
struct Items
{
    string name;
    double price;
};

vector<Items> items; // Using vector to dynamically manage the array size

/*
=================================================
            Utility Functions
=================================================
*/

//  File reader function
void fileReader(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error opening file" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

//  Welcome and exit function
void welcome()
{
    fileReader("welcome.txt");

    cout << "\n\nPress any key to continue..." << endl;
    _getch(); // Wait for user to press any key
}

void exit()
{
    system("cls");
    fileReader("thanks.txt");
}

//  Function to load and store all items form the file to an array
void loadItemsFromFileToArray()
{
    ifstream file("items.txt");
    if (!file.is_open())
    {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        Items newItem;
        if (getline(iss, newItem.name, ',') && iss >> newItem.price)
        {
            items.push_back(newItem);
        }
    }
    // istringstream allows you to treat a string as an input stream, enabling you to use the same extraction operators (>>) and functions (getline) that you would use with ifstream or cin.
    file.close();
}

void storeItemsFromArrayToFile()
{
    ofstream file("items.txt", ios::out);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    for (const auto &item : items)
    {
        file << item.name << "," << item.price << endl;
    }

    file.close();
}

//  Function for displaying items available (will be used in both user and owner panel)
void displayItems()
{
    int i = 1;
    cout << "Item name: " << ", Item price: " << endl;
    for (const auto &item : items)
    {
        cout << i << ". " << item.name << ", " << item.price << endl;
        i++;
    }
    cout << "press any key to continue..." << endl;
    _getch();
}

/*
=================================================
            OWNER PANEL CODE
=================================================
*/

//  login for owner authentication
bool login()
{
    system("cls");
    string username = "admin", password = "admin";
    string inputUsername, inputPassword;

    cout << "\n\n\t\t\t\tEnter username: ";
    cin >> inputUsername;
    cout << "\t\t\t\tEnter password: ";
    for (size_t i = 0; i < password.length(); i++)
    {
        inputPassword += _getch();
        cout << "*";
    }

    if (inputUsername == username && inputPassword == password)
    {

        cout << "\n\n\nLogin Successfully";
        for (int i = 0; i < 5; i++)
        {
            cout << ".";
            Sleep(200);
        }

        return true;
    }
    else if (inputUsername != username)
    {
        cerr << "\n\nInvalid username" << endl;
    }
    else if (inputPassword != password)
    {
        cerr << "\n\nInvalid password" << endl;
    }
    else
    {
        cerr << "\n\nInvalid username and password" << endl;
    }

    cout << "Enter 1 to try again or 0 to exit: ";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        login();
    }
    else
    {
        return false;
    }

    return false;
}

//  function for owner to add item
void addItem()
{
    system("cls");
    Items newItem;
    cout << "'\n\n\t\t\t\tEnter item name: ";
    cin.ignore();
    getline(cin, newItem.name);
    cout << "\t\t\t\tEnter item price: ";
    cin >> newItem.price;

    items.push_back(newItem); // Add the new item at the end of the vector

    cout << "Item added successfully!" << endl;
    cout << "Press any key to continue..." << endl;
    _getch();
}

// Function for owner to remove item
void removeItem()
{
    system("cls");

    int i = 1;
    cout << "Item name: " << ", Item price: " << endl;
    for (const auto &item : items)
    {
        cout << i << ". " << item.name << ", " << item.price << endl;
        i++;
    }

    cout << "\n\n\t\t\t\tEnter the item number you want to remove: ";
    int itemNumber;
    cin >> itemNumber;

    // Adjust index to be zero-based and ensure itemNumber is within valid range
    if (itemNumber > 0 && static_cast<size_t>(itemNumber - 1) < items.size())
    {
        items.erase(items.begin() + (itemNumber - 1)); // Remove the item from the vector
        cout << "Item removed successfully!" << endl;
    }
    else
    {
        cerr << "Invalid item number" << endl;
    }

    cout << "Press any key to continue..." << endl;
    _getch();
}

// Function for owner to update an existing item
void updateItem()
{
    system("cls");

    // Display the list of items
    cout << "Item name: " << ", Item price: " << endl;
    for (size_t i = 0; i < items.size(); ++i)
    {
        cout << (i + 1) << ". " << items[i].name << ", " << items[i].price << endl;
    }

    // Prompt the user to enter the item number to update
    cout << "\n\n\t\t\t\tEnter the item number you want to update: ";
    int itemNumber;
    cin >> itemNumber;

    // Validate the item number
    if (itemNumber > 0 && static_cast<size_t>(itemNumber - 1) < items.size())
    {
        // Adjust index to be zero-based
        itemNumber -= 1;

        // Prompt the user to choose what to update
        cout << "\n\n\t\t\t\t1. Update item name" << endl;
        cout << "\t\t\t\t2. Update item price" << endl;

        int choice;
        cout << "\n\n\t\t\t\tEnter your choice: ";
        cin >> choice;

        // Clear the input buffer to avoid issues with getline
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "\t\t\t\tEnter new item name: ";
            getline(cin, items[itemNumber].name);
            cin.ignore();
            break;
        case 2:
            cout << "\t\t\t\tEnter new item price: ";
            cin >> items[itemNumber].price;
            break;
        default:
            cerr << "Invalid choice" << endl;
            return;
        }

        cout << "Item updated successfully!" << endl;
    }
    else
    {
        cerr << "Invalid item number" << endl;
    }

    cout << "Press any key to continue..." << endl;
    _getch();
}

//  additional functions for owner
void viewRecord()
{
    fileReader("record.txt");

    cout << "Press any key to continue..." << endl;
    _getch();
}

// MAIN FUNCTION FOR OWNER PANEL
void ownerMenu()
{
    if (login())
    {
        int choice;
        do
        {
            system("cls");
            cout << "\n\n\t\t\t\t1. Add item" << endl;
            cout << "\t\t\t\t2. Remove item" << endl;
            cout << "\t\t\t\t3. Update item" << endl;
            cout << "\t\t\t\t4. View items" << endl;
            cout << "\t\t\t\t5. View Record" << endl;
            cout << "\t\t\t\t0. Exit" << endl;
            cout << "\n\n\t\t\t\tEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                addItem();
                break;
            case 2:
                removeItem();
                break;
            case 3:
                updateItem();
                break;
            case 4:
                displayItems();
                break;
            case 5:
                viewRecord();
                break;
            case 0:
                cout << "Exiting" << endl;
                for (int i = 0; i < 5; i++)
                {
                    cout << ".";
                    Sleep(300);
                }
                return;
                break;
            default:
                cerr << "Invalid choice" << endl;
                break;
            }
        } while (choice != 7);
    }
}

/*
=================================================
            CUSTOMER PANEL CODE
=================================================
*/

struct Customer
{
    string name;
    vector<Items> customerItems;
    double totalBill;
};

Customer customer;

// customer data input
void getCustomerData()
{
    cout << "\n\n\t\t\t\tEnter your name: ";
    cin.ignore();
    getline(cin, customer.name);
}

void buyItem()
{
    system("cls");
    int i = 1;
    cout << "Item name: " << ", Item price: " << endl;
    for (const auto &item : items)
    {
        cout << i << ". " << item.name << ", " << item.price << endl;
        i++;
    }

    cout << "\n\n\t\t\t\tEnter the item number you want to buy: ";
    int itemNumber;
    cin >> itemNumber;

    if (itemNumber >= 0 && static_cast<size_t>(itemNumber) < items.size())
    {
        customer.customerItems.push_back(items[itemNumber]);
        customer.totalBill += items[itemNumber].price;
        cout << "Item added to cart successfully!" << endl;
    }
    else
    {
        cerr << "Invalid item number" << endl;
    }

    cout << "Press any key to continue..." << endl;
    _getch();
}

//  bill generation
void billTxt()
{
    ofstream billFile("bill.txt");
    if (!billFile.is_open())
    {
        cerr << "Error: Could not create bill file." << endl;
        return;
    }

    time_t now = time(0);     // getting local time
    char *date = ctime(&now); // Converting toa string
    billFile << "\n\n\t\t" << date << endl;
    billFile << "\n\t\t                       CAFE MANAGEMENT SYSTEM - CUSTOMER INVOICE " << endl;
    billFile << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    billFile << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    billFile << "\t\t\t   Customer Name:                         " << customer.name << endl;
    billFile << "\t\t\t   Items bought: " << endl;
    for (const auto &item : customer.customerItems)
    {
        billFile << "\t\t\t    " << item.name << "," << item.price << endl;
    }
    billFile << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    billFile << "\t\t\t   Total Bill                             " << customer.totalBill << endl;
    billFile << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    billFile << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    billFile << "\t\t	 NOTE: This is a computer generated invoice. " << endl;
    billFile << "\t\t	       It does not require an authorised signature." << endl;
    billFile << "\t\t	       Get a print of this bill file." << endl;
    billFile << "\t\t	***********************************************************" << endl;

    billFile.close();
}

void billGeneration()
{
    system("cls");

    time_t now = time(0);               // getting local time
    char *date = ctime(&now);           // Converting toa string
    cout << "\n\n\t\t" << date << endl; // displays time on screen, setw() controls the width of line
    cout << "\n\t\t                       CAR RENTAL - CUSTOMER INVOICE                  " << endl;
    cout << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t\t   Customer Name:                         " << customer.name << endl;
    cout << "\t\t\t   Items bought: " << endl;
    for (const auto &item : customer.customerItems)
    {
        cout << "\t\t\t    " << item.name << "," << item.price << endl;
    }
    cout << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t\t   Total Bill                             " << customer.totalBill << endl;
    cout << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t	 NOTE: This is a computer generated invoce. " << endl;
    cout << "\t\t	       It does not require an authorised signture." << endl;
    cout << "\t\t	       Get print of the bill file." << endl;
    cout << "\t\t	***********************************************************" << endl;

    billTxt();

    cout << "Press any key to continue..." << endl;
    _getch();
}

//  storing customers data for future
void customerDataStoring()
{
    ofstream file("record.txt", ios::app);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    file << customer.name << "," << customer.totalBill << endl;
    file << "Items bought: " << endl;
    for (const auto &item : customer.customerItems)
    {
        file << item.name << "," << item.price << endl;
    }
    file << "--------------------------------------" << endl;

    file.close();
}

// MAIN FUNCTION FOR CUSTOMER PANEL
void customerMenu()
{
    getCustomerData();

    int choice;
    int i = 1;
    do
    {
        system("cls");
        cout << "\n\n\t\t\t\t1. Buy item" << endl;
        cout << "\t\t\t\t2. View cart" << endl;
        cout << "\t\t\t\t3. Generate bill" << endl;
        cout << "\t\t\t\t0. Exit" << endl;
        cout << "\n\n\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            buyItem();
            break;
        case 2:
            cout << "Item name: " << "\tItem price: " << endl;
            for (const auto &item : customer.customerItems)
            {
                cout << i << ". " << item.name << "\t" << item.price << endl;
                i++;
            }
            cout << "Press any key to continue..." << endl;
            _getch();
            break;
        case 3:
            billGeneration();
            break;
        case 0:
            exit();
            customerDataStoring();
            return;
            break;
        default:
            cerr << "Invalid choice" << endl;
            break;
        }
    } while (choice != 4);
}

/*
=================================================
            MAIN FUNCTION CODE
=================================================
*/
int main()
{
    welcome();
    loadItemsFromFileToArray();

    cout << "\n\n\t\t\t\t1. Owner" << endl;
    cout << "\t\t\t\t2. Customer" << endl;
    cout << "\n\n\t\t\t\tEnter your choice: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        ownerMenu();
        break;
    case 2:
        customerMenu();
        break;
    default:
        cerr << "Invalid choice" << endl;
        break;
    }

    storeItemsFromArrayToFile();

    return 0;
}