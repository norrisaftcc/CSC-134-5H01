#ifndef DND_H
#define DND_H

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
static int experience = 0;
//int maxExperience;
string currentPlayer, currentClass;
int level, hp, strength, constit, dex, intel, wisdom, rizz;
bool newPlayerCheck;
int statPoints = 0;
int lastProficiencyBonus = 2;
int proficiencyPoints = 0;

void updateLevel();
void inputStats();
void displayCharacter();
void saveCharacter();
void overwriteCharacterData();
void spendStatPoints();
int rollDice();
int rollStat();
int newPlayer();
void characterCreation();
int load_progress();
string chooseClass();
string encryptDecrypt(const string &input, const string &key);
string encryptStats(const string &stats);
string decryptStats(const string &encryptedStats);
string encryptPassword(const string &password);
string decryptPassword(const string &encryptedPassword);
string hashPassword(const string &password);
bool checkPassword(const string &username, const string &password);
int getProficiencyBonus();

/* -------------------------------------------------------------------------- */
//SECTION                         Encryption and Decryption                         */
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

//!SECTION -------------------------------------------------------------------------- */






/* -------------------------------------------------------------------------- */
//SECTION                             Character Creation                             */


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
        to_string(intel) + " " + to_string(wisdom) + " " + to_string(rizz) + " " + to_string(level) + " " + to_string(experience);

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

//NOTE - Display Character

void displayCharacter() {
    if (statPoints > 0) {
        spendStatPoints();  // Prompt user to spend points if they have any
    }

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
    cout << "Level: " << level << " | XP: " << experience << endl;
    cout << "Unspent Stat Points: " << statPoints << endl;
    cout << "" << endl;
}

//NOTE - Character initial stats

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
    return (rand() % 6) + 1;
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

//NOTE - NEW PLAYER

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

        // Parse the stats with proper error handling
        if (!(ssDecrypted >> strength >> dex >> constit >> intel >> wisdom >> rizz >> level >> experience)) {
            cerr << "Error parsing character stats for " << currentPlayer << "!" << endl;
            return -1;
        }

        // Check if the current player's name matches the input name
        if (currentPlayer == name2) {
            newPlayerCheck = false; // Player found, stop the loop
            break;
        }
    }

    statsFile.close();

    if (!newPlayerCheck) {
        // Player exists, now prompt for password
        string enteredPassword;
        cout << "Player found: " << currentPlayer << ". Please enter your password: ";
        cin >> enteredPassword;

        // Check if the entered password matches the stored password
        if (checkPassword(currentPlayer, enteredPassword)) {
            cout << "Password correct. Access granted!" << endl;

            // After successful login, update their data (XP, level, stat points)
            overwriteCharacterData();  // Ensure stats are saved correctly after login

        } else {
            cout << "Incorrect password! Access denied." << endl;

            // Ask if they want to reset their password
            char resetChoice;
            cout << "Would you like to reset your password? (y/n): ";
            cin >> resetChoice;

            if (resetChoice == 'y' || resetChoice == 'Y') {
                // Prompt for the correct class name
                string enteredClass;
                cout << "Please enter your class: ";
                cin >> enteredClass;

                // Check if the class is correct
                if (enteredClass == currentClass) {
                    string newPassword;
                    cout << "Class confirmed. Please enter a new password: ";
                    cin >> newPassword;

                    // Encrypt the new password
                    string encryptedNewPassword = encryptPassword(newPassword);

                    // Read existing passwords and update the file
                    ifstream passwordFileRead("passwords.txt");
                    if (!passwordFileRead) {
                        cerr << "Error opening password file for reading!" << endl;
                        return -1;
                    }

                    stringstream updatedPasswordFileContent;
                    bool found = false;

                    while (getline(passwordFileRead, line)) {
                        stringstream ss(line);
                        string fileUser, filePassword;
                        ss >> fileUser >> filePassword;

                        if (fileUser == currentPlayer) {
                            // Update the password for the current player
                            updatedPasswordFileContent << fileUser << " " << encryptedNewPassword << endl;
                            found = true;
                        } else {
                            // Keep the original lines for other users
                            updatedPasswordFileContent << line << endl;
                        }
                    }
                    passwordFileRead.close();

                    // If user was found, update the file
                    if (found) {
                        ofstream updatedPasswordFile("passwords.txt", ios::trunc);
                        if (!updatedPasswordFile) {
                            cerr << "Error opening password file for writing!" << endl;
                            return -1;
                        }
                        updatedPasswordFile << updatedPasswordFileContent.str();
                        updatedPasswordFile.close();

                        cout << "Password reset successfully!" << endl;
                    } else {
                        cout << "Error: User not found in password file!" << endl;
                    }
                } else {
                    cout << "Incorrect class name. Exiting the program." << endl;
                    exit(0);
                }
            } else {
                cout << "Access denied. Exiting the program." << endl;
                exit(0);
            }
        }
    } else {
        cout << "Player not found. Creating a new player..." << endl;
        newPlayerCheck = true;
    }

    return newPlayerCheck;
}

