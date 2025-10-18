#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "BigNum.h"
using namespace std;

// SAQIB REHMAN (sr10128) L2

BigNum::BigNum() {
    isNegative = false;
    digits.push_back('0'); 
}

BigNum::BigNum(const BigNum& bigNum) {
    this->isNegative = bigNum.isNegative;
    this->digits = bigNum.digits; 
}

BigNum::BigNum(const string& bigStr) {
    clear();
    if (bigStr.empty()) {
        isNegative = false;
        digits.push_back('0');
        return;
    }

    string str = bigStr;
    bool valid = true;
    int start = 0;

    // Handle negative
    if (str[0] == '-') {
        isNegative = true;
        start = 1;
        if (str.size() == 1) valid = false; // Just "-"
    } 
    else if (str[0] == '+') {
        isNegative = false;
        start = 1;
        if (str.size() == 1) valid = false; // Just "+"
    } 
    else {
        isNegative = false;
    }

    // Parse characters and validate
    for (int i = start; i < (int)str.size(); i++) {
        if (!isdigit(str[i])) {
            valid = false;
            break;
        }
        digits.push_back(str[i]);
    }

    // Handle invalid inputs
    if (!valid || digits.empty()) {
        cout << "Invalid number input." << endl;
        isNegative = false;
        digits.clear();
        digits.push_back('0');
        return;
    }

    // Remove leading zeros
    while (digits.size() > 1 && digits[0] == '0')
        digits.erase(digits.begin());

    // If zero, ensure positive
    if (digits.size() == 1 && digits[0] == '0')
        isNegative = false;
}

BigNum::BigNum(const int num) {
    clear();
    if (num == 0) {
        isNegative = false;
        digits.push_back('0');
        return;
    }

    isNegative = (num < 0);
    int n = (num < 0) ? -num : num;
    string s = to_string(n);
    for (char c : s)
        digits.push_back(c);
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
    cin >> inputStr;

    bool valid = true;
    int start = 0;

    if (inputStr.empty()) valid = false;
    else if (inputStr[0] == '-') {
        isNegative = true;
        start = 1;
        if (inputStr.size() == 1) valid = false;
    }
    else if (inputStr[0] == '+') {
        isNegative = false;
        start = 1;
        if (inputStr.size() == 1) valid = false;
    } else {
        isNegative = false;
    }

    for (int i = start; i < (int)inputStr.size(); i++) {
        if (!isdigit(inputStr[i])) {
            valid = false;
            break;
        }
        digits.push_back(inputStr[i]);
    }

    if (!valid || digits.empty()) {
        cout << "Invalid number input." << endl;
        isNegative = false;
        digits.clear();
        digits.push_back('0');
        return;
    }

    while (digits.size() > 1 && digits[0] == '0')
        digits.erase(digits.begin());
    if (digits.size() == 1 && digits[0] == '0')
        isNegative = false;
}

void BigNum::print() {
    while (digits.size() > 1 && digits[0] == '0')
        digits.erase(digits.begin());
    if (digits.size() == 1 && digits[0] == '0')
        isNegative = false;

    if (isNegative)
        cout << "-";

    int len = digits.size();
    int group = len % 3;
    if (group == 0) group = 3;

    for (int i = 0; i < len; i++) {
        cout << digits[i];
        if ((i + 1 - group) % 3 == 0 && i + 1 < len)
            cout << ",";
    }
}

void BigNum::inputFromFile(const string& fileName) {
    clear();
    ifstream inputFile(fileName);
    string line;
    getline(inputFile, line);

    if (line.empty()) {
        digits.push_back('0');
        return;
    }

    bool valid = true;
    int start = 0;

    if (line[0] == '-') {
        isNegative = true;
        start = 1;
        if (line.size() == 1) valid = false;
    } 
    else if (line[0] == '+') {
        isNegative = false;
        start = 1;
        if (line.size() == 1) valid = false;
    } 
    else {
        isNegative = false;
    }

    for (int i = start; i < (int)line.size(); i++) {
        if (!isdigit(line[i])) {
            valid = false;
            break;
        }
        digits.push_back(line[i]);
    }

    if (!valid || digits.empty()) {
        cout << "Invalid number input." << endl;
        isNegative = false;
        digits.clear();
        digits.push_back('0');
        return;
    }

    while (digits.size() > 1 && digits[0] == '0')
        digits.erase(digits.begin());
    if (digits.size() == 1 && digits[0] == '0')
        isNegative = false;
}

