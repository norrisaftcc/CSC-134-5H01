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
#include "dnd.h"
#include "story.h"
using namespace std;

// A simplified version of the game to test our fixes
int main(int argc, char* argv[]) {
    srand(time(0));

    cout << "===== DND Game Test =====\n" << endl;

    if (argc < 2) {
        cout << "Usage:" << endl;
        cout << "./test_game login <character_name> <password> - Login with existing character" << endl;
        cout << "./test_game xp <character_name> <amount> - Grant XP to character" << endl;
        return 1;
    }

    string command = argv[1];
    int choice;

    if (command == "login") {
        choice = 1;
    } else if (command == "xp") {
        choice = 3;
    } else {
        cout << "Unknown command: " << command << endl;
        return 1;
    }
    
    switch (choice) {
        case 1: {
            // Login with existing character
            if (argc < 4) {
                cout << "Usage: ./test_game login <character_name> <password>" << endl;
                return 1;
            }

            string name = argv[2];
            string password = argv[3];

            cout << "Logging in as: " << name << endl;
            
            // Try to load the character
            ifstream statsFile("character_stats.txt");
            if (!statsFile) {
                cerr << "Error opening character_stats.txt!" << endl;
                return 1;
            }
            
            bool foundCharacter = false;
            string line;
            
            while (getline(statsFile, line)) {
                stringstream ss(line);
                string storedName, storedClass, encryptedStats;
                
                ss >> storedName >> storedClass >> encryptedStats;
                
                if (storedName == name) {
                    // Check password
                    if (!checkPassword(name, password)) {
                        cout << "Incorrect password!" << endl;
                        return 1;
                    }
                    
                    // We found the character
                    currentPlayer = storedName;
                    currentClass = storedClass;
                    
                    // Decrypt and parse the stats
                    string decryptedStats = decryptStats(encryptedStats);
                    
                    stringstream ssStats(decryptedStats);
                    if (!(ssStats >> strength >> dex >> constit >> intel >> wisdom >> rizz >> level >> experience)) {
                        cerr << "Error parsing character stats!" << endl;
                        statsFile.close();
                        return 1;
                    }
                    
                    // Calculate stat points based on level (one per level above 1)
                    statPoints = level - 1;
                    
                    foundCharacter = true;
                    break;
                }
            }
            
            statsFile.close();
            
            if (!foundCharacter) {
                cout << "Character not found!" << endl;
                return 1;
            }
            
            // Display character info
            cout << "\nCharacter loaded successfully!\n" << endl;
            displayCharacter();
            
            // Test if the user wants to spend stat points
            if (statPoints > 0) {
                cout << "Would you like to spend your stat points? (y/n): ";
                char spendChoice;
                cin >> spendChoice;
                
                if (spendChoice == 'y' || spendChoice == 'Y') {
                    spendStatPoints();
                    displayCharacter();
                }
            }
            
            break;
        }
        case 2: {
            // Create a new character
            characterCreation();
            break;
        }
        case 3: {
            // Grant experience to a character
            if (argc < 4) {
                cout << "Usage: ./test_game xp <character_name> <amount>" << endl;
                return 1;
            }

            string name = argv[2];
            int xpAmount = atoi(argv[3]);
            
            // Try to load the character
            ifstream statsFile("character_stats.txt");
            if (!statsFile) {
                cerr << "Error opening character_stats.txt!" << endl;
                return 1;
            }
            
            bool foundCharacter = false;
            string line;
            
            while (getline(statsFile, line)) {
                stringstream ss(line);
                string storedName, storedClass, encryptedStats;
                
                ss >> storedName >> storedClass >> encryptedStats;
                
                if (storedName == name) {
                    // We found the character
                    currentPlayer = storedName;
                    currentClass = storedClass;
                    
                    // Decrypt and parse the stats
                    string decryptedStats = decryptStats(encryptedStats);
                    
                    stringstream ssStats(decryptedStats);
                    if (!(ssStats >> strength >> dex >> constit >> intel >> wisdom >> rizz >> level >> experience)) {
                        cerr << "Error parsing character stats!" << endl;
                        statsFile.close();
                        return 1;
                    }
                    
                    // Calculate stat points based on level
                    statPoints = level - 1;
                    
                    foundCharacter = true;
                    break;
                }
            }
            
            statsFile.close();
            
            if (!foundCharacter) {
                cout << "Character not found!" << endl;
                return 1;
            }
            
            // Display character before XP
            cout << "\nCharacter before XP gain:" << endl;
            displayCharacter();

            cout << "Granting " << xpAmount << " XP..." << endl;
            
            // Grant XP
            experiencePoints(xpAmount);
            
            // Display character after XP
            cout << "\nCharacter after XP gain:" << endl;
            displayCharacter();
            
            break;
        }
        case 4:
            // Exit
            cout << "Exiting test." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
    
    return 0;
}