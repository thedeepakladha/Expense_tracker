#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <map>
using namespace std;

struct Expense {
    string date;      // format: YYYY-MM-DD
    string category;
    double amount;
    string description;
};

void addExpense() {
    ofstream fout("expenses.txt", ios::app);
    Expense e;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> e.date;
    cin.ignore();
    cout << "Enter category (e.g., Food, Travel, Shopping): ";
    getline(cin, e.category);
    cout << "Enter amount: ";
    cin >> e.amount;
    cin.ignore();
    cout << "Enter description: ";
    getline(cin, e.description);
    fout << e.date << "|" << e.category << "|" << fixed << setprecision(2) << e.amount << "|" << e.description << endl;
    fout.close();
    cout << "Expense added successfully!\n";
}

vector<Expense> loadExpenses() {
    vector<Expense> expenses;
    ifstream fin("expenses.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        Expense e;
        getline(ss, e.date, '|');
        getline(ss, e.category, '|');
        string amountStr;
        getline(ss, amountStr, '|');
        e.amount = stod(amountStr);
        getline(ss, e.description);
        expenses.push_back(e);
    }
    fin.close();
    return expenses;
}

void viewAllExpenses() {
    vector<Expense> expenses = loadExpenses();
    cout << "\n--- All Expenses ---\n";
    cout << left << setw(12) << "Date" << setw(15) << "Category" << setw(10) << "Amount" << "Description\n";
    cout << "-------------------------------------------------------------\n";
    for (auto &e : expenses) {
        cout << left << setw(12) << e.date << setw(15) << e.category << setw(10) << e.amount << e.description << endl;
    }
}

void viewByCategory() {
    vector<Expense> expenses = loadExpenses();
    string searchCat;
    cout << "Enter category to view: ";
    cin.ignore();
    getline(cin, searchCat);
    cout << "\n--- Expenses in Category: " << searchCat << " ---\n";
    cout << left << setw(12) << "Date" << setw(10) << "Amount" << "Description\n";
    cout << "---------------------------------------------\n";
    double total = 0;
    for (auto &e : expenses) {
        if (e.category == searchCat) {
            cout << left << setw(12) << e.date << setw(10) << e.amount << e.description << endl;
            total += e.amount;
        }
    }
    cout << "Total spent in " << searchCat << ": " << total << endl;
}

void monthlySummary() {
    vector<Expense> expenses = loadExpenses();
    map<string, double> monthTotals;
    for (auto &e : expenses) {
        string month = e.date.substr(0, 7); // YYYY-MM
        monthTotals[month] += e.amount;
    }
    cout << "\n--- Monthly Summary ---\n";
    for (auto &pair : monthTotals) {
        cout << "Month: " << pair.first << " | Total Spent: " << pair.second << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- Personal Expense Tracker ---\n";
        cout << "1. Add Expense\n2. View All Expenses\n3. View by Category\n4. Monthly Summary\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewAllExpenses(); break;
            case 3: viewByCategory(); break;
            case 4: monthlySummary(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
    return 0;
}
