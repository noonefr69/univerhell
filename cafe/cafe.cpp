#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct menuItem {
  string name;
  string category;
  int price;
};

struct orderedItem {
  string name;
  int quantity;
  int price;
};

struct orderStruct {
  string customerName;
  vector<orderedItem> items;
  int total = 0;
};

vector<menuItem> menuVector;
vector<orderStruct> allOrders;

void loadMenu() {
  // ----- HOT DRINKS -----
  menuVector.push_back({"Espresso", "HOT", 3});
  menuVector.push_back({"Cappuccino", "HOT", 4});
  menuVector.push_back({"Latte", "HOT", 5});
  menuVector.push_back({"Chai Tea", "HOT", 3});

  // ----- COLD DRINKS -----
  menuVector.push_back({"Iced Coffee", "COLD", 5});
  menuVector.push_back({"Cold Brew", "COLD", 5});
  menuVector.push_back({"Orange Juice", "COLD", 4});

  // ----- FOOD -----
  menuVector.push_back({"Croissant", "FOOD", 3});
  menuVector.push_back({"Donut", "FOOD", 3});
  menuVector.push_back({"Sandwich", "FOOD", 7});
  menuVector.push_back({"Cake Slice", "FOOD", 4});

  // ----- EXTRAS -----
  menuVector.push_back({"Extra Shot", "EXTRA", 2});
  menuVector.push_back({"Oat Milk", "EXTRA", 1});
  menuVector.push_back({"Vanilla Syrup", "EXTRA", 1});
}

void displayCafeMenu() {
  system("clear");

  cout << "===============================================\n";
  cout << "\t LOS POLLOS HERMANOS CAFE MENU \t\n";
  cout << "===============================================\n\n";

  for (int i = 0; i < menuVector.size(); i++) {
    cout << i + 1 << ".   " << menuVector[i].name
      << " ........................... " << menuVector[i].price << "$"
      << endl;
  }

  cout << "===============================================\n\n";

  cout << "\nPress enter to continue...";
  cin.get();
}

void chooseOrder() {
  system("clear");

  orderStruct currentOrder;
  cout << "What is your name? ";
  getline(cin, currentOrder.customerName);

  cout << "\nChoose items. Enter 0 when finished:\n";

  for (int i = 0; i < menuVector.size(); i++) {
    cout << i + 1 << ". " << menuVector[i].name << " - $" << menuVector[i].price
      << endl;
  }

  while (true) {
    int number;
    cout << "\nItem number (0 to finish): ";
    cin >> number;

    if (number == 0) {
      break;
    }

    if (number < 1 || number > menuVector.size()) {
      cout << "Invalid item number.\n";
      continue;
    }

    int quantity;
    cout << "Quantity: ";
    cin >> quantity;

    // Save this item in this customer's order.
    orderedItem item;
    item.name = menuVector[number - 1].name;
    item.quantity = quantity;
    item.price = menuVector[number - 1].price;

    currentOrder.items.push_back(item);
    currentOrder.total += item.price * item.quantity;
  }

  allOrders.push_back(currentOrder);

  system("clear");
  cout << "\nOrder for " << currentOrder.customerName << ":\n";
  for (int i = 0; i < currentOrder.items.size(); i++) {
    cout << currentOrder.items[i].quantity << " x "
      << currentOrder.items[i].name << endl;
  }
  cout << "Total: $" << currentOrder.total << endl;

  cout << "Press Enter to continue...";
  cin.ignore();
  cin.get();
}

void waitlist() {
  system("clear");

  if (allOrders.empty()) {
    cout << "There are no orders yet.\n";
  }

  for (int i = 0; i < allOrders.size(); i++) {
    cout << "\nOrder " << i + 1 << " for " << allOrders[i].customerName
      << ":\n";

    for (int j = 0; j < allOrders[i].items.size(); j++) {
      cout << "  " << allOrders[i].items[j].quantity << " x "
        << allOrders[i].items[j].name << endl;
    }

    cout << "Total: $" << allOrders[i].total << endl;
  }

  cout << "\nPress Enter to continue...";
  cin.get();
}

void abortLastOrder() {
  system("clear");

  if (allOrders.size() == 0) {
    cout << "There are no orders to abort.\n";
  } else {
    int choice;

    cout << "Abort the most recent order? Enter 1 for yes, 0 for no: ";
    cin >> choice;
    cin.get();

    if (choice == 1) {
      allOrders.pop_back();
      cout << "The most recent order was aborted.\n";
    } else {
      cout << "No order was aborted.\n";
    }
  }

  cout << "Press Enter to continue...";
  cin.get();
}

void abortOrder() {
  system("clear");

  if (allOrders.empty()) {
    cout << "There are no orders to abort.\n";
    cout << "Press Enter to continue...";
    cin.get();
  }

  cout << "Orders:\n";

  for (int i = 0; i < allOrders.size(); i++) {
    cout << i + 1 << ". " << allOrders[i].customerName << " - Total: $"
      << allOrders[i].total << endl;
  }

  int orderNumber;
  cout << "\nEnter the order number to abort (0 to cancel): ";
  cin >> orderNumber;

  if (orderNumber == 0) {
    cin.get();
    cout << "No order was aborted.\n";
  } else if (orderNumber < 1 || orderNumber > allOrders.size()) {
    cin.get();
    cout << "Invalid order number.\n";
  } else {
    allOrders.erase(allOrders.begin() + orderNumber - 1);
    cin.get();
    cout << "Order aborted.\n";
  }

  cout << "Press Enter to continue...";
  cin.get();
}

