#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

//double getLength();
//double getWidth();
void experiencePoints();
int level;
double levels;

int main() {
//    double length = getLength();
//    double width = getWidth();
//    if (length == width) {
//        cout << "The area of the square is " << length * width << endl;
//        cout << "The perimeter of the square is " << length + length + width + width << endl;
//    } else {
//        cout << "The area of the rectangle is " << length * width << endl;
//        cout << "The perimeter of the rectangle is " << length + length + width + width << endl;
//    }

    experiencePoints();

    return 0;
}

//double getLength() {
//    double length;
//    cout << "Enter the length of the shape: ";
//    return length;
//}
//
//double getWidth() {
//    double width;
//    cout << "Enter the width of the shape: ";
//    return width;
//}

void experiencePoints() {
    int level = 1;
    int experience;
    int levelUp = 1000;

    cout << "Enter experience: ";
    cin >> experience;

    while (experience >= levelUp) {
        experience -= levelUp;
        level++;
        levelUp = 1000 * level;
        cout << "Level Up! Now at Level " << level << "!" << endl;
    }

    cout << "Experience to next level: " << experience << "/" << levelUp << endl;
    cout << "Current Level: " << level << endl;
}



