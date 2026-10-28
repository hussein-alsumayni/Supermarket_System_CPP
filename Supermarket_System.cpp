#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// ===== الهياكل =====
struct User {
    string username;
    string password;
    string role;    // Admin / Employee
    string phone;
    string status;  // active / inactive
    string gender;  // male / female
};

struct Product {
    int id;
    string name;
    double price;
    int quantity;
};

struct Sale {
    int id;
    string productName;
    double totalPrice;
    int quantity;
};

struct ItemCount { string name; int count; };

// ===== دوال التحقق =====
bool isValidUsername(const string& username) {
    for (int i = 0; i < username.length(); i++)
        if (!isalpha(username[i])) return false;
    return true;
}

bool isValidPhone(const string& phone) {
    if (phone.length() != 9) return false;
    for (int i = 0; i < phone.length(); i++)
        if (!isdigit(phone[i])) return false;

    string prefix = phone.substr(0, 2);
    return (prefix == "77" || prefix == "73" || prefix == "71" || prefix == "78");
}

bool isNumeric(const string& str) {
    for (int i = 0; i < str.length(); i++)
        if (!isdigit(str[i]) && str[i] != '.') return false;
    return true;
}

// ===== أسماء الملفات =====
const string USER_FILE = "users.txt";
const string PROD_FILE = "products.txt";
const string SALE_FILE = "sales.txt";

// ===== تعريف الدوال =====
void login();
void adminMenu();
void employeeMenu();

// Admin
bool isUsernameExists(const string& username);
void addUser();
void viewUsers();
void deleteUser();
void manageUserStatus();
void showStatistics();

// Employee
void addProduct();
void viewProducts();
void searchProduct();
void updateProduct();
void deleteProduct();
void sellProduct();
void showReports();

// ===== Main =====
int main() {
    ifstream check(USER_FILE);
    if (!check.good()) {
        ofstream file(USER_FILE);
        file << "admin 1234 Admin 777777777 active male\n";
        file.close();
    }
    check.close();

    int choice;
    do {
        cout << "\n=== Super Market System ===\n";
        cout << "1. Login\n2. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) login();
    } while (choice != 2);

    return 0;
}

// ===== Login =====
void login() {
    string u, p;
    cout << "Username: "; cin >> u;
    cout << "Password: "; cin >> p;

    ifstream file(USER_FILE);
    string fu, fp, fr, fph, fs, fg;

    while (file >> fu >> fp >> fr >> fph >> fs >> fg) {
        if (fu == u && fp == p) {
            if (fs == "inactive") {
                cout << "Account inactive.\n";
                return;
            }
            cout << "Login successful.\n";
            (fr == "Admin") ? adminMenu() : employeeMenu();
            return;
        }
    }
    cout << "Invalid login.\n";
}

// ================= ADMIN =================
void adminMenu() {
    int c;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add User\n2. View Users\n3. Delete User\n";
        cout << "4. Activate/Deactivate User\n5. Statistics\n6. Logout\nChoice: ";
        cin >> c;

        switch (c) {
            case 1: addUser(); break;
            case 2: viewUsers(); break;
            case 3: deleteUser(); break;
            case 4: manageUserStatus(); break;
            case 5: showStatistics(); break;
        }
    } while (c != 6);
}

bool isUsernameExists(const string& username) {
    ifstream file(USER_FILE);
    string u, p, r, ph, s, g;
    while (file >> u >> p >> r >> ph >> s >> g)
        if (u == username) return true;
    return false;
}

