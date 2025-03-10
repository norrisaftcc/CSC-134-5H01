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

const int SIDES = 6;
int seed = time(0);
int roll;
int experience, maxExperience;
string currentPlayer, currentClass;
int level, hp, strength, constit, dex, intel, wisdom, rizz;
bool newPlayerCheck;

void inputStats();
void displayCharacter();
void saveCharacter();
int rollDice();
int rollStat();
int newPlayer();
void characterCreation();
string chooseClass();
string encryptDecrypt(const string &input, const string &key);
string encryptStats(const string &stats);
string decryptStats(const string &encryptedStats);
string encryptPassword(const string &password);
string decryptPassword(const string &encryptedPassword);
string hashPassword(const string &password);
bool checkPassword(const string &username, const string &password);

int main() {
    if (newPlayer()) {
        characterCreation();
    } else {
        displayCharacter();
    }

    cout << "Main Success!" << endl;
}

// XOR encryption/decryption function
string encryptDecrypt(const string &input, const string &key) {
    string output = input;
    for (size_t i = 0; i < input.size(); i++) {
        output[i] = input[i] ^ key[i % key.size()];
    }
    return output;
}

// Encrypt the stats before storing
string encryptStats(const string &stats) {
    string key = "some_secret_key";  // You can use a better key management method
    return encryptDecrypt(stats, key);
}

// Decrypt the stats when loading
string decryptStats(const string &encryptedStats) {
    string key = "some_secret_key";  // Use the same key for decryption
    return encryptDecrypt(encryptedStats, key);
}

// Encrypt the password before saving
string encryptPassword(const string &password) {
    string key = "password_secret_key";  // You can use a better key management method
    return encryptDecrypt(password, key);
}

// Decrypt the password when checking login
string decryptPassword(const string &encryptedPassword) {
    string key = "password_secret_key";  // Use the same key for decryption
    return encryptDecrypt(encryptedPassword, key);
}

// Simple hash function for passwords (used as an additional layer of security)
string hashPassword(const string &password) {
    unsigned long hash = 5381;
    for (char c : password) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << hash;
    return ss.str();
}

// Check if the password is correct by decrypting and comparing
bool checkPassword(const string &username, const string &password) {
    ifstream passwordFile("passwords.txt");
    if (!passwordFile) {
        cerr << "Error opening password file!" << endl;
        return false;
    }

    string fileUser, filePassword;
    while (passwordFile >> fileUser >> filePassword) {
        // Decrypt the stored password
        string decryptedPassword = decryptPassword(filePassword);
        if (fileUser == username && decryptedPassword == password) {
            return true;  // Password matched
        }
    }
    return false;  // Password didn't match
}

void characterCreation() {
    srand(seed);
    int classChoice;
    char choice2;
    string password;

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

        cout << "Please create a password for your character: ";
        cin >> password;

        // Hash the password before storing it
        string hashedPassword = hashPassword(password);

        cout << "You are " << currentPlayer << " the " << currentClass << ". Will you accept? Type 'a' to accept, 'r' to reroll." << endl;
        cin >> choice2;
    } while(choice2 == 'r');

    // Encrypt the password before storing in the password file
    string encryptedPassword = encryptPassword(password);

    // Store the password in the password file
    ofstream passwordFile("passwords.txt", ios::app);
    if (!passwordFile) {
        cerr << "Error opening password file for writing!" << endl;
        return;
    }
    passwordFile << currentPlayer << " " << encryptedPassword << endl;
    passwordFile.close();

    // Concatenate stats into a single string before encryption
    string stats = to_string(strength) + " " + to_string(dex) + " " + to_string(constit) + " " +
                   to_string(intel) + " " + to_string(wisdom) + " " + to_string(rizz);

    // Encrypt the stats
    string encryptedStats = encryptStats(stats);

    // Store the player stats in the character stats file
    ofstream statsFile("character_stats.txt", ios::app);
    if (!statsFile) {
        cerr << "Error opening stats file for writing!" << endl;
        return;
    }
    statsFile << currentPlayer << " " << currentClass << " " << encryptedStats << endl;
    statsFile.close();

    cout << "Files written successfully!" << endl;
}

void displayCharacter() {
    cout << "\nCharacter Stats:\n";
    cout << " " << endl;
    cout << "Current Class: " << currentClass << endl;
    cout << "------------------------------------" << endl;
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

    switch (classChoice) {
    case 1:
        currentClass = "Fighter";
        break;
    case 2:
        currentClass = "Magic-User";
        break;
    case 3:
        currentClass = "Thief";
        break;
    case 4:
        currentClass = "Cleric";
        break;
    case 5:
        currentClass = "Elf";
        break;
    case 6:
        currentClass = "Dwarf";
        break;
    case 7:
        currentClass = "Halfling";
        break;
    default:
        cout << "Invalid Selection" << endl;
        currentClass = chooseClass();
        break;
    }
    return currentClass;
}

int newPlayer() {
    string name2;
    bool newPlayerCheck = true;
    cout << "Please enter your name: ";
    cin >> name2;

    // Check if the player exists in the character stats file
    ifstream statsFile("character_stats.txt");
    if (!statsFile) {
        cerr << "Error opening stats file!" << endl;
        return -1; // Indicating an error in opening file
    }

    string line;
    while (getline(statsFile, line)) {
        stringstream ss(line);
        string encryptedStats;
        ss >> currentPlayer >> currentClass >> encryptedStats;

        // Decrypt the stats
        string decryptedStats = decryptStats(encryptedStats);
        stringstream ssDecrypted(decryptedStats);

        ssDecrypted >> strength >> dex >> constit >> intel >> wisdom >> rizz;

        // Check if the current player's name matches the input name
        if (currentPlayer == name2) {
            newPlayerCheck = false; // Player found, stop the loop
            break;
        }
    }

    statsFile.close();

    if (newPlayerCheck == false) {
        // Player exists, now prompt for password
        string enteredPassword;
        cout << "Player found: " << currentPlayer << ". Please enter your password: ";
        cin >> enteredPassword;

        // Check if the entered password matches the stored hashed password
        if (checkPassword(currentPlayer, enteredPassword)) {
            cout << "Password correct. Access granted!" << endl;
        } else {
            cout << "Incorrect password! Access denied." << endl;
            exit(0);  // If password is incorrect, deny access
        }
    } else {
        cout << "Player not found. Creating a new player..." << endl;
        newPlayerCheck = true;
    }

    return newPlayerCheck;
}