void BigNum::printToFile(const string& fileName) {
    ofstream outputFile(fileName);
    if (isNegative)
        outputFile << "-";
    for (int i = 0; i < (int)digits.size(); i++)
        outputFile << digits[i];
    outputFile.close();
}


void BigNum::copy(const BigNum& bigNum) {
    this->isNegative = bigNum.isNegative;
    this->digits = bigNum.digits;
}

void BigNum::operator=(const BigNum& bigNum) {
    this->isNegative = bigNum.isNegative;
    this->digits = bigNum.digits;
}

void BigNum::zerofy() {
    isNegative = false;
    digits.clear();
    digits.push_back('0');
}

// ===== Comparison =====

bool BigNum::equals(const BigNum& bigNum) {
    return isNegative == bigNum.isNegative && digits == bigNum.digits;
}

bool BigNum::notEquals(const BigNum& bigNum) {
    return !equals(bigNum);
}

bool BigNum::lessThan(const BigNum& bigNum) {
    if (isNegative != bigNum.isNegative)
        return isNegative;
    if (digits.size() != bigNum.digits.size())
        return (digits.size() < bigNum.digits.size()) ^ isNegative;
    return (digits < bigNum.digits) ^ isNegative;
}

bool BigNum::greaterThan(const BigNum& bigNum) {
    return !equals(bigNum) && !lessThan(bigNum);
}

// ===== Addition =====

BigNum BigNum::add(const BigNum& bigNum) {
    // Handle cases where one number is negative
    if (isNegative && !bigNum.isNegative) {
        BigNum temp = *this;
        temp.isNegative = false;
        BigNum copy = bigNum;
        return copy.subtract(temp); // (-A) + B = B - A
    }
    if (!isNegative && bigNum.isNegative) {
        BigNum temp = bigNum;
        temp.isNegative = false;
        return this->subtract(temp); // A + (-B) = A - B
    }

    BigNum result;
    result.digits.clear();

    int carry = 0;
    int i = digits.size() - 1;
    int j = bigNum.digits.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int d1 = 0;
        int d2 = 0;

        if (i >= 0)
            d1 = digits[i] - '0';
        if (j >= 0)
            d2 = bigNum.digits[j] - '0';

        int sum = d1 + d2 + carry;
        result.digits.insert(result.digits.begin(), (sum % 10) + '0');
        carry = sum / 10;

        i--;
        j--;
    }

    // Remove leading zeros
    while (result.digits.size() > 1 && result.digits[0] == '0')
        result.digits.erase(result.digits.begin());

    // Zero should never be negative
    if (result.digits.size() == 1 && result.digits[0] == '0')
        result.isNegative = false;
    else
        result.isNegative = isNegative;

    return result;
}

BigNum BigNum::add(const int num) {
    BigNum temp(num);
    return add(temp);
}

void BigNum::compoundAdd(const BigNum& bigNum) {
    *this = add(bigNum);
}

void BigNum::compoundAdd(const int num) {
    *this = add(num);
}

// ===== Subtraction =====

