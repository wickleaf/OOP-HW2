#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "BigNum.h"
using namespace std;

BigNum::BigNum() {
    isNegative = false;
    digits.push_back(0); 
}
BigNum::BigNum(const BigNum& bigNum) {
    this -> isNegative = bigNum.isNegative;
    this -> digits = bigNum.digits; 
}
BigNum::BigNum(const std::string& bigStr){
    int x = bigStr.length();
    if (bigStr[0] == '-') {
        isNegative = true;
    } else {
        isNegative = false;
    }
    for (int i=1; i<x; i++) {
        if (isdigit(bigStr[i])) {
            digits.push_back(bigStr[i]);
        }
    }
}
BigNum::BigNum(const int num) {
    if (num < 0) {
        isNegative = true;
    } else {
        isNegative = false;
    }
    int n = num;
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    if (digits.empty()) {
        digits.push_back(0); 
    }
}
void BigNum::clear() {
    isNegative = false;
    digits.clear(); 
}

BigNum::~BigNum() {
    clear();
}

void BigNum::input() {
    clear();
    string inputStr;
    while (true) {
        cin >> inputStr;
        if(cin.fail()) {
            cout << "Wrong fucking datatype retard." << endl;
            cin.clear();
    }
        else break;
    }
    

    if (inputStr[0] == '-') {
        isNegative = true;
    } else {
        isNegative = false;
    }
    for (char ch : inputStr) {
        if (isdigit(ch)) {
            digits.push_back(ch); 
        }
        else{
            cout << "Invalid number"<<endl;
            return;
        }
    }
    if (digits.empty()) {
        digits.push_back(0); 
    }
}

void BigNum::print(){
    int count = 0;
    string outputStr ="";
    for(int i=digits.size(); i<0; i++){
        if (count%3==0){
            outputStr= ","+outputStr;
            outputStr= digits[i]+outputStr;
            count++;
        }
        else{
            outputStr= digits[i]+outputStr;
        }
    }
}

void BigNum::inputFromFile(const string& fileName){
    ifstream inputFile(fileName);
    string line;
    getline(inputFile, line);

    if (line[0] == '-') {
        isNegative = true;
    } else {
        isNegative = false;
    }
    for (char ch : line) {
        if (isdigit(ch)) {
            digits.push_back(ch); 
        }
        else{
            cout << "Invalid number"<<endl;
            return;
        }
    }
    if (digits.empty()) {
        digits.push_back(0); 
    }

}
void BigNum::printToFile(const string& fileName){
    ofstream outputFile(fileName);
    if (isNegative) {
        outputFile << "-";
    }
    for (int i = digits.size() - 1; i >= 0; i--) {
        outputFile << static_cast<char>(digits[i]);
    }
    outputFile.close();
}

void BigNum::copy(const BigNum& bigNum){
    this -> isNegative = bigNum.isNegative;
    this -> digits = bigNum.digits; 
}
void BigNum::operator=(const BigNum& bigNum){
    this -> isNegative = bigNum.isNegative;
    this -> digits = bigNum.digits; 
}
void BigNum::zerofy(){
    isNegative = false;
    digits.clear();
    digits.push_back(0); 
}   

BigNum BigNum::add(const BigNum& bigNum){
    BigNum result;