void addUser() {
    User u;
    cout << "Username: "; cin >> u.username;

    if (!isValidUsername(u.username)) {
        cout << "Invalid username.\n"; return;
    }
    if (isUsernameExists(u.username)) {
        cout << "The username is found.\n"; return;
    }

    cout << "Password: "; cin >> u.password;

    do {
        cout << "Role (Admin/Employee): ";
        cin >> u.role;
    } while (u.role != "Admin" && u.role != "Employee");

    cout << "Phone: "; cin >> u.phone;
    if (!isValidPhone(u.phone)) {
        cout << "Invalid phone.\n"; return;
    }

    do {
        cout << "Gender (male/female): ";
        cin >> u.gender;
    } while (u.gender != "male" && u.gender != "female");

    u.status = "active";

    ofstream file(USER_FILE, ios::app);
    file << u.username << " " << u.password << " " << u.role << " "
         << u.phone << " " << u.status << " " << u.gender << endl;
    file.close();

    cout << "User added successfully.\n";
}

void viewUsers() {
    ifstream file(USER_FILE);
    string u, p, r, ph, s, g;

    cout << left << setw(15) << "Username" << setw(10) << "Role"
         << setw(12) << "Phone" << setw(10) << "Status" << setw(10) << "Gender" << endl;

    while (file >> u >> p >> r >> ph >> s >> g) {
        cout << left << setw(15) << u << setw(10) << r
             << setw(12) << ph << setw(10) << s << setw(10) << g << endl;
    }
}

void deleteUser() {
    string target;
    cout << "Username to delete: "; cin >> target;
    if (target == "admin") {
        cout << "Cannot delete admin.\n"; return;
    }

    ifstream in(USER_FILE);
    ofstream out("temp.txt");
    string u, p, r, ph, s, g;
    bool found = false;

    while (in >> u >> p >> r >> ph >> s >> g) {
        if (u == target) { found = true; continue; }
        out << u << " " << p << " " << r << " " << ph << " " << s << " " << g << endl;
    }

    in.close(); out.close();
    remove(USER_FILE.c_str());
    rename("temp.txt", USER_FILE.c_str());

    cout << (found ? "User deleted.\n" : "User not found.\n");
}

void manageUserStatus() {
    string target;
    cout << "Username: "; cin >> target;

    vector<User> users;
    ifstream file(USER_FILE);
    string u, p, r, ph, s, g;
    bool found = false;

    while (file >> u >> p >> r >> ph >> s >> g) {
        User usr = {u,p,r,ph,s,g};
        if (u == target) {
            cout << "New status (active/inactive): ";
            cin >> usr.status;
            found = true;
        }
        users.push_back(usr);
    }
    file.close();

    if (!found) { cout << "User not found.\n"; return; }

    ofstream out(USER_FILE);
    for (int i = 0; i < users.size(); i++)
        out << users[i].username << " " << users[i].password << " " << users[i].role << " "
            << users[i].phone << " " << users[i].status << " " << users[i].gender << endl;
    out.close();

    cout << "Status updated.\n";
}

void showStatistics() {
    ifstream u(USER_FILE), p(PROD_FILE);
    int uc = 0, pc = 0;
    string line;

    while (getline(u, line)) uc++;
    while (getline(p, line)) pc++;

    cout << "Users: " << uc << "\nProducts: " << pc << endl;
}

// ================= EMPLOYEE =================
void employeeMenu() {
    int c;
    do {
        cout << "\n--- Employee Menu ---\n";
        cout << "1.Add Product\n2.View Products\n3.Search\n4.Update\n";
        cout << "5.Delete\n6.Sell\n7.Reports\n8.Logout\nChoice: ";
        cin >> c;

        switch (c) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: sellProduct(); break;
            case 7: showReports(); break;
        }
    } while (c != 8);
}

void addProduct() {
    Product p;
    cout << "ID: "; cin >> p.id;
    cin.ignore();
    cout << "Name: "; getline(cin, p.name);

    string ps;
    cout << "Price: "; cin >> ps;
    if (!isNumeric(ps)) { cout << "Invalid price.\n"; return; }
    p.price = stod(ps);

    cout << "Quantity: "; cin >> p.quantity;

    ofstream file(PROD_FILE, ios::app);
    file << p.id << " " << p.name << " " << p.price << " " << p.quantity << endl;
    cout << "Product added.\n";
}

