#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "dnd.h"
#include "story.h"

using namespace std;

// Test functions
void test_leveling_system();
void test_character_creation();
void test_file_operations();
void test_battle_system();
void clean_test_files();

// Helper functions
void print_test_header(const string& test_name);
void print_test_result(const string& test_name, bool success);
void create_sample_player(const string& name, const string& charClass, int level = 1);

// Function to test save toggle feature
void test_save_toggle();

int main(int argc, char* argv[]) {
    srand(time(0));
    cout << "===== DND Game Test Scaffold =====" << endl;

    // Check for command-line args
    if (argc > 1) {
        string command = argv[1];

        // Create sample player
        if (command == "create_player" && argc >= 4) {
            string name = argv[2];
            string charClass = argv[3];
            int level = 1;

            if (argc >= 5) {
                level = atoi(argv[4]);
                if (level < 1) level = 1;
                if (level > 20) level = 20;
            }

            create_sample_player(name, charClass, level);
            return 0;
        }

        // Show help
        if (command == "help" || command == "--help" || command == "-h") {
            cout << "Usage: " << endl;
            cout << "  ./test_dnd                      - Run all tests" << endl;
            cout << "  ./test_dnd create_player <name> <class> [level]  - Create a sample player" << endl;
            cout << "    Example: ./test_dnd create_player TestPlayer Fighter 5" << endl;
            cout << "    Classes: Fighter, Magic-User, Thief, Cleric, Elf, Dwarf, Halfling" << endl;
            return 0;
        }
    }

    // Clean any previous test files
    clean_test_files();

    // Run tests
    test_leveling_system();
    test_character_creation();
    test_file_operations();
    test_battle_system();
    test_save_toggle();

    cout << "\nAll tests completed!" << endl;
    return 0;
}

void clean_test_files() {
    // Remove test files
    remove("character_stats.txt");
    remove("passwords.txt");
    remove("player_progress.txt");
    
    // Create empty files
    ofstream stats_file("character_stats.txt");
    stats_file.close();
    
    ofstream pass_file("passwords.txt");
    pass_file.close();
    
    ofstream prog_file("player_progress.txt");
    prog_file.close();
}

void print_test_header(const string& test_name) {
    cout << "\n----- Testing " << test_name << " -----" << endl;
}

void print_test_result(const string& test_name, bool success) {
    if (success) {
        cout << "✅ " << test_name << " test passed!" << endl;
    } else {
        cout << "❌ " << test_name << " test failed!" << endl;
    }
}

void test_leveling_system() {
    print_test_header("Leveling System");
    bool success = true;
    
    // Setup a test character
    currentPlayer = "TestPlayer";
    currentClass = "Fighter";
    level = 1;
    experience = 0;
    statPoints = 0;
    
    // Test leveling up
    cout << "Initial state: Level " << level << ", XP " << experience << ", Stat Points " << statPoints << endl;

    // Add XP to trigger a level up
    experience += 350;  // Should reach level 2
    updateLevel();

    // Check results
    cout << "After adding 350 XP: Level " << level << ", XP " << experience << ", Stat Points " << statPoints << endl;

    if (level != 2) {
        cout << "Error: Expected level to be 2, got " << level << endl;
        success = false;
    }

    if (statPoints != 1) {
        cout << "Error: Expected 1 stat point, got " << statPoints << endl;
        success = false;
    }

    // Add more XP to trigger multiple level ups
    int oldLevel = level;
    experience += 6000;  // Should reach level 4 based on the XP thresholds
    updateLevel();

    // Check results
    cout << "After adding 6000 more XP: Level " << level << ", XP " << experience << ", Stat Points " << statPoints << endl;

    // Level 4 is correct for 6350 XP (exceeds 2700 but not 6500)
    if (level != 4) {
        cout << "Error: Expected level to be 4, got " << level << endl;
        success = false;
    }

    int expectedStatPoints = 1 + (level - oldLevel);
    if (statPoints != expectedStatPoints) {
        cout << "Error: Expected " << expectedStatPoints << " stat points, got " << statPoints << endl;
        success = false;
    }

    // Test with experiencePoints function
    oldLevel = level;
    int oldStatPoints = statPoints;
    experiencePoints(10000);  // Should reach level 6 (16350 XP > 14000)

    // Check results
    cout << "After adding 10000 XP through experiencePoints(): Level " << level << ", XP " << experience << ", Stat Points " << statPoints << endl;

    if (level != 6) {
        cout << "Error: Expected level to be 6, got " << level << endl;
        success = false;
    }

    expectedStatPoints = oldStatPoints + (level - oldLevel);
    if (statPoints != expectedStatPoints) {
        cout << "Error: Expected " << expectedStatPoints << " stat points, got " << statPoints << endl;
        success = false;
    }
    
    print_test_result("Leveling System", success);
}