// void changeOrder() {
//  system("clear");
//
//  if(allOrders.size() == 0){
//    cout << "there are no orders yet to edit \n";
//    cout << "press enter to continue...";
//    cin.get();
//  }
//}

void changeOrder() {
  system("clear");

  if (allOrders.size() == 0) {
    cout << "There are no orders to edit.\n";
    cout << "Press Enter to continue...";
    cin.get();
    return;
  }

  cout << "Orders:\n";

  for (int i = 0; i < allOrders.size(); i++) {
    cout << i + 1 << ". " << allOrders[i].customerName
         << " - Total: $" << allOrders[i].total << endl;
  }

  int orderNumber;
  cout << "\nEnter the order number to edit (0 to cancel): ";
  cin >> orderNumber;
  cin.ignore();

  if (orderNumber == 0) {
    cout << "No order was selected.\n";
    cout << "Press Enter to continue...";
    cin.get();
    return;
  }

  if (orderNumber < 1 || orderNumber > allOrders.size()) {
    cout << "Invalid order number.\n";
    cout << "Press Enter to continue...";
    cin.get();
    return;
  }

  int orderIndex = orderNumber - 1;

  // Let the user change the name, or press Enter to keep it.
  string newName;
  cout << "Current customer name: "
       << allOrders[orderIndex].customerName << endl;
  cout << "New name (press Enter to keep the current name): ";
  getline(cin, newName);

  if (newName != "") {
    allOrders[orderIndex].customerName = newName;
  }

  if (allOrders[orderIndex].items.size() == 0) {
    cout << "This order has no items.\n";
  } else {
    cout << "\nItems in this order:\n";

    for (int i = 0; i < allOrders[orderIndex].items.size(); i++) {
      cout << i + 1 << ". "
           << allOrders[orderIndex].items[i].quantity << " x "
           << allOrders[orderIndex].items[i].name << endl;
    }

    while (true) {
      int itemNumber;
      cout << "\nChoose an item to edit (0 to finish): ";
      cin >> itemNumber;
      cin.ignore();

      if (itemNumber == 0) {
        break;
      }

      if (itemNumber < 1 ||
          itemNumber > allOrders[orderIndex].items.size()) {
        cout << "Invalid item number.\n";
        continue;
      }

      int itemIndex = itemNumber - 1;
      int newQuantity;

      cout << "Current quantity: "
           << allOrders[orderIndex].items[itemIndex].quantity << endl;
      cout << "New quantity (enter 0 to keep it): ";
      cin >> newQuantity;
      cin.ignore();

      if (newQuantity > 0) {
        allOrders[orderIndex].items[itemIndex].quantity = newQuantity;
        cout << "Quantity updated.\n";
      } else if (newQuantity == 0) {
        cout << "Quantity was not changed.\n";
      } else {
        cout << "Quantity must be greater than 0.\n";
      }
    }
  }

  // Recalculate the order total after any quantity changes.
  allOrders[orderIndex].total = 0;

  for (int i = 0; i < allOrders[orderIndex].items.size(); i++) {
    allOrders[orderIndex].total +=
        allOrders[orderIndex].items[i].price *
        allOrders[orderIndex].items[i].quantity;
  }

  cout << "\nUpdated order for "
       << allOrders[orderIndex].customerName << ":\n";

  for (int i = 0; i < allOrders[orderIndex].items.size(); i++) {
    cout << allOrders[orderIndex].items[i].quantity << " x "
         << allOrders[orderIndex].items[i].name << endl;
  }

  cout << "Total: $" << allOrders[orderIndex].total << endl;
  cout << "Press Enter to continue...";
  cin.get();
}


int menu() {
  system("clear");
  int customerChoice;
  cout << "===================================================================="
    "=============================\n";
  cout << "Hello and welcome to the Los Pollos Hermanos cafe. My name is "
    "Gustavo, but you can call me Gus. \n";
  cout << "===================================================================="
    "=============================\n";

  cout << "1. Menu... " << endl;
  cout << "2. Order..." << endl;
  cout << "3. Wait list..." << endl;
  cout << "4. Abort order..." << endl;
  cout << "5. Abort recent order..." << endl;
  cout << "6. Change order..." << endl;
  cout << "7. Exit..." << endl;

  cout << "\nplease choose your option between 1-7: ";
  cin >> customerChoice;
  cin.get();

  return customerChoice;
}

int main() {
  int z;
  loadMenu();

  while (true) {
    z = menu();

    switch (z) {
      case 1:
        displayCafeMenu();
        break;
      case 2:
        chooseOrder();
        break;
      case 3:
        waitlist();
        break;
      case 4:
        abortOrder();
        break;
      case 5:
        abortLastOrder();
        break;
      case 6:
        changeOrder();
        break;
      case 7:
        return 0;
        break;
      default:
        system("clear");
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
          "!!!!\n";
        cout << "                       CHOOSE BETWEEN 1-7\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
          "!!!!\n";
        cout << "                    Press enter to continue...\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
          "!!!!\n";
        cin.get();
        break;
    }
  }
  return 0;
}
