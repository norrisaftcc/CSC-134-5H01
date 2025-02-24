#include <iostream>
using namespace std;

// beginning of the main() method
int main() {
  // declare the variable we need
  int choice, choice2; 
  const int FIGHT = 1, RUN = 2, ITEM = 3;
  const int FISHING = 1, FINGER = 2, EXIT = 3;

  // ask the question
  cout << "You're fighting Sukuna." << endl;
  cout << "1. Fight" << endl;
  cout << "2. Run" << endl;
  cout << "3. Use Item" << endl;
  cout << "Type 1,2, or 3: "; 
  cin >> choice;

  // using if, make a decision based on the user's choice
  if (FIGHT == choice) {
    cout << "You chose to fight" << endl;
    cout << "You got folded, clapped, and utterly destroyed. " << endl;
  }
  else if (RUN == choice) {
    cout << "You chose to run" << endl;
    cout << "You still die due to a World Cutting Slash." << endl;
  }
  else if (ITEM == choice) {
    cout << "You open your inventory" << endl;
    cout << "1. Fishing Rod" << endl;
    cout << "2. Sukuna's Finger" << endl;
    cout << "3. Close Inventory" << endl;
    cout << "Type 1,2, or 3: "; 
    cin >> choice2;

    if (FISHING == choice2) {
      cout << "You chose to show Sukuna a fishing rod. " << endl;
      cout << "He remembers long ago. " << endl;
      cout << "Come on ladies" << endl;
      cout << "Come on ladies (2x)" << endl;
      cout << "One pound fish" << endl;
      
      cout << "[Verse 1]" << endl;
      cout << "Have a, have a look, one pound fish" << endl;
      cout << "Have a, have a look, one pound fish" << endl;
      cout << "Very, very good, one pound fish" << endl;
      cout << "Very, very cheap, one pound fish" << endl;
      cout << "Six for five pound, one pound each" << endl;
      cout << "Six for five pound, one pound each" << endl;
      cout << "Very, very good and very, very cheap" << endl;
      cout << "(One pound, one pound)" << endl;

      cout << "[Hook]" << endl;
      cout << "Come on ladies" << endl;
      cout << "Come on ladies (4x)" << endl;
      cout << "One pound fish" << endl;
      cout << "Come on ladies" << endl;
      cout << "Come on ladies (2x)" << endl;

      cout << "[Verse 2]" << endl;
      cout << "Have a, have a look, one pound fish" << endl;
      cout << "Have a, have a look, one pound fish" << endl;
      cout << "Very, very good, one pound fish" << endl;
      cout << "Very, very cheap, one pound fish" << endl;
      cout << "Six for five pound, one pound each" << endl;
      cout << "Six for five pound, one pound each" << endl;
      cout << "" << endl;
      cout << "" << endl;
      cout << "" << endl;
      cout << "You win!" << endl;
    }
    else if (FINGER == choice2) {
      cout << "You chose to show Sukuna his finger" << endl;
      cout << "He eats it reaching 20, you've doomed the world." << endl;
    }
    else if (EXIT == choice2) {
      cout << "You're fighting Sukuna." << endl;
      cout << "1. Fight" << endl;
      cout << "2. Run" << endl;
      cout << "3. Use Item" << endl;
      cout << "Type 1,2, or 3: "; 
      cin >> choice;

      if (FIGHT == choice) {
        cout << "You chose to fight" << endl;
        cout << "You got folded, clapped, and utterly destroyed. " << endl;
      }
      else if (RUN == choice) {
        cout << "You chose to run" << endl;
        cout << "You still die due to a World Cutting Slash." << endl;
      }
      else if (ITEM == choice) {
        cout << "You open your inventory" << endl;
        cout << "1. Fishing Rod" << endl;
        cout << "2. Sukuna's Finger" << endl;
        cout << "3. Close Inventory" << endl;
        cout << "Type 1,2, or 3: "; 
        cin >> choice2;
      }
    }
  }
  else {
    cout << "I'm sorry, that is not a valid choice." << endl;
  }
  
  // finish up
  cout << "Thanks for playing!" << endl; // this runs no matter what they choose
  return 0; // exit without error
} // end of the main() method
