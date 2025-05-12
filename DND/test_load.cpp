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

// Simple test function to load a character by name
bool loadCharacterByName(const string& name) {
    ifstream statsFile("character_stats.txt");
    if (!statsFile) {
        cerr << "Error opening character_stats.txt!" << endl;
        return false;
    }
    
    bool characterFound = false;
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
            cout << "Decrypted stats: " << decryptedStats << endl;

            stringstream ssStats(decryptedStats);
            if (!(ssStats >> strength >> dex >> constit >> intel >> wisdom >> rizz >> level >> experience)) {
                cerr << "Error parsing character stats!" << endl;
                statsFile.close();
                return false;
            }

            // Calculate stat points based on level (one per level above 1)
            statPoints = level - 1;
            
            characterFound = true;
            break;
        }
    }
    
    statsFile.close();
    
    if (characterFound) {
        // Check if the player has a saved progress
        ifstream progressFile("player_progress.txt");
        int lastChoice = 0;
        
        if (progressFile) {
            string name, encryptedChoice;
            while (progressFile >> name >> encryptedChoice) {
                if (name == currentPlayer) {
                    string decryptedChoice = decryptStats(encryptedChoice);
                    lastChoice = stoi(decryptedChoice);
                    break;
                }
            }
            progressFile.close();
        }
        
        // Display the character information
        cout << "Character loaded successfully:" << endl;
        cout << "------------------------" << endl;
        cout << "Name: " << currentPlayer << endl;
        cout << "Class: " << currentClass << endl;
        cout << "Level: " << level << endl;
        cout << "Experience: " << experience << endl;
        cout << "Stats:" << endl;
        cout << "  Strength: " << strength << endl;
        cout << "  Dexterity: " << dex << endl;
        cout << "  Constitution: " << constit << endl;
        cout << "  Intelligence: " << intel << endl;
        cout << "  Wisdom: " << wisdom << endl;
        cout << "  Charisma: " << rizz << endl;
        cout << "Stat Points: " << statPoints << endl;
        cout << "Last progress choice: " << lastChoice << endl;
        
        return true;
    } else {
        cout << "Character '" << name << "' not found!" << endl;
        return false;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./test_load <character_name>" << endl;
        cout << "Example: ./test_load TestElf" << endl;
        return 1;
    }
    
    string characterName = argv[1];
    cout << "Attempting to load character: " << characterName << endl;
    
    if (loadCharacterByName(characterName)) {
        cout << "Character loaded successfully!" << endl;
    } else {
        cout << "Failed to load character." << endl;
    }
    
    return 0;
}