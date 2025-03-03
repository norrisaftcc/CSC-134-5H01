#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

const int SIDES = 6;
int seed = time(0);
int roll;
string currentPlayer, currentClass;
int level, hp, strength, constit, dex, intel, wisdom, rizz;
void inputStats();
void displayCharacter();
void saveCharacter();
int rollDice();
int rollStat();
void characterCreation();
string chooseClass();

using namespace std;

int main() {
    characterCreation();
    cout << "Main Success!" << endl;
}

void characterCreation() {
    srand(seed);
    int classChoice;
    char choice2, choice3;

do {
    currentClass = chooseClass();
    cout << "" << endl;
    cout << "Your character is a " << currentClass << "!" << endl;
    cout << "Here are your stats" << endl;
    inputStats();
    displayCharacter();
    cout << "Type 'a' to accept, 'r' to reroll." << endl;
    char choice;
    cin >> choice;
    cout << "" << endl;
    while ('r' == choice) {
        inputStats();
        displayCharacter();
        cout << "Type 'a' to accept, 'r' to reroll." << endl;
        cin >> choice;
        cout << "" << endl;
    }
    cout << "Please name your character: ";
    cin >> currentPlayer;

    cout << "You are " << currentPlayer << " the " << currentClass << " will you accept? Type 'a' to accept, 'r' to reroll." << endl;
    cin >> choice2;
}while(choice2 == 'r');
    std::ofstream outfile("character.txt", std::ios::app);
    if (!outfile) {
        std::cerr << "Error opening file for writing!" << std::endl;
    }
    outfile << currentPlayer << " " << currentClass << " " << strength << " " << dex << " " << constit << " " << intel << " " << wisdom << " " << rizz << std::endl;
    outfile.close();

    std::cout << "File written successfully!" << std::endl;
}

void displayCharacter() {
    cout << "\nCharacter Stats:\n";
    cout << "Strength: " << strength << endl;
    cout << "Dexterity: " << dex << endl;
    cout << "Constitution: " << constit << endl;
    cout << "Intelligence: " << intel << endl;
    cout << "Wisdom: " << wisdom << endl;
    cout << "Charisma: " << rizz << endl;
    cout << "" << endl;
}

void inputStats() {
    cout << "Rolling your character..." << endl;
    strength = rollStat();
    dex = rollStat();
    constit = rollStat();
    intel = rollStat();
    wisdom = rollStat();
    rizz = rollStat();
}

int rollDice() {
    return rand() % 6 + 1;
}

int rollStat() {
    // roll 3d6
    int stat;
    stat = rollDice() + rollDice() + rollDice();
    return stat;
}

string chooseClass() {
    int classChoice;


    cout << "Please choose a class from the list." << endl;
    cout << "1: Fighter" << endl;
    cout << "2: Magic-User" << endl;
    cout << "3: Thief" << endl;
    cout << "4: Cleric" << endl;
    cout << "5: Elf" << endl;
    cout << "6: Dwarf" << endl;
    cout << "7: Halfling" << endl;
    cout << "" << endl;
    cin >> classChoice;

    switch (classChoice)
    {
    case 1:
        currentClass = "Fighter";
        break;
    case 2:
        currentClass = "magicUser";
        //choice3 == 'a';
        break;
    case 3:
        currentClass = "Thief";
        //choice3 == 'a';
        break;
    case 4:
        currentClass = "Cleric";
        //choice3 == 'a';
        break;
    case 5:
        currentClass = "Elf";
        //choice3 == 'a';
        break;
    case 6:
        currentClass = "Dwarf";
        //choice3 == 'a';
        break;
    case 7:
        currentClass = "Halfling";
        //choice3 == 'a';
        break;
    default:
        cout << "Invalid Selection" << endl;
        currentClass = chooseClass();
        //choice3 == 'r';
        break;
    }
    return currentClass;
}