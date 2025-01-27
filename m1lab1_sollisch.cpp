//CSC 134
//Jack Sollisch
// 1/27/2025

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    string name = "Jack";
    int num_apples = 100;
    double price_each = .25;

    cout <<"Welcome to the " << name << " apple farm." << endl;
    cout <<"We have " << num_apples << " apples in stock." << endl;
    cout <<"Price per apple is: $" << price_each << endl;

    double total_cost = num_apples * price_each;
    cout << fixed << setprecision(2);
    cout <<"The total for all " << num_apples << " apples is $" << total_cost << endl;

    return 0;
}