//NOTE - Load Progress

int load_progress() {
    ifstream progressFile("player_progress.txt");
    int lastChoice = 0;
    if (progressFile) {
        string name, encryptedChoice;
        while (progressFile >> name >> encryptedChoice) {
            // Decrypt the progress for each player
            string decryptedChoice = decryptStats(encryptedChoice);
            if (name == currentPlayer) {
                lastChoice = stoi(decryptedChoice);  // Convert decrypted choice to integer
                break;  // Stop once we find the current player
            }
        }
        progressFile.close();
    } else {
        cerr << "Error: Unable to load progress!" << endl;
    }
    return lastChoice;
}

//!SECTION -------------------------------------------------------------------------- */









// -------------------------------------------------------------------------- */
//SECTION                                    Level                                   */
void updateLevel() {
    int oldLevel = level;

    // XP thresholds for leveling up
    int xpThresholds[] = {
        0, 300, 900, 2700, 6500, 14000, 23000, 34000, 48000, 64000,
        85000, 100000, 120000, 140000, 165000, 195000, 225000, 265000,
        305000, 355000
    };

    // Level up logic based on experience points
    for (int i = 19; i >= 0; --i) {
        if (experience >= xpThresholds[i]) {
            level = i + 1;
            break;
        }
    }

    // Add stat points based on the new level
    int statPointsAdded = level - oldLevel; // You gain one stat point per level
    statPoints += statPointsAdded;  // Increase the stat points

    // Notify player about the stat points added
    if (statPointsAdded > 0 && level > oldLevel) { // Fixed condition: check if NEW level > OLD level
        cout << "\n🆙 You've leveled up to Level " << level << "!" << endl;
        cout << "🎁 You received " << statPointsAdded << " stat point(s)!" << endl;
    }

    // Save the updated character stats to file
    if (level != oldLevel) {
        stringstream updatedStatsFileContent;
        string line;
        bool foundPlayer = false;

        ifstream statsFileRead("character_stats.txt");
        if (statsFileRead) {
            while (getline(statsFileRead, line)) {
                stringstream ss(line);
                string storedName, storedClass, encryptedStats;
                ss >> storedName >> storedClass >> encryptedStats;

                // Update the player's stats if their name matches
                if (storedName == currentPlayer) {
                    string updatedStats = to_string(strength) + " " + to_string(dex) + " " + to_string(constit) + " " +
                                          to_string(intel) + " " + to_string(wisdom) + " " + to_string(rizz) + " " +
                                          to_string(level) + " " + to_string(experience);

                    string encryptedUpdatedStats = encryptStats(updatedStats);
                    updatedStatsFileContent << storedName << " " << storedClass << " " << encryptedUpdatedStats << endl;
                    foundPlayer = true; //Update Character with new stats
                } else {
                    updatedStatsFileContent << line << endl; //Populates file on new occurrence
                }
            }
            statsFileRead.close();

            // Write the updated content back to the file
            if (foundPlayer) {
                ofstream statsFileWrite("character_stats.txt", ios::trunc);
                if (statsFileWrite) {
                    statsFileWrite << updatedStatsFileContent.str();
                    statsFileWrite.close();
                } else {
                    cerr << "Error opening stats file for writing!" << endl;
                }
            }
        } else {
            cerr << "Error opening stats file for reading!" << endl;
        }
    }
    // Additional level-up actions like learning new abilities can be placed here
}


