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

// Utility to create a sample player for testing
void createSamplePlayer(const string& playerName, const string& playerClass, int startLevel = 1) {
    // Set the global flag to ensure saving
    enableSaving = true;
    
    // Set player info
    currentPlayer = playerName;
    currentClass = playerClass;
    
    // Roll initial stats
    srand(time(0));  // Seed random number generator
    strength = rollStat();
    dex = rollStat();
    constit = rollStat();
    intel = rollStat();
    wisdom = rollStat();
    rizz = rollStat();
    
    // Set level and experience
    level = startLevel;
    
    // Calculate appropriate XP for the level
    // XP thresholds: 0, 300, 900, 2700, 6500, 14000, 23000, etc.
    int xpThresholds[] = {
        0, 300, 900, 2700, 6500, 14000, 23000, 34000, 48000, 64000,
        85000, 100000, 120000, 140000, 165000, 195000, 225000, 265000,
        305000, 355000
    };
    
    // Set XP to match the level
    if (startLevel <= 1) {
        experience = 0;
    } else {
        experience = xpThresholds[startLevel - 1] + 10;  // Just over the threshold
    }
    
    // Set stat points based on level
    statPoints = startLevel - 1;  // One stat point per level (excluding starting level)
    
    // Create a sample password
    string password = "test123";
    string encryptedPassword = encryptPassword(password);
    
    // Store the password in the password file
    ofstream passwordFile("passwords.txt", ios::app);
    if (!passwordFile) {
        cerr << "Error opening password file for writing!" << endl;
        return;
    }
    passwordFile << currentPlayer << " " << encryptedPassword << endl;
    passwordFile.close();
    
    // Save the character stats - directly write to the file
    string statsStr = to_string(strength) + " " + to_string(dex) + " " + to_string(constit) + " " +
                     to_string(intel) + " " + to_string(wisdom) + " " + to_string(rizz) + " " +
                     to_string(level) + " " + to_string(experience);
    string encryptedStats = encryptStats(statsStr);

    // Store the player stats in the character stats file
    ofstream statsFile("character_stats.txt", ios::app);
    if (!statsFile) {
        cerr << "Error opening stats file for writing!" << endl;
        return;
    }
    statsFile << currentPlayer << " " << currentClass << " " << encryptedStats << endl;
    statsFile.close();
    
    // Save initial progress (position 0)
    save_progress(0);
    
    cout << "Created sample player: " << currentPlayer << " the " << currentClass << " (Level " << level << ")" << endl;
    cout << "Stats: STR " << strength << ", DEX " << dex << ", CON " << constit 
         << ", INT " << intel << ", WIS " << wisdom << ", CHA " << rizz << endl;
    cout << "Experience: " << experience << ", Stat Points: " << statPoints << endl;
    cout << "Password: test123" << endl;
}

int main() {
    cout << "===== DND Sample Player Creator =====" << endl;
    
    string playerName, playerClass;
    int startLevel;
    
    cout << "Enter player name: ";
    cin >> playerName;
    
    cout << "Choose a class (Fighter, Magic-User, Thief, Cleric, Elf, Dwarf, Halfling): ";
    cin >> playerClass;
    
    cout << "Enter starting level (1-20): ";
    cin >> startLevel;
    if (startLevel < 1) startLevel = 1;
    if (startLevel > 20) startLevel = 20;
    
    createSamplePlayer(playerName, playerClass, startLevel);
    
    cout << "\nPlayer created successfully! You can now run the main game and login with:\n"
         << "Username: " << playerName << "\n"
         << "Password: test123\n";
    
    return 0;
}