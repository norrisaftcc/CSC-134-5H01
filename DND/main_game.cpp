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
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

int main() {
    srand(time(0));
    if (newPlayer()) {
        characterCreation();
    } else {
        displayCharacter();
    }

    main_menu();
}
