#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    const int NUM_STATS = 6;
    const int STR = 0;
    const int DEX = 1;
    const int CON = 2;
    const int INT = 3;
    const int WIS = 4;
    const int CHA = 5;

    int stats[NUM_STATS];
    string stat_names[] = {"STR", "DEX", "CON", "INT", "WIS", "CHA"};
    int current_stat;
    double total_stats = 0;
    double average_stat;

    cout << "Please enter your character stats." << endl;
    for (int i=0; i<NUM_STATS; i++){
        cout << "Stat (" <<stat_names[i] << "): ";
        cin >> current_stat;
        stats[i] = current_stat;
        total_stats += current_stat;
    }
    average_stat = total_stats / NUM_STATS;
    cout << "Total: " << total_stats << " Average: " << average_stat << endl;
    cout << "Character Sheet:" << endl;
    for (int i=0; i<NUM_STATS; i++){
        cout << stat_names[i] << ": " << stats[i] << endl;
    }
}