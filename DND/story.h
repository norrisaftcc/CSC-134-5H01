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
void main_menu_fake();
void choice_front_door();
void choice_back_door();
void choice_go_home();
void choice_food();
void choice_bed();
void choice_break_in();
void save_progress(int choice);
void displayCharacterAction();

void main_menu() {
  static bool firstLoad = true;  // Tracks whether this is the first time loading progress
  int lastChoice = load_progress(); // Load last position
  string emoji;
  static bool partyMember = false;

  if (currentClass == "Fighter"){
      emoji = "⚔️";
  }
  else if (currentClass == "Magic-User"){
      emoji = "🧙";
  }
  else if (currentClass == "Thief"){
      emoji = "🗡️";
  }
  else if (currentClass == "Cleric"){
      emoji = "💉";
  }
  else if (currentClass == "Elf"){
      emoji = "🏹";
  }
  else if (currentClass == "Dwarf"){
      emoji = "🔨";
  }
  else if (currentClass == "Halfling"){
      emoji = "🔱";
  }

  if (lastChoice != 0 && firstLoad) {
      cout << "Resuming from your last choice: " << lastChoice << endl;
      firstLoad = false;  // Prevent message from appearing again
//      switch (lastChoice) {
//          case 1:
//              choice_front_door();
//              return;
//          case 2:
//              choice_go_home();
//              return;
//      }
  }

  // Normal game start if no progress exists
  cout << "" << endl;
  cout << "Welcome " << currentPlayer << " the " << currentClass << "." << endl;
  cout << "You've awakened as a " << currentClass << "." << endl;
  if (currentClass == "Fighter"){
    cout << "Since you're a fighter it makes you better at using physical abilites and brute force!" << endl;
  }
  else if (currentClass == "Magic-User"){
    cout << "Since you're a magic-user it gives you the immense power of abilites but you're weaker in health and physical combat." << endl;
  }
  else if (currentClass == "Thief"){
      emoji = "Since you're a thief you're good at stealth and are really agile, but you're strength is weaker than most.";
  }
  else if (currentClass == "Cleric"){
      emoji = "Since you're a cleric you are given the ability to heal people, and connect with nature. This comes with weaker health, but you have things to counteract that";
  }
  else if (currentClass == "Elf"){
      emoji = "Since you're an elf you're good with bows and arrows, but you're more frail.";
  }
  else if (currentClass == "Dwarf"){
      emoji = "Since you're a dwarf you're stronger and you have the ability to make armor more powerful!";
  }
  else if (currentClass == "Halfling"){
      emoji = "Since you're a halfling you're a master with the spear.";
  }
  cout << "========================================" << endl;
  cout << emoji << "  : " << currentPlayer << " the " << currentClass << endl;
  if (partyMember){
      cout << "TODO" << endl;
  }
  cout << "1. Try the front door" << endl;
  cout << "2. Sneak around back" << endl;
  cout << "3. Forget it, and go home" << endl;
  cout << "4. Stats" << endl;
  cout << "5. Test" << endl;
  cout << "6. [Quit]" << endl;
  cout << "Choose: ";

  int choice;
  cin >> choice;
  save_progress(choice); // Save progress at this step

  switch (choice) {
      case 1:
      case 2:
      case 3:
      case 5:
          save_progress(choice);
          break;
  }

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
      case 4:
          displayCharacterAction();
          break;
      case 5:
          choice_break_in();
          break;
      default:
          cout << "That's not a valid choice, please try again." << endl;
          cin.ignore();
          main_menu();
          break;
  }
}


void displayCharacterAction(){
  displayCharacter();
  cout << "Any Key: Go back" << endl;
  int choice;
  cin >> choice;
  switch (choice){
    case 1:
      main_menu();
      break;
    default:
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
  srand(time(0));
  int door = rollDice() + rollDice();
  if (door < 5){
    door += 3;
  }
  else if (door > 15){
    door -= 3;
  }
  int youRoll = rollDice() + rollDice();
  int doorRoll = rollDice() + rollDice();
  cout << "You try to break down the door" << endl;
  cout << "Door Strength: " << door << endl;
  if (currentClass == "Fighter"){
    cout << "You Roll " << youRoll << "!" << endl;
    cout << "You gain +3 for the class bonus!" << endl;
    youRoll += 3;
    cout << "You Roll " << youRoll << "!" << endl;
  }
  else{
  cout << "You Roll " << youRoll << "!" << endl;
  }
  cout << "Door Rolls " << doorRoll << "!" << endl;
  if (strength > door){
    doorRoll = doorRoll - (strength - door);
    cout << "Because you're stronger you weaken the doors roll!" << endl;
    if (doorRoll < 0){
      cout << "New Door Roll " << 0 << "!" << endl;
    }
    else {
      cout << "New Door Roll " << doorRoll << "!" << endl;
    }
  }
  else if(door > strength) {
    youRoll = youRoll - (door - strength);
    cout << "Because you're weaker the door weakens your roll!" << endl;
    if (youRoll < 0){
      cout << "Your New Roll " << 0 << "!" << endl;
    }
    else {
      cout << "Your New Roll " << youRoll << "!" << endl;
    }
  }
  if (youRoll > doorRoll || youRoll == doorRoll){
    cout << "You break it down!" << endl;
  }
  else {
    cout << "You don't break down the door" << endl;
    choice_go_home();
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