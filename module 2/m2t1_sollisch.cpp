#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    string customer_name;
    int apples_to_buy;
    const double APPLEPRICE = .25;
    string farm_name = "Jack";

    cout << "Hi, what's your name? ";
    cin >> customer_name;
    cout << "Nice to meet you, " << customer_name << " welcome to the " << farm_name << " farm!" << endl;

    cout << "How many apples do you want? ";
    cin >> apples_to_buy;
    double customer_cost = apples_to_buy * APPLEPRICE;
    cout << "For " << apples_to_buy << " your total is $" << customer_cost << endl;

    return 0;
}