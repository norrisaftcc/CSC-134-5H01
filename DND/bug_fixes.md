# DND Game Bug Fixes

This document outlines the bugs identified in the DND game and the fixes applied.

## 1. Level System Bugs

### Issue 1.1: Competing Level Update Functions
The game had two separate functions for updating levels - `updateLevel()` in dnd.h and `experiencePoints()` in story.h, creating conflicts in how levels are calculated.

### Issue 1.2: Experience Points Reset Bug
In `experiencePoints()`, experience points were incorrectly reset after leveling up by subtracting the threshold. This prevented proper progression.

### Issue 1.3: Backwards Level Comparison
In `updateLevel()`, the condition `oldLevel > level` was backwards - it should check if the new level is higher than the old level.

### Issue 1.4: Incomplete File Updates
The `updateLevel()` function reads from the stats file but doesn't write the modified content back properly.

## 2. Character Stats Management Issues

### Issue 2.1: Inconsistent Stats Format
Different functions use different formats for saving character stats, particularly the inclusion of "Level:" in some formats but not others.

### Issue 2.2: Parsing Errors
The `newPlayer()` function fails to handle the potential "Level:" label when parsing stats.

### Issue 2.3: Global Variables
The code uses global variables for character stats, making it harder to maintain and debug.

## 3. File System Issues

### Issue 3.1: Hardcoded Encryption Keys
The encryption keys are hardcoded in the source, creating a security vulnerability.

### Issue 3.2: Inconsistent File Operations
File reading and writing operations have inconsistencies in formatting and error handling.

## Fixes Applied

The following changes have been made to fix these issues:

### Fix 1: Consolidate Level System (story.h)
- Modified `experiencePoints()` function to properly handle level-ups
- Removed experience point subtraction after leveling up
- Now properly awards stat points upon level-up
- Added better notification for level-ups

```cpp
void experiencePoints(int xpGained) {
  cout << "You gain " << xpGained << " XP!" << endl;
  experience += xpGained;

  int oldLevel = level;
  int newLevel = level;
  int newProfBonus = 0;

  // Check for level-up and set new level
  for (int i = 19; i >= 0; --i) {
      if (experience >= levelTable[i].xpThreshold) {
          newLevel = levelTable[i].level;
          newProfBonus = levelTable[i].proficiencyBonus;
          break;
      }
  }

  if (newLevel > oldLevel) {
      level = newLevel;
      // Calculate stat points to add (1 per level gained)
      int statPointsAdded = level - oldLevel;
      statPoints += statPointsAdded;

      cout << "\n🆙 Level Up! You are now Level " << level << "!" << endl;
      cout << "🎁 You received " << statPointsAdded << " stat point(s)!" << endl;
      saveCharacter();
  }

  // Update current XP display
  int nextLevelXP = (level < 20) ? levelTable[level].xpThreshold : levelTable[19].xpThreshold;
  cout << "Current XP: " << experience << " / " << nextLevelXP << " (Level " << level << ")" << endl;

  // IMPORTANT: DO NOT reset experience after leveling up
  // We need to keep the total XP for proper progression through levels
}
```

### Fix 2: Updated `updateLevel()` Function (dnd.h)
- Fixed the backwards level comparison logic (`level > oldLevel` instead of `oldLevel > level`)
- Properly saves the updated character data to file
- Added proper file operation error handling

```cpp
// Notify player about the stat points added
if (statPointsAdded > 0 && level > oldLevel) { // Fixed condition: check if NEW level > OLD level
    cout << "\n🆙 You've leveled up to Level " << level << "!" << endl;
    cout << "🎁 You received " << statPointsAdded << " stat point(s)!" << endl;
}

// Save the updated character stats to file
if (level != oldLevel) {
    // File operations with proper error handling
    // ...
}
```

### Fix 3: Standardized Character Stats Format
- Removed the inconsistent "Level:" string in stats format
- Now using a consistent format across all functions:
  ```
  strength dex constit intel wisdom rizz level experience
  ```
- Updated both `characterCreation()` and `overwriteCharacterData()` functions

### Fix 4: Improved Stats Parsing in `newPlayer()`
- Added error handling when parsing character stats
- Will properly report if there's an issue with stats parsing

```cpp
// Parse the stats with proper error handling
if (!(ssDecrypted >> strength >> dex >> constit >> intel >> wisdom >> rizz >> level >> experience)) {
    cerr << "Error parsing character stats for " << currentPlayer << "!" << endl;
    return -1;
}
```

### Fix 5: Fixed Class Description and Emoji Inconsistencies
- Corrected improperly assigned emoji variables in `main_menu()`
- Now properly separating emoji symbols from class descriptions
- Fixed output formatting to maintain consistent UI

## New Features

### File Saving Toggle

A new feature has been added to control file saving operations. This allows:

1. Disabling file saving for testing purposes
2. Running the game without affecting save files
3. Creating "sandbox" mode where changes aren't saved

Usage:
```cpp
// To disable saving
enableSaving = false;

// To re-enable saving (this is the default)
enableSaving = true;
```

The toggle affects all file operations:
- Character stat saving
- Progress saving
- Character data overwriting

## Test Scaffold

A test scaffold has been created to verify that the fixes work properly. This scaffold tests:

1. The leveling system - Ensures characters level up correctly and gain proper stat points
2. Character creation and loading - Verifies character data is saved and loaded correctly
3. File operations - Tests that character stats are properly persisted after modifications
4. Battle system - Verifies class-specific battle adjustments work correctly
5. Save toggle feature - Tests that the save toggle correctly enables/disables file saving

To compile and run the test scaffold:

```bash
g++ -o test_dnd test_scaffold.cpp -std=c++11
./test_dnd
```

The test scaffold will output detailed information about each test and whether it passes or fails.