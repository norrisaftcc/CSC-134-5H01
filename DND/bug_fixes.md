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