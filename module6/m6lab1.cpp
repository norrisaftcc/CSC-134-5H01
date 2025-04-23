#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <thread>  // For adding delays
#include <chrono>  // For time durations
using namespace std;

// Function to reload the magazine
void reloadMagazine(vector<int>& magazine, const int MAGSIZE) {
    magazine.clear();  // Clear the current magazine

    // Generate new shells (random 0: Black, 1: Red)
    for (int i = 0; i < MAGSIZE; i++) {
        int shell = rand() % 2; // Random 0 (Black) or 1 (Red)
        magazine.push_back(shell);
    }
    
    // Add an EMPTY shell at the end
    magazine.push_back(-1);
}

// Function for the player's turn
void playerTurn(vector<int>& magazine, int& PHEALTH, int& EHEALTH, int& currentShellIndex, const int MAGSIZE) {
    int choice;

    if (currentShellIndex >= magazine.size()) {
        cout << "\nNo shells left. You need to reload.\n";
        reloadMagazine(magazine, MAGSIZE);  // Reload if no shells left
        currentShellIndex = 0;  // Reset the shell index to start from the beginning
    }

    // Count loaded shells and blanks (excluding EMPTY)
    int blackCount = 0;
    int redCount = 0;

    for (size_t i = currentShellIndex; i < magazine.size(); ++i) {
        if (magazine[i] == 0) { // Black shell
            blackCount++;
        } else if (magazine[i] == 1) { // Red shell
            redCount++;
        }
    }

    cout << "\nYour HP: " << PHEALTH << " | Dealer HP: " << EHEALTH << endl;
    cout << "Remaining shells " << MAGSIZE << " — Loaded: " << blackCount << ", Blanks: " << redCount << "\n";
    cout << "Will you shoot yourself or the dealer?\n1: Yourself\n2: Dealer\nChoice: ";
    cin >> choice;

    int shell = magazine[currentShellIndex];

    // Wait before shooting to add intensity
    cout << "\n...The tension rises...\n";
    this_thread::sleep_for(chrono::seconds(1));

    if (shell == -1) {
        cout << "CLICK! EMPTY shell — Time to reload (out of ammo).\n";
        reloadMagazine(magazine, MAGSIZE);  // Reload if an EMPTY shell is encountered
        currentShellIndex = 0;  // Reset shell index
        playerTurn(magazine, PHEALTH, EHEALTH, currentShellIndex, MAGSIZE);
        return;  // Skip the rest of the loop and reload
    }

    if (choice == 1) { // Shoot yourself
        currentShellIndex++;
        if (shell == 0) {
            PHEALTH--;
            cout << "The shell was loaded — you took 1 damage!\n";
        } else {
            cout << "The shell was blank — you're safe... for now.\n";
            playerTurn(magazine, PHEALTH, EHEALTH, currentShellIndex, MAGSIZE);
            return;
        }    
    } else if (choice == 2) { // Shoot dealer
        if (shell == 0) {  // Loaded shell (black)
            EHEALTH--;
            cout << "The shell was loaded — the dealer took 1 damage!\n";
        } else {  // Blank shell (red)
            cout << "The shell was blank — the dealer lives.\n";
        }
        // After shooting the dealer, advance to the next shell and it's his turn
        currentShellIndex++; 
    } else {
        cout << "Invalid choice.\n";
        return;  // Skip to next loop without advancing shell
    }
}

void dealerTurn(vector<int>& magazine, int& PHEALTH, int& EHEALTH, int& currentShellIndex, const int MAGSIZE) {
    if (EHEALTH <= 0) return;

    // Reload if out of shells
    if (currentShellIndex >= magazine.size()) {
        cout << "\nNo shells left. The dealer reloads.\n";
        reloadMagazine(magazine, MAGSIZE);
        currentShellIndex = 0;
        dealerTurn(magazine, PHEALTH, EHEALTH, currentShellIndex, MAGSIZE);
        return;
    }

    cout << "\nIt's the dealer's turn!\n";
    this_thread::sleep_for(chrono::seconds(1));

    // Count future shell types
    int blackCount = 0, redCount = 0;
    for (size_t i = currentShellIndex; i < magazine.size(); ++i) {
        if (magazine[i] == 0) blackCount++;
        else if (magazine[i] == 1) redCount++;
    }

    int dealerChoice;
    if (redCount > blackCount) {
        dealerChoice = (rand() % 4 == 0) ? 2 : 1;  // More blanks: prefer self
    } else if (blackCount > redCount) {
        dealerChoice = (rand() % 4 == 0) ? 1 : 2;  // More loaded: prefer player
    } else {
        dealerChoice = (rand() % 2) + 1;  // Equal: random
    }

    int dealerShell = magazine[currentShellIndex];

    // If EMPTY shell, reload and retry
    if (dealerShell == -1) {
        cout << "CLICK! EMPTY shell — the dealer must reload.\n";
        reloadMagazine(magazine, MAGSIZE);
        currentShellIndex = 0;
        dealerTurn(magazine, PHEALTH, EHEALTH, currentShellIndex, MAGSIZE);  // Retry
        return;
    }


    if (dealerChoice == 1) { // Dealer shoots himself
        currentShellIndex++;
        if (dealerShell == 0) {
            EHEALTH--;
            cout << "The dealer shot himself with a loaded shell! He took 1 damage.\n";
        } else {
            cout << "The dealer shot himself with a blank shell...\n";
            dealerTurn(magazine, PHEALTH, EHEALTH, currentShellIndex, MAGSIZE);
            return;
        }
    } else { // Dealer shoots player
        currentShellIndex++;
        if (dealerShell == 0) {
            PHEALTH--;
            cout << "The dealer shot you with a loaded shell! You took 1 damage.\n";
        } else {
            cout << "The dealer shot you with a blank shell... You're safe.\n";
        }
    }
}


int main() {
    srand(time(0)); // Seed RNG

    const int BLACK = 0;
    const int RED = 1;
    const int EMPTY = -1;
    int PHEALTH = 4;
    int EHEALTH = 4;
    const int MAGSIZE = (rand() % 7) + 2; // At least 2 shells

    string shell_names[] = {"Black", "Red", "Empty"};
    vector<int> magazine;

    // Generate the initial magazine
    reloadMagazine(magazine, MAGSIZE);

    int currentShellIndex = 0;

    cout << "Buckshot Roulette Begins! First to drop to 0 HP loses.\n";

    // Main game loop
    while (PHEALTH > 0 && EHEALTH > 0) {
        // Check if reload is needed before player's turn
        if (currentShellIndex >= magazine.size()) {
            cout << "\nNo shells left. You need to reload before your turn.\n";
            reloadMagazine(magazine, MAGSIZE);  // Reload before the player's turn
            currentShellIndex = 0;  // Reset to the first shell
        }

        // Player's turn
        playerTurn(magazine, PHEALTH, EHEALTH, currentShellIndex, MAGSIZE);

        // Check if either has died after the player's turn
        if (PHEALTH <= 0) {
            cout << "\nYou died. The dealer wins.\n";
            break;
        } else if (EHEALTH <= 0) {
            cout << "\nThe dealer died. You win!\n";
            break;
        }

        // Dealer's turn
        dealerTurn(magazine, PHEALTH, EHEALTH, currentShellIndex, MAGSIZE);

        // Check if either has died after the dealer's turn
        if (PHEALTH <= 0) {
            cout << "\nYou died. The dealer wins.\n";
            break;
        } else if (EHEALTH <= 0) {
            cout << "\nThe dealer died. You win!\n";
            break;
        }
    }

    return 0;
}

