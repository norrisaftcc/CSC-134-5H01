// CSC 134
// M3T3
// norrisa
// 2/17/2025
// Start with dice rolls
// What dice are you using today?
// norris - 1d20

#include <iostream>
// for random
#include <cmath>    
#include <ctime>
using namespace std;

int main() {
    int sides;
    cout << "How many sides are on the dice: ";
    cin >> sides;
    
     // yours will differ!
    //int seed = 35860;
    int seed = time(0);
    // seed the random number generator
    srand(seed);
    // rand() is a large number, so we take the remainder which is %
    int rolls, average, total = 0, diceRolls;
    cout << "How many rolls do you want: ";
    cin >> rolls;
    cout << " " << endl;
    
    int highestRoll = 0;
    int lowestRoll = sides;
    int i = 1;
    do 
    {
        diceRolls = ( (rand() % sides)+1 );
        seed += rand();
        seed -= rand();
        seed += rand();
        cout << diceRolls << endl;
        i += 1;
        total += diceRolls;
        
            if (highestRoll < diceRolls) {
                highestRoll = diceRolls;
            }
            if (lowestRoll > diceRolls) {
                lowestRoll = diceRolls;
            }
    }while (rolls >= i);

    cout << " " << endl;

    average = total/rolls;
    cout << "You rolled an total of " << total << "." << endl;
    cout << "You rolled an average of " << average << "." << endl;
    cout << "Your highest roll was a " << highestRoll << "." << endl; 
    cout << "Your lowest roll was a " << lowestRoll << "." << endl; 
}