void viewProducts() {
    ifstream file(PROD_FILE);
    int id, q;
    double pr;
    string name;

    while (file >> id >> name >> pr >> q)
        cout << id << " | " << name << " | $" << pr << " | Qty: " << q << endl;
}

void searchProduct() {
    int id;
    cout << "Enter ID: "; cin >> id;

    ifstream file(PROD_FILE);
    int pid, q;
    double pr;
    string name;

    while (file >> pid >> name >> pr >> q)
        if (pid == id) {
            cout << name << " $" << pr << " Qty:" << q << endl;
            return;
        }
    cout << "Not found.\n";
}

void updateProduct() {
    int id;
    cout << "Product ID: "; cin >> id;

    vector<Product> v;
    ifstream file(PROD_FILE);
    Product p;
    bool found = false;

    while (file >> p.id >> p.name >> p.price >> p.quantity) {
        if (p.id == id) {
            cout << "New price: "; cin >> p.price;
            cout << "New quantity: "; cin >> p.quantity;
            found = true;
        }
        v.push_back(p);
    }
    file.close();

    if (!found) { cout << "Not found.\n"; return; }

    ofstream out(PROD_FILE);
    for (int i = 0; i < v.size(); i++)
        out << v[i].id << " " << v[i].name << " " << v[i].price << " " << v[i].quantity << endl;
}

void deleteProduct() {
    int id;
    cout << "ID: "; cin >> id;

    ifstream in(PROD_FILE);
    ofstream out("temp.txt");
    Product p;
    bool found = false;

    while (in >> p.id >> p.name >> p.price >> p.quantity) {
        if (p.id == id) { found = true; continue; }
        out << p.id << " " << p.name << " " << p.price << " " << p.quantity << endl;
    }

    in.close(); out.close();
    remove(PROD_FILE.c_str());
    rename("temp.txt", PROD_FILE.c_str());

    cout << (found ? "Deleted.\n" : "Not found.\n");
}

void sellProduct() {
    int id, qty;
    cout << "Product ID: "; cin >> id;
    cout << "Quantity: "; cin >> qty;
    if (qty <= 0) return;

    vector<Product> v;
    ifstream file(PROD_FILE);
    Product p;
    bool found = false;
    double total = 0;
    string name;

    while (file >> p.id >> p.name >> p.price >> p.quantity) {
        if (p.id == id && p.quantity >= qty) {
            p.quantity -= qty;
            total = p.price * qty;
            name = p.name;
            found = true;
        }
        v.push_back(p);
    }
    file.close();

    if (!found) { cout << "Cannot sell.\n"; return; }

    ofstream out(PROD_FILE);
    for (int i = 0; i < v.size(); i++)
        out << v[i].id << " " << v[i].name << " " << v[i].price << " " << v[i].quantity << endl;

    Sale s = {id, name, total, qty};
    ofstream sale(SALE_FILE, ios::app);
    sale << s.id << " " << s.productName << " " << s.totalPrice << " " << s.quantity << endl;

    cout << "\n=== INVOICE ===\n";
    cout << "Product: " << name << "\nQty: " << qty << "\nTotal: $" << total << endl;
}

void showReports() {
    ifstream file(SALE_FILE);
    vector<ItemCount> v;
    int id, q;
    double price;
    string name;
    double total = 0;

    while (file >> id >> name >> price >> q) {
        total += price;
        bool ok = false;
        for (int i = 0; i < v.size(); i++)
            if (v[i].name == name) { v[i].count += q; ok = true; }
        if (!ok) v.push_back({name, q});
    }


    // فرز المنتجات حسب العدد
    for (int i = 0; i < v.size(); i++)
        for (int j = i + 1; j < v.size(); j++)
            if (v[i].count < v[j].count) swap(v[i], v[j]);

    cout << "Total Sales: $" << total << endl;
    cout << "Top 5 Products:\n";
    for (int i = 0; i < v.size() && i < 5; i++)
        cout << i+1 << ". " << v[i].name << " (" << v[i].count << ")\n";
}