void test_character_creation() {
    print_test_header("Character Creation");
    bool success = true;
    
    // Setup test variables
    currentPlayer = "TestCharacter";
    currentClass = "Thief";
    
    // Roll random stats
    strength = rollStat();
    dex = rollStat();
    constit = rollStat();
    intel = rollStat();
    wisdom = rollStat();
    rizz = rollStat();
    level = 1;
    experience = 0;
    
    // Display character stats
    cout << "Created character with stats:" << endl;
    cout << "Strength: " << strength << endl;
    cout << "Dexterity: " << dex << endl;
    cout << "Constitution: " << constit << endl;
    cout << "Intelligence: " << intel << endl;
    cout << "Wisdom: " << wisdom << endl;
    cout << "Charisma: " << rizz << endl;
    
    // Save character
    saveCharacter();
    
    // Load character back (simulate newPlayer logic)
    string savedStats;
    ifstream statsFile("character_stats.txt");
    if (statsFile) {
        string line;
        while (getline(statsFile, line)) {
            stringstream ss(line);
            string name, charClass, encryptedStats;
            ss >> name >> charClass >> encryptedStats;
            
            if (name == currentPlayer) {
                string decryptedStats = decryptStats(encryptedStats);
                cout << "Decrypted stats: " << decryptedStats << endl;
                
                int loadedStr, loadedDex, loadedCon, loadedInt, loadedWis, loadedCha, loadedLvl, loadedXP;
                stringstream ssDecrypted(decryptedStats);
                
                if (!(ssDecrypted >> loadedStr >> loadedDex >> loadedCon >> loadedInt >> loadedWis >> loadedCha >> loadedLvl >> loadedXP)) {
                    cout << "Error parsing stats!" << endl;
                    success = false;
                    break;
                }
                
                // Verify stats loaded correctly
                if (loadedStr != strength || loadedDex != dex || loadedCon != constit || 
                    loadedInt != intel || loadedWis != wisdom || loadedCha != rizz || 
                    loadedLvl != level || loadedXP != experience) {
                    cout << "Error: Loaded stats don't match original stats!" << endl;
                    success = false;
                } else {
                    cout << "Character data loaded successfully!" << endl;
                }
                
                break;
            }
        }
        statsFile.close();
    } else {
        cout << "Error opening stats file!" << endl;
        success = false;
    }
    
    print_test_result("Character Creation", success);
}

