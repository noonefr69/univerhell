#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Contact {
  string f_name;
  string l_name;
  string phone;
};

vector<Contact> contacts;

void readFile(vector<Contact>& contacts){
  ifstream r("phonebook.txt");

  if(!r.is_open()){
    return;
  }

  Contact temp;
  while(getline(r, temp.f_name)){
    getline(r, temp.l_name);
    getline(r, temp.phone);
    contacts.push_back(temp); 
  }

  r.close();
}

void writeFile(const vector<Contact>& contacts){
  ofstream w("phonebook.txt");

  if(!w.is_open()){
    cout << "Error: could not open file for writing!\n";
    return;
  }

  for(int i = 0; i < contacts.size(); i++){
    w << contacts[i].f_name << endl;
    w << contacts[i].l_name << endl;
    w << contacts[i].phone  << endl;
  }

  w.close();
}

int menu() {
  system("clear");
  int userChoice;

  cout << "==========================\n";
  cout << "\t PHONEBOOK \t\n";
  cout << "==========================\n";
  cout << "1. Add new contact..." << endl;
  cout << "2. Search contact..." << endl;
  cout << "3. Display all contact..." << endl;
  cout << "4. Delete contact..." << endl;
  cout << "5. Edit contact..." << endl;
  cout << "6. Exit..." << endl;
  cout << "----------------------------\n";
  cout << "Your choice: ";
  cin >> userChoice;

  return userChoice;
}

void addPhone(vector<Contact>& contacts){
  system("clear");
  Contact newContact;

  cin.get();
  cout << "first name: ";
  getline(cin, newContact.f_name);


  cout << "last name: ";
  getline(cin, newContact.l_name);


  cout << "phone number: ";
  getline(cin, newContact.phone);

  contacts.push_back(newContact);

  writeFile(contacts);
  cout << "New contact added!\n";
  cout << "press enter to continue...";
  cin.get();
}

void displayContacts(const vector<Contact>& contacts){
  system("clear");

  if(contacts.empty()){
    cout << "phonebook is empty! \n"; 
    cout << "please get back and create a phone into phonebook...";
    cin.get();
    cin.get();
    return;
  }

  cout << "==== ALL Contacts ===\n";
  for(int i = 0; i < contacts.size(); i++){
    cout << i + 1 << ". " << contacts[i].f_name << " - " << contacts[i].l_name << " - " << contacts[i].phone << endl;
  }
  cout << "=====================\n";
  cout << "press enter to continue...";
  cin.get();
  cin.get();
}

void searchContact(const vector<Contact>& contacts){
  system("clear");

  cin.get();

  if(contacts.empty()){
    cout << "phonebook is empty!\n";
    cout << "please get back and create a phone into phonebook...";
    cin.get();
    cin.get();
    return;
  }

  string query;
  cout << "search by name: ";
  getline(cin, query);

  bool found = false;
  for(int i = 0; i < contacts.size(); i++){
    if(contacts[i].f_name == query || contacts[i].l_name == query){
      cout << i + 1 << ". "
        << contacts[i].f_name << " "
        << contacts[i].l_name << " - "
        << contacts[i].phone << endl;
      found = true;
    }
  }

  if(!found){
    cout << "no contact found for \"" << query << "\"\n";
  }

  cout << "press enter to continue...";
  cin.get();
}

void deleteContact(vector<Contact>& contacts){
  system("clear");

  if(contacts.empty()){
    cout << "phonebook is empty! \n"; 
    cout << "please get back and create a phone into phonebook...";
    cin.get();
    cin.get();
    return;
  }

  cout << "==== ALL Contacts ===\n";
  for(int i = 0; i < contacts.size(); i++){
    cout << i + 1 << ". " << contacts[i].f_name << " - " << contacts[i].l_name << " - " << contacts[i].phone << endl;
  }
  cout << "=====================\n";

  int pick;
  cout << "pick a number to delete(pick 0 to cancel): ";
  cin >> pick;

  if(pick == 0){
    return;
  }

  if(pick < 1 || pick > contacts.size()){
    cout << "invalid number!\n";
    cout << "press enter to continue...";
    cin.get();
    cin.get();
    return;
  }

  contacts.erase(contacts.begin() + (pick - 1));
  writeFile(contacts);

  cout << "contact deleted!\n";
  cout << "press enter to continue...";
  cin.get();
  cin.get();
}

void editContact(vector<Contact>& contacts){
  system("clear");

  if(contacts.empty()){
    cout << "phonebook is empty!\n";
    cout << "press enter to continue...";
    cin.get();
    cin.get();
    return;
  }

  cout << "==== ALL Contacts ===\n";
  for(int i = 0; i < contacts.size(); i++){
    cout << i + 1 << ". "
         << contacts[i].f_name << " "
         << contacts[i].l_name << " - "
         << contacts[i].phone << endl;
  }
  cout << "=====================\n";

  int pick;
  cout << "which number to edit? (0 to cancel): ";
  cin >> pick;

  if(pick == 0){
    return;
  }

  if(pick < 0 || pick > contacts.size()){
    cout << "invalid number!\n";
    cout << "press enter to continue...";
    cin.get();
    cin.get();
    return;
  }

  int idx = pick - 1;

  cout << "\ncurrent: "
       << contacts[idx].f_name << " "
       << contacts[idx].l_name << " - "
       << contacts[idx].phone << "\n\n";

  cin.get();  // eat the '\n' from cin >> pick

  string tmp;

  cout << "new first name (leave empty to keep): ";
  getline(cin, tmp);
  if(!tmp.empty()){
    contacts[idx].f_name = tmp;
  }

  cout << "new last name (leave empty to keep): ";
  getline(cin, tmp);
  if(!tmp.empty()){
    contacts[idx].l_name = tmp;
  }

  cout << "new phone (leave empty to keep): ";
  getline(cin, tmp);
  if(!tmp.empty()){
    contacts[idx].phone = tmp;
  }

  writeFile(contacts);

  cout << "contact updated!\n";
  cout << "press enter to continue...";
  cin.get();
}

int main(){
  int z;
  readFile(contacts);

  while(true){
    z = menu();
    switch(z){
      case 1:
        addPhone(contacts);
        break;
      case 2:
        searchContact(contacts);
        break;
      case 3:
        displayContacts(contacts);
        break;
      case 4:
        deleteContact(contacts);
        break;
      case 5:
        editContact(contacts);
        break;
      case 6:
        system("clear");
        cout << "Good Bye\n";
        cout << "Press enter to exit...";
        cin.get();
        cin.get();
        exit(0);
        break;
      default:
        system("clear");
        cout << "press enter to get back to menu and choose number between 1-6...";
        cin.get();
        cin.get();
    }
  }

  return 0;
}
