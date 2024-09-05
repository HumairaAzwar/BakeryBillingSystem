#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Struct for bakery items
struct BakeryItem {
    int id;
    string name;
    double price;
    int quantity;
};

vector<BakeryItem> bakeryItems;
vector<pair<string, int>> purchasedItems; // Keep track of purchased items and quantities
int total = 0; // for the total bill amount

void displaycompanydetails();
void displayBakeryItems();
void menu();
void login();
void registr();
void invoice();
void manageItems();
void manageSalesDetails();

int main() 
{
    // Define bakery items
    bakeryItems = {
        {1, "Chocolate Cake              ",  100},
        {2, "Blueberry Muffin            ",  250},
        {3, "French Bread                ",  150},
        {4, "Vanilla Cupcake             ",   75},
        {5, "Cinnamon Roll               ",   80},
        {6, "Ice Coffee                  ",   50},
        {7, "Nescafe                     ",   60},
        {8, "Birthday Package            ", 3500},
        {9, "Evening Party Package       ", 1500},
        {10, "Wedding Cakes              ", 6500}
    };

    int choice;
    cout << endl << endl;
    system("Color F0");
    cout << "                 **************************************        " << endl;
    cout << "                 ****    WELCOME TO AMBER BAKERY   ****        " << endl;
    cout << "                 **************************************        " << endl;
    cout << std::endl;
    cout << endl;
    cout << "                    Delicious Cakes, Pastries, Breads          " << endl;
    cout << "                             and much more!                    " << endl;
    cout << endl;
    cout << "                          Range of Beverages                   " << endl;
    cout << "                          and Hot Coffee too!                  " << endl;
    cout << endl;
    cout << "                 **************************************        " << endl;
    cout << endl;
    cout << "                     Celebrate with us on holidays,            " << endl;
    cout << "                         parties, and weddings.                " << endl;
    cout << "                         Order now and Enjoy!                  " << endl;
    cout << endl;
    cout << "                 **************************************        " << endl;
    cout << "                 **************************************        " << endl;
    cout << "                             1. Login                          " << endl;
    cout << "                             2. Register                       " << endl<<endl;
    cout << "                           Enter your choice:";
    cin >> choice;

    switch (choice) {
        case 1:
            login();
            break;
        case 2:
            registr();
            break;
        default:
            cout << "Invalid option" << endl;
            system("cls");
            main();
            break;
    }
}

void displayBakeryItems(const vector<BakeryItem>& bakeryItems, const string& searchString) 
{
    int number, n = 0;
    char ask;

retry:
    system("cls");
    cout <<endl<<endl<<endl;
    cout << "                    Available Bakery Items:                              " << endl;
    cout << "                    ----------------------------------------------       " << endl;
    cout << "                    ID   | Name                            | Price       " << endl;
    cout << "                    ----------------------------------------------       " << endl;
    
    for (const auto& item : bakeryItems) {
        // Check if the item name contains the search string
        if (searchString.empty() || item.name.find(searchString) != string::npos) {
            cout <<"                    "<< item.id << "    |  " << item.name << "   | " << item.price << endl;
        }
    }

    cout << "                   -----------------------------------------------       " << endl;
    cout << "                   Do you want to order?                                 "<< endl;
    cout << "                       Yes[y]                                            "<< endl;
    cout << "                       No [n]                                            "<< endl<<endl;
    cout << "                       y or n : ";
    cin >> ask;

    if (ask == 'y') {
        cout << "               Enter the Item ID: ";
        cin >> number;
        int n;

        if (number >= 1 && number <= bakeryItems.size()) {
            cout << "               Enter the quantity: ";
            cin >> n;

            if (n > 0) {
                // Calculate the total price for the selected item and add it to the total bill
                int itemPrice = bakeryItems[number - 1].price;
                total += (itemPrice * n);

                // Add the purchased item and quantity to the vector
                purchasedItems.push_back({bakeryItems[number - 1].name, n});
            } else {
                cout << "      Invalid quantity. Please enter a positive quantity." << endl;
            }
        } else {
            cout << "          Invalid Item ID. Please enter a valid Item ID." << endl;
        }

        cout << "               Do you want to purchase more items? (y/n): ";
        cin >> ask;

        if (ask == 'y') {
            goto retry;
        } else {
            invoice();
        }
    } else {
        menu();
    }
}
void invoice() 
{
    system("cls");
    cout <<endl<<endl<<endl;
    cout << "       ****************************************************       " << endl;
    cout << "                              Invoice                             " << endl;
    cout << "       ****************************************************       " << endl;

    // Display the purchased items, their unit prices, and quantities
    cout << "       Items Purchased:" << endl;
    cout << "       --------------------------------------------------------" << endl;
    cout << "       ID   | Name                         | Price   | Quantity" << endl;
    cout << "       --------------------------------------------------------" << endl;

    for (const auto& item : purchasedItems) {
        int itemId = -1;
        for (const auto& bakeryItem : bakeryItems) {
            if (item.first == bakeryItem.name) {
                itemId = bakeryItem.id;
                string itemName = bakeryItem.name;
                double itemPrice = bakeryItem.price;
                int itemQuantity = item.second;

                // Format the output manually with fixed-width columns
                cout<<"       " << itemId << "    | " << itemName;
                cout << string(29 - itemName.size(), ' '); // Adjust for column width
                cout << "Rs." << itemPrice << "   | " << itemQuantity << endl;
                break;
            }
        }
        if (itemId == -1) {
            cout << "Unknown Item: " << item.first << " (Quantity: " << item.second << ")" << endl;
        }
    }
    cout << "        --------------------------------------------------------" << endl;

    // Calculate and display the total bill amount
    double totalAmount = 0.0;
    for (const auto& item : purchasedItems) {
        int itemId = -1;
        for (const auto& bakeryItem : bakeryItems) {
            if (item.first == bakeryItem.name) {
                itemId = bakeryItem.id;
                totalAmount += (bakeryItem.price * item.second);
                break;
            }
        }
    }
    cout << "        Total Bill Amount: Rs." << totalAmount << endl;

    cout << "        ****************************************************  " << endl<<endl;
    cout << "             Thank you for shopping with us!" << endl;

    // Save the sale details to a file
    ofstream saleFile("sales.txt", ios::app); // Open the file in append mode
    if (saleFile.is_open()) {
        saleFile << "           Total Sale Amount: Rs." << totalAmount << endl;
        saleFile.close();
    }
    cout<<endl << "     Press Enter to return to the main menu..."; // Wait for the user to press Enter
    cin.ignore(); // Ignore any previous newline character
    cin.get(); // Read the Enter key press
    menu(); // Return to the main menu
}




