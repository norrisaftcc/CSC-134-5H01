#include <iostream>
using namespace std;

void repeater();

int main(){
    repeater();
}

void repeater(){
    int num1;
    cout << "Enter a number from 1 to 12: ";
    cin >> num1;

    while (num1 < 1 || num1 > 12) {
        cout << "That number wasn't between 1 to 12: ";
        cin >> num1;
    } 


    cout << num1 << " times 1 is " << num1*1 << "." << endl;
    cout << num1 << " times 2 is " << num1*2 << "." << endl;
    cout << num1 << " times 3 is " << num1*3 << "." << endl;
    cout << num1 << " times 4 is " << num1*4 << "." << endl;
    cout << num1 << " times 5 is " << num1*5 << "." << endl;
    cout << num1 << " times 6 is " << num1*6 << "." << endl;
    cout << num1 << " times 7 is " << num1*7 << "." << endl;
    cout << num1 << " times 8 is " << num1*8 << "." << endl;
    cout << num1 << " times 9 is " << num1*9 << "." << endl;
    cout << num1 << " times 10 is " << num1*10 << "." << endl;
    cout << num1 << " times 11 is " << num1*11 << "." << endl;
    cout << num1 << " times 12 is " << num1*12 << "." << endl;
}
