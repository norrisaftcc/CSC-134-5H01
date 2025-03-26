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


void main_menu();
void choice_front_door();
void choice_back_door();
void choice_go_home();
void choice_food();
void choice_bed();

int main() {
  cout << "M5LAB1 - Choose Your Own Adventure" << endl;
  main_menu();
  cout << "Thanks for playing!" << endl;
  return 0;
}

void main_menu() {
  cout << "Main Menu" << endl;
  cout << "You're in front of a spooky old house..." << endl;
  cout << "Do you:" << endl;
  cout << "1. Try the front door" << endl;
  cout << "2. Sneak around back" << endl;
  cout << "3. Forget it, and go home" << endl;
  cout << "4. [Quit]" << endl;
  cout << "Choose: ";
  int choice;
  cin >> choice;
  switch (choice)
  {
  case 1:
    choice_front_door();
    break;
  case 2:
    choice_back_door();
    break;
  case 3:
    choice_go_home();
    break;
  default:
    cout << "That's not a valid choice, please try again." << endl;
    cin.ignore();
    main_menu();
    break;
  }
}

void choice_front_door() {
  cout << "Try the front door." << endl;
  cout << "It's locked. " << endl;
  cout << "Do you:" << endl;
  cout << "1. Check around back" << endl;
  cout << "2. Give up and go home" << endl;
  int choice;
  cout << "Choose: ";
  cin >> choice;
  switch (choice){
    case 1:
      choice_back_door();
      break;
    case 2:
      choice_go_home();
      break;
    default:
      cout << "That's not a valid choice, please try again." << endl;
      cin.ignore();
      choice_front_door();
      break;
  }
}

void choice_back_door() { 
  cout << "You enter the house! Unfortunatley the owners were home..." << endl;
  cout << "You've been arrested for breaking and entering." << endl; 
  cout << "~~~~~ Arrested Ending ~~~~~" << endl;
  cout << "           1/3        " << endl;
}

void choice_go_home() { 
  cout << "You go home." << endl;
  cout << "You're hungry " << endl;
  cout << "Do you:" << endl;
  cout << "1. Go out for food" << endl;
  cout << "2. Go to bed" << endl;
  int choice;
  cout << "Choose: ";
  cin >> choice;
  switch (choice){
    case 1:
      choice_food();
      break;
    case 2:
      choice_bed();
      break;
    default:
      cout << "That's not a valid choice, please try again." << endl;
      cin.ignore();
      choice_front_door();
      break; 
  }
}

void choice_food(){
  cout << "You drive for food..." << endl;
  cout << "Unfortunatley, since you live in a town where entering random houses is normal, someone stole the lugnuts on your tires causing them to fly off while driving" << endl; 
  cout << "~~~~~ Hungry Ending ~~~~~" << endl;
  cout << "          3/3        " << endl;
}

void choice_bed(){
  cout << "You go to bed..." << endl;
  cout << "You live to see the next day!" << endl; 
  cout << "~~~~~ Lazy Ending ~~~~~" << endl;
  cout << "          2/3        " << endl;
}