void displaycompanydetails()
{
	system("cls");
	cout <<endl<<endl<<endl;
    cout << "        ********************************************************************     " << endl;
    cout << "        ******                     ABOUT AMBER BAKERY                 ******     " << endl;
    cout << "        ********************************************************************     " << endl;
    cout<<endl;
    cout << "          Amber Bakery offers a variety of delectable bakery delights            " << endl;
	cout << "                 including cakes, desserts, bread, and cookies,                  " << endl;
	cout << "          ensuring quality and freshness for a memorable experience.             " << endl;
	cout<<endl;
	cout << "          History: Established in the heart of London in 1980 by                  "  <<endl;
    cout << "                   Mr. Francisco Michael,Amber Bakery has been serving the        " << endl;
    cout << "                   community with  love for decades.Our journey began as a        " << endl; 
    cout << "                   small, family-owned business,and over the years we've          " <<endl;
    cout << "                   grown to become a cherished part of the neighborhood.          " <<endl;
	cout<<endl;
    cout << "          Contact: +44 (0) 123-456-7890                                           " << endl;
	cout<<endl;
    cout << "          Address: 123 Baker Street, London, CF1 2AB                              " << endl;
	cout<<endl;
    cout << "          Working Hours: Monday to Saturday: 8:00 AM - 8:00 PM                    " << endl;
    cout<<endl;
    cout << "       *********************************************************************      " << endl<<endl;
    cout << "     Press Enter to return to the main menu..."; // Wait for the user to press Enter
    cin.ignore(); // Ignore any previous newline character
    cin.get(); // Read the Enter key press
    menu();
}

void menu() 
{
    //  menu function
    system("cls");
    int option;
    string searchString; // Variable to store the search string
    cout <<endl<<endl<<endl;
    cout << "                 *****************************************                 " << endl;
    cout << "                 ****        AMBER BAKERY SYSTEM      ****                 " << endl;
    cout << "                 *****************************************                 " << endl << endl;
    cout << "                  1. View Available Bakery Items and Packages              " << endl;
    cout << "                  2. Manage Items and Packages                             " << endl;
    cout << "                  3. Manage Sales Details.                                 " << endl;
    cout << "                  4. Search Bakery Items                                   " << endl; 
    cout << "                  5. About us                                              " << endl;
    cout << "                  6. Log out                                               " << endl;
    cout << "                  7. Exit                                                  " << endl<< endl;
    cout << "        Enter your option : ";
    cin >> option;

    switch (option) {
        case 1:
            system("cls");
            getline(cin, searchString);
            displayBakeryItems(bakeryItems, searchString); // Pass the search string
            break;
        case 2:
            manageItems();
            break;
        case 3:
            manageSalesDetails();
            break;
        case 4: // Search Bakery Items
            system("cls");
            cout <<endl<<endl<<endl;
            cout << "                Enter search keyword: ";
            cin.ignore();
            getline(cin, searchString);
            displayBakeryItems(bakeryItems, searchString); // Pass the search string
            break;
        case 5:
            system("cls");
            displaycompanydetails();
            break;
        case 6:
            system("cls");
            main();
            break;
        case 7:
            system("cls");
            cout << "    " << endl << endl <<endl;
            cout << "           Thank You for Using Amber Bakery System!        " << endl << endl;
            exit(0);
            break;
        default:
            cout << "           Invalid choice! TRY AGAIN !                     " << endl;
            break;
    }
}
void login() 
{
    int exist = 0;
    string user, pass, u, p;
    system("cls");
    cout <<endl<<endl<<endl;
    cout << "              **************************************      " << endl;
    cout << "              ****            LOGIN             ****      " << endl;
    cout << "              **************************************      " << endl<<endl;
    cout << "     Enter the username : ";
    cin >> user;
    cout <<endl;
    cout << "     Enter the password : ";
    cin >> pass;

    ifstream input("database.txt");

    while (input >> u >> p) {
        if (u == user && p == pass) {
            exist = 1;
            system("cls");
        }
    }
    input.close();
    if (exist == 1) 
	{
        int check;
        system("cls");

        while (true) {
            menu();
            cin.get();
        }
    } else {
        cout << "\n\t\t\t LOGIN ERROR !  \n\n\t\tPlease check your username and password\n"<<endl;
        cout << "      Press Enter to return to the Main Menu ";
        cin.ignore();
        cin.get();
        system("cls");
        main();
    }
}