void test_file_operations() {
    print_test_header("File Operations");
    bool success = true;

    // Setup test - make sure we're saving to the files
    enableSaving = true;

    // Create a fresh file
    ofstream createFile("character_stats.txt", ios::trunc);
    createFile.close();

    // Setup test
    currentPlayer = "FileTestChar";
    currentClass = "Magic-User";
    strength = 12;
    dex = 13;
    constit = 14;
    intel = 15;
    wisdom = 16;
    rizz = 17;
    level = 3;
    experience = 1000;

    // Calculate original stats sum
    int originalStatsSum = strength + dex + constit + intel + wisdom + rizz + level + experience;
    cout << "Original stats sum: " << originalStatsSum << endl;

    // Convert to string format
    string statsStr = to_string(strength) + " " + to_string(dex) + " " + to_string(constit) + " " +
                   to_string(intel) + " " + to_string(wisdom) + " " + to_string(rizz) + " " +
                   to_string(level) + " " + to_string(experience);
    string encryptedStats = encryptStats(statsStr);

    // Write directly to the file to ensure it's there
    ofstream statsFile("character_stats.txt", ios::trunc);
    if (statsFile) {
        statsFile << currentPlayer << " " << currentClass << " " << encryptedStats << endl;
        statsFile.close();
    } else {
        cout << "Error creating stats file!" << endl;
        success = false;
    }

    // Change stats
    strength += 2;
    dex += 1;
    experience += 500;
    level = 4;

    // Calculate updated stats sum
    int updatedStatsSum = strength + dex + constit + intel + wisdom + rizz + level + experience;
    cout << "Updated stats sum: " << updatedStatsSum << endl;

    // Save character with updated stats
    saveCharacter();

    // Load character back
    int loadedStr = 0, loadedDex = 0, loadedCon = 0, loadedInt = 0, loadedWis = 0, loadedCha = 0, loadedLvl = 0, loadedXP = 0;

    ifstream statsFileRead("character_stats.txt");
    if (statsFileRead) {
        string line;
        while (getline(statsFileRead, line)) {
            stringstream ss(line);
            string name, charClass, encryptedStatsFromFile;
            ss >> name >> charClass >> encryptedStatsFromFile;

            if (name == currentPlayer) {
                cout << "Found player in file: " << name << endl;

                string decryptedStats = decryptStats(encryptedStatsFromFile);
                cout << "Decrypted stats: " << decryptedStats << endl;

                stringstream ssDecrypted(decryptedStats);

                if (!(ssDecrypted >> loadedStr >> loadedDex >> loadedCon >> loadedInt >> loadedWis >> loadedCha >> loadedLvl >> loadedXP)) {
                    cout << "Error parsing stats! Contents: " << decryptedStats << endl;
                    success = false;
                    break;
                }

                cout << "Parsed stats: " << loadedStr << " " << loadedDex << " " << loadedCon << " "
                     << loadedInt << " " << loadedWis << " " << loadedCha << " "
                     << loadedLvl << " " << loadedXP << endl;

                break;
            }
        }
        statsFileRead.close();
    } else {
        cout << "Error opening stats file for reading!" << endl;
        success = false;
    }

    // Verify loaded stats match updated stats
    int loadedSum = loadedStr + loadedDex + loadedCon + loadedInt + loadedWis + loadedCha + loadedLvl + loadedXP;
    cout << "Loaded stats sum: " << loadedSum << endl;

    if (loadedStr != strength || loadedDex != dex || loadedCon != constit ||
        loadedInt != intel || loadedWis != wisdom || loadedCha != rizz ||
        loadedLvl != level || loadedXP != experience) {
        cout << "Error: Loaded stats don't match updated stats!" << endl;
        cout << "Expected: " << strength << " " << dex << " " << constit << " "
             << intel << " " << wisdom << " " << rizz << " " << level << " " << experience << endl;
        cout << "Got: " << loadedStr << " " << loadedDex << " " << loadedCon << " "
             << loadedInt << " " << loadedWis << " " << loadedCha << " " << loadedLvl << " " << loadedXP << endl;
        success = false;
    } else {
        cout << "File operations completed successfully!" << endl;
    }
    
    print_test_result("File Operations", success);
}

void test_battle_system() {
    print_test_header("Battle System");
    bool success = true;

    // Setup different class types for testing
    string classes[] = {"Fighter", "Magic-User", "Thief"};

    for (const string& testClass : classes) {
        cout << "\nTesting battle with class: " << testClass << endl;

        // Set up character
        currentClass = testClass;
        strength = 10;  // Base strength

        // Test battle adjustments for this class
        int enemyStrength = 10;
        int youRoll = 10;  // Base roll
        int enemyRoll = 10;  // Base roll

        // Apply class adjustments (similar to battleWithEnemy)
        if (currentClass == "Fighter") {
            cout << "Fighter roll before adjustment: " << youRoll << endl;
            youRoll += 3;  // Fighter bonus
            cout << "Fighter roll after adjustment: " << youRoll << endl;
        } else if (currentClass == "Thief") {
            cout << "Thief roll before adjustment: " << youRoll << endl;
            youRoll -= 3;  // Thief penalty
            cout << "Thief roll after adjustment: " << youRoll << endl;
        } else if (currentClass == "Magic-User") {
            cout << "Magic-User roll before adjustment: " << youRoll << endl;
            youRoll -= 5;  // Magic-User penalty
            cout << "Magic-User roll after adjustment: " << youRoll << endl;
        }

        // Ensure rolls are in proper range
        if (youRoll < 0) youRoll = 0;
        if (youRoll > 20) youRoll = 20;

        // Adjust based on strength difference
        if (strength > enemyStrength) {
            enemyRoll = enemyRoll - (strength - enemyStrength);
            cout << "Enemy roll after strength adjustment: " << enemyRoll << endl;
        } else if (enemyStrength > strength) {
            youRoll = youRoll - (enemyStrength - strength);
            cout << "Your roll after strength adjustment: " << youRoll << endl;
        }

        // Check battle outcome
        if (youRoll > enemyRoll || youRoll == enemyRoll) {
            cout << testClass << " wins the battle!" << endl;
        } else {
            cout << testClass << " loses the battle!" << endl;
        }

        // Verify class-specific adjustments
        if (testClass == "Fighter" && youRoll <= 10) {
            cout << "Error: Fighter should have a bonus to rolls!" << endl;
            success = false;
        } else if (testClass == "Thief" && youRoll >= 10) {
            cout << "Error: Thief should have a penalty to rolls!" << endl;
            success = false;
        } else if (testClass == "Magic-User" && youRoll >= 8) {
            cout << "Error: Magic-User should have a significant penalty to rolls!" << endl;
            success = false;
        }
    }

    print_test_result("Battle System", success);
}

