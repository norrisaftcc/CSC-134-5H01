/*
CSC 134
M5T1 -  basic Functions
Jack Sollisch
3/24/2025
*/
#include <iostream>
using namespace std;

void sayHi();
int add(int first, int second);
void printNumber(int num);
int globalX = 690;

int main(){
    int myNum =12;
    cout << "int main(), myNum = " << myNum << endl;
    cout << "Global Variable: globalX = " << globalX << endl;
    sayHi();
    cout << "2 + 2 = ";
    int num = add(2,2);
    printNumber(num);
    return 0;
}
void sayHi(){
    cout << "Hi" << endl;
}
int add(int first, int second){
    int answer = first + second;
    return answer;
}
void printNumber(int num){
    cout << num << endl;
}