void registr()
{
    string reguser, regpass;
    system("cls");
    cout <<endl<<endl<<endl;
    cout << "              **************************************       " << endl;
    cout << "              ****          REGISTER            ****       " << endl;
    cout << "              **************************************       " << endl<<endl;
    cout << "     Enter the username : ";
    cin >> reguser;
    cout <<endl;
    cout << "     Enter the password : ";
    cin >> regpass;

    ofstream reg("database.txt");
    reg << reguser << ' ' << regpass << endl;

    cout << "\n\n\t\t  Registration Successful !  \n\n";
    cout << "      Press Enter to return to the Main Menu ";
    cin.ignore();
    cin.get();
    system("cls");
    main();
}

void manageItems() 
{
    int option;
    char repeat;
    
    do {
        system("cls");
        cout <<endl<<endl<<endl;
        cout << "             **************************************      " << endl;
        cout << "             ****   MANAGE ITEMS AND PACKAGES  ****      " << endl;
        cout << "             **************************************      " << endl;
        cout << std::endl;
        cout << "               1. Add Item                               " << endl;
        cout << "               2. Edit Item                              " << endl;
        cout << "               3. Delete Item                            " << endl<<endl;
        cout << "               Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: // Add Item
                {
                    BakeryItem newItem;
                    cout <<endl;
                    cout << "        Enter Item Name: ";
                    cin.ignore();
                    getline(cin, newItem.name);
                    cout << "        Enter Item Price: Rs.";
                    cin >> newItem.price;

                    // Assign a unique ID to the new item
                    newItem.id = bakeryItems.size() + 1;

                    bakeryItems.push_back(newItem);
                    cout <<endl;
                    cout << "        Item added successfully!" << endl;
                }
                break;

            case 2: // Edit Item
                {
                    int editID;
                    cout << "        Enter the ID of the item to edit: ";
                    cin >> editID;

                    if (editID >= 1 && editID <= bakeryItems.size()) {
                    	cout <<endl;
                        cout << "    Editing Item ID: " << editID<<endl;
                        cout << "    Enter new Item Name: ";
                        cin.ignore();
                        getline(cin, bakeryItems[editID - 1].name);
                        cout << "    Enter new Item Price: Rs.";
                        cin >> bakeryItems[editID - 1].price;
                        
                        cout<<endl;
                        cout << "    Item edited successfully!" << endl;
                    } else {
                        cout << "        Invalid Item ID. Please enter a valid Item ID." << endl;
                    }
                }
                break;

            case 3: // Delete Item
                {
                    int deleteID;
                    cout << "         Enter the ID of the item to delete: ";
                    cin >> deleteID;

                    if (deleteID >= 1 && deleteID <= bakeryItems.size()) {
                    	cout<<endl;
                        cout << "     Deleting Item ID: " << deleteID << endl;
                        bakeryItems.erase(bakeryItems.begin() + deleteID - 1);
                        cout <<endl;

                        cout << "     Item deleted successfully!" << endl;
                    } else {
                        cout << "     Invalid Item ID. Please enter a valid Item ID." << endl;
                    }
                }
                break;

            default:
                cout << "      Invalid option! Please try again." << endl<<endl;
                break;
        }
        cout <<endl;
        cout << "              Do you want to perform another operation? (y/n): ";
        cin >> repeat;
    } while (repeat == 'y' || repeat == 'Y');
}


void manageSalesDetails() 
{
    // Display sales report
    system("cls");
    cout <<endl<<endl<<endl;
    cout << "              **************************************       " << endl;
    cout << "              ****     MANAGE SALES DETAILS     ****       " << endl;
    cout << "              **************************************       " << endl;
    cout << std::endl;

    ifstream saleFile("sales.txt");

    if (saleFile.is_open()) {
        string line;
        cout << "              Sales Report:" << endl;
        cout << "              --------------------------------------" << endl;

        while (getline(saleFile, line)) {
            cout << line << endl;
        }

        saleFile.close();
    } else {
        cout << "              No sales data available." << endl;
    }
    cout << std::endl;
    cout << "              Press ENTER to return to the main menu -->";
    cin.ignore();
    cin.get();
    menu();
}

