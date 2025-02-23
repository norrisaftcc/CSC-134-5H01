#include <iostream>
#include <iomanip>

using namespace std;


int main() {
    cout << "CSC-134" << endl;
    cout << "M2HW1 - Silver" << endl;
    cout << "Name: Jack Sollisch" << endl;
    cout << "Date: 2/23/2025" << endl;
    cout << endl;
    
    // Question 1: Banking Transactions
    string name;
    double startingBalance, deposit, withdrawal, finalBalance;
    const int ACCOUNTNUMBER = 69420;

    cout << "Question 1: Banking Transactions" << endl;
    cout << "Enter your full name: ";
    getline(cin, name);
    
    cout << "Enter starting account balance: $";
    cin >> startingBalance;
    cout << "Enter deposit amount: $";
    cin >> deposit;
    cout << "Enter withdrawal amount: $";
    cin >> withdrawal;

    finalBalance = startingBalance + deposit - withdrawal;
    
    cout << fixed << setprecision(2); // Formatting money values to two decimal places
    cout << "\nAccount Summary:\n";
    cout << "Name: " << name << endl;
    cout << "Account Number: " << ACCOUNTNUMBER << endl;
    cout << "Final Balance: $" << finalBalance << endl;

    // Question 2: Storage Cost Calculation
    double length, width, height, volume, storageCost, maxChargeRate = 0.52;
    const double costPerCubicFoot = 0.3;
    
    cout << "\nQuestion 2: Storage Cost Calculation" << endl;
    cout << "Enter length of the crate (feet): ";
    cin >> length;
    cout << "Enter width of the crate (feet): ";
    cin >> width;
    cout << "Enter height of the crate (feet): ";
    cin >> height;
    
    volume = length * width * height;
    storageCost = volume * costPerCubicFoot;
    
    cout << fixed << setprecision(2);
    cout << "\nStorage Summary:\n";
    cout << "Crate Volume: " << volume << " cubic feet" << endl;
    cout << "Storage Cost: $" << storageCost << endl;
    cout << "Max Charge Allowed: $" << (volume * maxChargeRate) << endl;
    
    return 0;
}

