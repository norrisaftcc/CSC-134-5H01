#ifndef STORY_H
#define STORY_H

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
using namespace std;


void main_menu();
void choice_front_door();
void choice_back_door();
void choice_go_home();
void choice_food();
void choice_bed();
void choice_break_in();
void save_progress(int choice);

void main_menu() {
  int lastChoice = load_progress(); // Load last position

  if (lastChoice != 0) {
      cout << "Resuming from your last choice: " << lastChoice << endl;
      switch (lastChoice) {
          case 1:
              choice_front_door();
              return;
          case 2:
              choice_go_home();
              return;
      }
  }

  // Normal game start if no progress exists
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
  save_progress(choice); // Save progress at this step

  switch (choice) {
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
  save_progress(1);
  cout << "Try the front door." << endl;
  cout << "It's locked. " << endl;
  cout << "Do you:" << endl;
  cout << "1. Check around back" << endl;
  cout << "2. Give up and go home" << endl;
  cout << "3. Break in" << endl;
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
    case 3:
      choice_break_in();
      break;
    default:
      cout << "That's not a valid choice, please try again." << endl;
      cin.ignore();
      choice_front_door();
      break;
  }
}

void choice_back_door() { 
  save_progress(0);
  cout << "You enter the house! Unfortunatley the owners were home..." << endl;
  cout << "You've been arrested for breaking and entering." << endl; 
  cout << "~~~~~ Arrested Ending ~~~~~" << endl;
  cout << "           1/3        " << endl;
}

void choice_go_home() {
  save_progress(2); 
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
  save_progress(0);
  cout << "You drive for food..." << endl;
  cout << "Unfortunatley, since you live in a town where entering random houses is normal, someone stole the lugnuts on your tires causing them to fly off while driving" << endl; 
  cout << "~~~~~ Hungry Ending ~~~~~" << endl;
  cout << "          3/3        " << endl;
}

void choice_bed(){
  save_progress(0);
  cout << "You go to bed..." << endl;
  cout << "You live to see the next day!" << endl; 
  cout << "~~~~~ Lazy Ending ~~~~~" << endl;
  cout << "          2/3        " << endl;
}

void choice_break_in(){
  save_progress(0);
  int door = 11;
  cout << "You try to break down the door" << endl;
  if (door < strength){
    cout << "You break it down!" << endl;
  }
  else {
    cout << "You don't break down the door" << endl;
  }
}

void save_progress(int choice) {
  if (currentPlayer.empty()) {
      cerr << "Error: No player name found. Progress not saved!" << endl;
      return;
  }

  map<string, string> progressMap;  // Map will now store encrypted choices

  // Read existing progress data
  ifstream progressFileRead("player_progress.txt");
  if (progressFileRead) {
      string name, encryptedChoice;
      while (progressFileRead >> name >> encryptedChoice) {
          progressMap[name] = encryptedChoice;  // Store existing encrypted progress
      }
      progressFileRead.close();
  }

  // Encrypt current player's progress
  string encryptedChoice = encryptStats(to_string(choice));
  progressMap[currentPlayer] = encryptedChoice;  // Update progress for the current player

  // Write updated progress back to file
  ofstream progressFileWrite("player_progress.txt");
  if (progressFileWrite) {
      for (const auto& entry : progressMap) {
          progressFileWrite << entry.first << " " << entry.second << endl;  // Write encrypted data
      }
      progressFileWrite.close();
  } else {
      cerr << "Error: Unable to save progress!" << endl;
  }
}




#endif // STORY_H