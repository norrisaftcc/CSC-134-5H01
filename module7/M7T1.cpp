#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

// CSC 134
// M7T1 - Restaurant Rating
// norrisa
// 4/29/24
// Use Restaurant class to store user ratings

// Next time we'll put the class in a separate file
class Restaurant {
  private:
    string name;    // the name
    double rating;  // 0 to 5 stars

  public:
    // constructor
    Restaurant(string n, double r) {
        name = n;
        rating = r;
    }
    // getters and setters
    void setName(string n) {
        name = n; 
    }
    void setRating(double r) {
        rating = r;
    }
    string getName() const {
        return name;
    }
    double getRating() const {
        return rating;
    }
    // print a formatted entry
    void printInfo() {
        cout << "Name: " << name << " ";
        int i = 0;
        int stars = static_cast<int>(rating);

        double fractionalPart = fmod(rating, 1.0);

        for (int i = 0; i < 10; ++i) {
            if (i < stars) {
                cout << "🌕";
            } else if (i == stars && fractionalPart == 0.5) {
                cout << "🌗";
            } else {
                cout << "🌑";
            }
        }
        cout << "\n";
    }
};

int main() {
    cout << "M7T1 - Restaurant Reviews" << endl;
    int seed = time(0);
    srand(seed);
    int steps = 21;
    int index = rand() % steps;
    int index2 = rand() % steps;
    double roll = index * 0.5;
    double roll2 = index2 * 0.5;
    string restName;
    
    cout << "Pick a resturant and we'll review it!" << endl;
    cout << "Choose a resturaunt: ";
    cin >> restName;
    Restaurant lunch_place = Restaurant(restName, roll);

    cout << "Pick another resturant and we'll review it!" << endl;
    cout << "Choose another resturaunt: ";
    cin >> restName;
    Restaurant breakfast_place = Restaurant(restName, roll2);

    
    
    cout << "Review info" << endl;
    cout << "Lunch:" << endl;
    breakfast_place.printInfo();
    cout << "Breakfast:" << endl;
    lunch_place.printInfo();

    return 0;

}