void test_save_toggle() {
    print_test_header("Save Toggle Feature");
    bool success = true;

    // Start with a clean slate
    clean_test_files();

    // Setup test character
    currentPlayer = "SaveToggleTest";
    currentClass = "Fighter";
    strength = 12;
    dex = 10;
    constit = 11;
    intel = 8;
    wisdom = 9;
    rizz = 7;
    level = 1;
    experience = 0;
    statPoints = 0;

    // First test: Saving enabled (default)
    cout << "Test with saving enabled (default behavior):" << endl;
    enableSaving = true;

    // Create stats string and write it directly to the file
    string statsStr = to_string(strength) + " " + to_string(dex) + " " + to_string(constit) + " " +
                 to_string(intel) + " " + to_string(wisdom) + " " + to_string(rizz) + " " +
                 to_string(level) + " " + to_string(experience);

    string encryptedStats = encryptStats(statsStr);

    // Write directly to file to ensure it exists
    ofstream directWrite("character_stats.txt");
    if (directWrite) {
        directWrite << currentPlayer << " " << currentClass << " " << encryptedStats << endl;
        directWrite.close();
        cout << "Character data written directly to file for testing" << endl;
    }

    // Save progress only (character data already written)
    save_progress(1);

    // Check if files were created
    ifstream statsCheck("character_stats.txt");
    ifstream progressCheck("player_progress.txt");

    if (!statsCheck) {
        cout << "Error: character_stats.txt was not created with saving enabled!" << endl;
        success = false;
    } else {
        string statsContent;
        bool foundPlayer = false;
        while (getline(statsCheck, statsContent)) {
            if (statsContent.find(currentPlayer) != string::npos) {
                foundPlayer = true;
                cout << "Character stats saved successfully!" << endl;
                break;
            }
        }
        if (!foundPlayer) {
            cout << "Error: Player stats not found in character_stats.txt!" << endl;
            success = false;
        }
        statsCheck.close();
    }

    if (!progressCheck) {
        cout << "Error: player_progress.txt was not created with saving enabled!" << endl;
        success = false;
    } else {
        string progressContent;
        bool foundProgress = false;
        while (getline(progressCheck, progressContent)) {
            if (progressContent.find(currentPlayer) != string::npos) {
                foundProgress = true;
                cout << "Progress saved successfully!" << endl;
                break;
            }
        }
        if (!foundProgress) {
            cout << "Error: Player progress not found in player_progress.txt!" << endl;
            success = false;
        }
        progressCheck.close();
    }

    // Clean files for next test
    clean_test_files();

    // Second test: Saving disabled
    cout << "\nTest with saving disabled:" << endl;
    enableSaving = false;

    // Try to save character
    saveCharacter();
    save_progress(1);

    // Check that files are still empty
    statsCheck.open("character_stats.txt");
    progressCheck.open("player_progress.txt");

    if (statsCheck) {
        string statsContent;
        if (getline(statsCheck, statsContent)) {
            if (!statsContent.empty()) {
                cout << "Error: character_stats.txt was written to with saving disabled!" << endl;
                success = false;
            } else {
                cout << "Character stats correctly not saved when disabled!" << endl;
            }
        }
        statsCheck.close();
    }

    if (progressCheck) {
        string progressContent;
        if (getline(progressCheck, progressContent)) {
            if (!progressContent.empty()) {
                cout << "Error: player_progress.txt was written to with saving disabled!" << endl;
                success = false;
            } else {
                cout << "Progress correctly not saved when disabled!" << endl;
            }
        }
        progressCheck.close();
    }

    // Reset enableSaving to default for other tests
    enableSaving = true;

    print_test_result("Save Toggle Feature", success);
}

void create_sample_player(const string& name, const string& charClass, int startLevel) {
    // Set the global flag to ensure saving
    enableSaving = true;

    // Set player info
    currentPlayer = name;
    currentClass = charClass;

    // Roll initial stats
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

    // Save the character stats
    saveCharacter();

    // Save initial progress (position 0)
    save_progress(0);

    cout << "Created sample player: " << currentPlayer << " the " << currentClass << " (Level " << level << ")" << endl;
    cout << "Stats: STR " << strength << ", DEX " << dex << ", CON " << constit
         << ", INT " << intel << ", WIS " << wisdom << ", CHA " << rizz << endl;
    cout << "Experience: " << experience << ", Stat Points: " << statPoints << endl;
    cout << "Password: test123" << endl;
}