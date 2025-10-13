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
    isNegative = bigNum.isNegative;
    digits = bigNum.digits; 
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