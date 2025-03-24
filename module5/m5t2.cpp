/*
CSC 134
M5T1
Jack Sollisch
3/24/2025
*/
#include <iostream>
using namespace std;
int num = 1;
int product;
int square();
void printAnswer();

int main(){
    do{
    square();
    printAnswer();
    num++;
    } while(num < 11);
}

int square(){
    product = num * num;
    return product;
}

void printAnswer(){
    cout << num << " squared is " << product << endl;
}