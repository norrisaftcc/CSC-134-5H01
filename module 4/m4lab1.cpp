#include <iostream>
using namespace std;

int main() {
    cout << "Enter emoji 1: ";
    string emoji1;
    cin >> emoji1;
    cout << "Enter emoji 2: ";
    string emoji2;
    cin >> emoji2;
    string pattern = emoji1 + emoji2;
    int WIDTH;
    int HEIGHT;
    cout << "Enter Width: ";
    cin >> WIDTH;
    cout << "Enter Height: ";
    cin >> HEIGHT;

    if (WIDTH == HEIGHT) {
    cout << "Square of " << WIDTH << " by " << HEIGHT << "." << endl;
    for (int i=0; i <HEIGHT; i++) {
    for (int i=0; i <WIDTH; i++) {
        cout << pattern;
        }
    cout << endl;
    }
    }
    else {
    cout << "Rectangle of " << WIDTH << " by " << HEIGHT << "." << endl;
    for (int i=0; i <HEIGHT; i++) {
    for (int i=0; i <WIDTH; i++) {
        cout << pattern;
        }
        cout << endl;
    }
    }
}

