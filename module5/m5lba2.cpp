#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

void experiencePoints(int& experience, int& level, int& levelUp);

int main() {
    int choice = 1;
    int experience = 0;
    int level = 1;
    int levelUp = 1000;

    do {
        experiencePoints(experience, level, levelUp);
        cout << "Do you want to run this program again (1 for yes, 0 for no): ";
        cin >> choice;
    } while (choice == 1);

    return 0;
}

void experiencePoints(int& experience, int& level, int& levelUp) {
    int experienceAdd;

    cout << "Enter experience to add: ";
    cin >> experienceAdd;

    experience += experienceAdd;

    while (experience >= levelUp) {
        experience -= levelUp;
        level++;
        levelUp = 1000 * level;
        cout << "Level Up! Now at Level " << level << "!" << endl;
    }

    cout << "Experience to next level: " << experience << "/" << levelUp << endl;
    cout << "Current Level: " << level << endl;
}



