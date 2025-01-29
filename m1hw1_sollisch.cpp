#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    string movie = "Whiplash";
    int year = 2014;
    double gross = 50.40;
    string quote = "\"There are no two words in the English language more harmful than 'good job'\".";

    cout <<"My favorite move is " << movie << "." << endl;
    cout <<"It came out in " << year << "." << endl;
    cout <<"It grossed $" << gross << " million in the box office." << endl;
    cout <<"A famous quote from " << movie << " is " << quote << endl;
    return 0;
}