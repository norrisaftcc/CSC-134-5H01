//Jack Sollisch
// 1/15/2025

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    string store_name = "Jack's Burger";
    string burger_name = "burger", fries = "fries";
    double fries_price = 5.99, burger_price = 10.99, subtotal, total, tax_cost;
    const double tax_percent = .08;
    int burger_number, fries_number, food_price;
    cout <<"How many burgers do you want?" << endl;
    cin >> burger_number;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout <<"Thank you for your purchase!" << endl;
    burger_price = burger_number * burger_price;
    if (burger_number >= 2) {
        cout <<"You ordered " << burger_number << " " << burger_name << "s and it's $" << burger_price << endl;
    }
    else if (burger_number = 1) {
        cout <<"You ordered " << burger_number << " " << burger_name << " and it's $" << burger_price << endl;
    }
    else {
        cout << "Have a nice day!" << endl;
    }
    cout <<"How many fries do you want?" << endl;
    cin >> fries_number;
    fries_price = fries_number * fries_price;
    if (fries_number >= 1) {
        cout <<"You ordered " << fries_number << " " << fries << " and it's $" << fries_price << endl;
    }
    else {
        cout << "Have a nice day!" << endl;
    }
    subtotal = burger_price + fries_price;
    tax_cost = subtotal * tax_percent;
    total = subtotal + tax_cost;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << setw(5) << setprecision(2) << fixed << endl;
    cout << "Subtotal: " << setw(8) << "\t$" << subtotal << endl;
    cout << "Sales Tax (8%):" << setw(8) << " \t$" << tax_cost << endl;
    cout << "_______________________________" << endl;
    cout << setw(12) << "Total: " << setw(8) << " \t$" << total << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    return 0;
}