void spendStatPoints() {
    if (statPoints == 0) {
        cout << "You have no stat points to spend!" << endl;
        return;
    }

    cout << "You have " << statPoints << " stat point(s) to spend!" << endl;
    cout << "Choose a stat to improve:" << endl;
    cout << "1. Strength: " << strength << endl;
    cout << "2. Dexterity: " << dex << endl;
    cout << "3. Constitution: " << constit << endl;
    cout << "4. Intelligence: " << intel << endl;
    cout << "5. Wisdom: " << wisdom << endl;
    cout << "6. Charisma: " << rizz << endl;
    cout << "Enter the number of the stat you want to increase: ";
    
    int choice;
    cin >> choice;

    if (choice < 1 || choice > 6) {
        cout << "Invalid choice!" << endl;
        return;
    }

    // Spend stat points on the chosen stat
    int* stat = nullptr;
    switch (choice) {
        case 1: stat = &strength; break;
        case 2: stat = &dex; break;
        case 3: stat = &constit; break;
        case 4: stat = &intel; break;
        case 5: stat = &wisdom; break;
        case 6: stat = &rizz; break;
    }

    // Spend the stat point and update the stat
    if (statPoints > 0) {
        (*stat)++;  // Increase the chosen stat by 1
        statPoints--;  // Deduct one stat point
        cout << "You increased your stat! Current value: " << *stat << endl;
        saveCharacter();
    }
}

//!SECTION -------------------------------------------------------------------------- */








/* -------------------------------------------------------------------------- */
//SECTION                              Character Saving                              */

void saveCharacter() {
    ifstream statsFileRead("character_stats.txt");
    if (!statsFileRead) {
        cerr << "Error opening stats file for reading!" << endl;
        return;
    } //Open Character Stats

    stringstream updatedStatsFileContent;
    string line;
    bool foundPlayer = false;

    while (getline(statsFileRead, line)) {
        stringstream ss(line);
        string storedName, storedClass, encryptedStats;
        ss >> storedName >> storedClass >> encryptedStats;

        // Update the player's stats if their name matches
        if (storedName == currentPlayer) {
            string updatedStats = to_string(strength) + " " + to_string(dex) + " " + to_string(constit) + " " +
                                  to_string(intel) + " " + to_string(wisdom) + " " + to_string(rizz) + " " + to_string(level) + " " + to_string(experience);

            string encryptedUpdatedStats = encryptStats(updatedStats);
            updatedStatsFileContent << storedName << " " << storedClass << " " << encryptedUpdatedStats << endl;
            foundPlayer = true; //Update Character with new stats
        } else {
            updatedStatsFileContent << line << endl; //Populates file on  new occurance
        }
    }

    statsFileRead.close();

    if (foundPlayer) {
        ofstream updatedStatsFile("character_stats.txt", ios::trunc); // Use trunc to overwrite
        if (!updatedStatsFile) {
            cerr << "Error opening stats file for writing!" << endl;
            return;
        }
        updatedStatsFile << updatedStatsFileContent.str();
        updatedStatsFile.close();
    } else {
        cerr << "Player not found in stats file!" << endl;
    }
}



void overwriteCharacterData() {
    // Open the file to read and write
    ifstream statsFile("character_stats.txt");
    if (!statsFile) {
        cerr << "Error opening stats file for reading!" << endl;
        return;
    }

    stringstream updatedStatsFileContent;
    string line;
    bool foundPlayer = false;

    // Read each line and look for the player's name
    while (getline(statsFile, line)) {
        stringstream ss(line);
        string storedName, storedClass, encryptedStats;
        ss >> storedName >> storedClass >> encryptedStats;

        if (storedName == currentPlayer) {
            // Update this player's stats
            string updatedStats = to_string(strength) + " " + to_string(dex) + " " + to_string(constit) + " " +
                                  to_string(intel) + " " + to_string(wisdom) + " " + to_string(rizz) + " " + to_string(level) + " " + to_string(experience);

            // Encrypt the stats
            string encryptedUpdatedStats = encryptStats(updatedStats);
            updatedStatsFileContent << storedName << " " << storedClass << " " << encryptedUpdatedStats << endl;
            foundPlayer = true;
        } else {
            updatedStatsFileContent << line << endl; // Copy other players' data as is
        }
    }

    statsFile.close();

    // If the player was found and updated, overwrite the file
    if (foundPlayer) {
        ofstream updatedStatsFile("character_stats.txt", ios::trunc);
        if (!updatedStatsFile) {
            cerr << "Error opening stats file for writing!" << endl;
            return;
        }
        updatedStatsFile << updatedStatsFileContent.str();
        updatedStatsFile.close();
    } else {
        cerr << "Player not found in stats file!" << endl;
    }
}

//!SECTION -------------------------------------------------------------------------- */


#endif // DND_H