BigNum BigNum::subtract(const BigNum& bigNum) {
    // Case 1: (-A) - (-B)  →  B - A
    if (isNegative && bigNum.isNegative) {
        BigNum a = *this;
        BigNum b = bigNum;
        a.isNegative = false;
        b.isNegative = false;
        BigNum res = b.subtract(a);
        return res;
    }

    // Case 2: (-A) - B  →  -(A + B)
    if (isNegative && !bigNum.isNegative) {
        BigNum temp = *this;
        temp.isNegative = false;
        BigNum res = temp.add(bigNum);
        res.isNegative = true;
        return res;
    }

    // Case 3: A - (-B)  →  A + B
    if (!isNegative && bigNum.isNegative) {
        BigNum temp = bigNum;
        temp.isNegative = false;
        return this->add(temp);
    }

    // Case 4: A - B (both positive)
    bool negativeResult = false;
    BigNum a = *this;
    BigNum b = bigNum;

    if (a.lessThan(b)) {
        swap(a, b);
        negativeResult = true;
    }

    BigNum result;
    result.digits.clear();

    int borrow = 0;
    int i = a.digits.size() - 1;
    int j = b.digits.size() - 1;

    while (i >= 0) {
        int d1 = a.digits[i] - '0' - borrow;
        int d2 = 0;
        if (j >= 0)
            d2 = b.digits[j] - '0';

        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        int diff = d1 - d2;
        result.digits.insert(result.digits.begin(), diff + '0');

        i--;
        j--;
    }

    // Remove leading zeros
    while (result.digits.size() > 1 && result.digits[0] == '0')
        result.digits.erase(result.digits.begin());

    // Handle sign
    if (result.digits.size() == 1 && result.digits[0] == '0')
        result.isNegative = false;
    else
        result.isNegative = negativeResult;

    return result;
}

BigNum BigNum::subtract(const int num) {
    BigNum temp(num);
    return subtract(temp);
}

void BigNum::compoundSubtract(const BigNum& bigNum) {
    *this = subtract(bigNum);
}

void BigNum::compoundSubtract(const int num) {
    *this = subtract(num);
}

// ===== Increment / Decrement =====

void BigNum::increment() {
    *this = add(1);
}

void BigNum::decrement() {
    *this = subtract(1);
}

// ===== Multiplication =====

BigNum BigNum::multiply(const BigNum& bigNum) {
    BigNum result("0");
    int n = digits.size();
    int m = bigNum.digits.size();

    for (int i = m - 1, pos = 0; i >= 0; i--, pos++) {
        int carry = 0;
        string temp;
        for (int j = n - 1; j >= 0; j--) {
            int prod = (digits[j] - '0') * (bigNum.digits[i] - '0') + carry;
            temp.insert(temp.begin(), (prod % 10) + '0');
            carry = prod / 10;
        }
        if (carry) temp.insert(temp.begin(), carry + '0');
        for (int k = 0; k < pos; k++) temp.push_back('0');
        result = result.add(BigNum(temp));
    }

    while (result.digits.size() > 1 && result.digits[0] == '0')
        result.digits.erase(result.digits.begin());
    if (result.digits.size() == 1 && result.digits[0] == '0')
        result.isNegative = false;
    else
        result.isNegative = (isNegative != bigNum.isNegative);

    return result;
}

// ===== Division =====

BigNum BigNum::div(const BigNum& divisor) {
    BigNum copyDivisor = divisor;

    if (copyDivisor.equals(BigNum("0"))) {
        cout << "Error: Division by zero!" << endl;
        BigNum zero("0");
        return zero;
    }

    BigNum dividend = *this;
    dividend.isNegative = false;
    BigNum divisorAbs = copyDivisor;
    divisorAbs.isNegative = false;

    BigNum quotient("0");
    BigNum current("0");

    for (char d : dividend.digits) {
        current.digits.push_back(d);
        while (current.digits.size() > 1 && current.digits[0] == '0')
            current.digits.erase(current.digits.begin());

        int count = 0;
        while (!current.lessThan(divisorAbs)) {
            current = current.subtract(divisorAbs);
            count++;
        }

        quotient.digits.push_back(count + '0');
    }

    while (quotient.digits.size() > 1 && quotient.digits[0] == '0')
        quotient.digits.erase(quotient.digits.begin());

    if (quotient.digits.size() == 1 && quotient.digits[0] == '0')
        quotient.isNegative = false;
    else
        quotient.isNegative = (isNegative != divisor.isNegative);

    return quotient;
}

BigNum BigNum::mod(const BigNum& bigNum) {
    BigNum zero("0");
    BigNum temp;
    temp.copy(bigNum);
    if (temp.equals(zero)) {
        cout << "Error: Modulo by zero!" << endl;
        return zero;
    }
    BigNum quotient = this->div(bigNum);
    BigNum product = quotient.multiply(bigNum);
    BigNum remainder = this->subtract(product);
    return remainder;
}
