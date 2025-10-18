#include "BigNum.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>
using namespace std;

BigNum::BigNum() {
    isNegative = false;
    digits.push_back(0);
}

BigNum::BigNum(const string& numStr) {
    isNegative = false;
    digits.clear();

    if (numStr.empty()) {
        digits.push_back(0);
        return;
    }

    string str = numStr;

    // Check for sign
    if (str[0] == '-') {
        isNegative = true;
        str = str.substr(1);
    }

    // Remove commas
    str.erase(remove(str.begin(), str.end(), ','), str.end());

    // Check validity — only digits allowed
    if (!all_of(str.begin(), str.end(), ::isdigit)) {
        cout << "Invalid numeric input: " << numStr << endl;
        isNegative = false;
        digits = {0};
        return;
    }

    // Remove leading zeros
    while (str.size() > 1 && str[0] == '0')
        str.erase(0, 1);

    if (str == "0")
        isNegative = false;

    for (int i = str.size() - 1; i >= 0; i--)
        digits.push_back(str[i] - '0');
}

string BigNum::toString() const {
    string str;
    for (int i = digits.size() - 1; i >= 0; i--)
        str += to_string(digits[i]);

    // Remove leading zeros
    while (str.size() > 1 && str[0] == '0')
        str.erase(0, 1);

    if (str == "0")
        return "0";

    if (isNegative)
        str = "-" + str;

    // Add commas
    for (int i = str.size() - 3; i > 0 && str[i - 1] != '-'; i -= 3)
        str.insert(i, ",");

    return str;
}

void BigNum::printToFile(const string& fileName) {
    ofstream outputFile(fileName);
    string output = toString();
    outputFile << output;
    outputFile.close();
}

bool BigNum::equals(const BigNum& bigNum) {
    return (isNegative == bigNum.isNegative && digits == bigNum.digits);
}

bool BigNum::notEquals(const BigNum& bigNum) {
    return !equals(bigNum);
}

bool BigNum::lessThan(const BigNum& bigNum) {
    if (isNegative != bigNum.isNegative)
        return isNegative;

    if (digits.size() != bigNum.digits.size())
        return isNegative ? digits.size() > bigNum.digits.size() : digits.size() < bigNum.digits.size();

    for (int i = digits.size() - 1; i >= 0; i--) {
        if (digits[i] != bigNum.digits[i])
            return isNegative ? digits[i] > bigNum.digits[i] : digits[i] < bigNum.digits[i];
    }
    return false;
}

bool BigNum::greaterThan(const BigNum& bigNum) {
    return !equals(bigNum) && !lessThan(bigNum);
}

BigNum BigNum::add(const BigNum& bigNum) {
    BigNum result;
    result.digits.clear();

    if (isNegative == bigNum.isNegative) {
        int carry = 0;
        int maxSize = max(digits.size(), bigNum.digits.size());
        for (int i = 0; i < maxSize; i++) {
            int d1 = (i < digits.size()) ? digits[i] : 0;
            int d2 = (i < bigNum.digits.size()) ? bigNum.digits[i] : 0;
            int sum = d1 + d2 + carry;
            carry = sum / 10;
            result.digits.push_back(sum % 10);
        }
        if (carry)
            result.digits.push_back(carry);
        result.isNegative = isNegative;
    } else {
        BigNum a = *this, b = bigNum;
        a.isNegative = false;
        b.isNegative = false;
        if (a.lessThan(b))
            result = b.subtract(a);
        else
            result = a.subtract(b);
        result.isNegative = (this->isNegative && !bigNum.isNegative && !a.equals(b)) ? true : false;
    }

    // Trim leading zeros
    while (result.digits.size() > 1 && result.digits.back() == 0)
        result.digits.pop_back();

    return result;
}

BigNum BigNum::subtract(const BigNum& bigNum) {
    BigNum result;
    result.digits.clear();

    if (isNegative != bigNum.isNegative) {
        BigNum b = bigNum;
        b.isNegative = !b.isNegative;
        return add(b);
    }

    if (absLessThan(bigNum)) {
        result = bigNum.subtract(*this);
        result.isNegative = !isNegative;
        return result;
    }

    int borrow = 0;
    for (size_t i = 0; i < digits.size(); i++) {
        int d1 = digits[i];
        int d2 = (i < bigNum.digits.size()) ? bigNum.digits[i] : 0;
        int diff = d1 - d2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else
            borrow = 0;
        result.digits.push_back(diff);
    }

    while (result.digits.size() > 1 && result.digits.back() == 0)
        result.digits.pop_back();

    result.isNegative = isNegative;

    // Fix "-0"
    if (result.digits.size() == 1 && result.digits[0] == 0)
        result.isNegative = false;

    return result;
}

BigNum BigNum::multiply(const BigNum& bigNum) {
    BigNum result;
    result.digits = vector<int>(digits.size() + bigNum.digits.size(), 0);

    for (size_t i = 0; i < digits.size(); i++) {
        int carry = 0;
        for (size_t j = 0; j < bigNum.digits.size() || carry; j++) {
            long long cur = result.digits[i + j] +
                            digits[i] * 1LL * (j < bigNum.digits.size() ? bigNum.digits[j] : 0) + carry;
            result.digits[i + j] = cur % 10;
            carry = cur / 10;
        }
    }

    while (result.digits.size() > 1 && result.digits.back() == 0)
        result.digits.pop_back();

    result.isNegative = (isNegative != bigNum.isNegative);
    return result;
}

BigNum BigNum::divide(const BigNum& divisor) {
    if (divisor.digits.size() == 1 && divisor.digits[0] == 0) {
        cout << "Error: Division by zero!" << endl;
        return BigNum("0");
    }

    BigNum dividend = *this;
    BigNum result;
    result.digits.clear();
    result.isNegative = (isNegative != divisor.isNegative);

    BigNum current;
    current.digits.clear();

    for (int i = dividend.digits.size() - 1; i >= 0; i--) {
        current.digits.insert(current.digits.begin(), dividend.digits[i]);
        while (current.digits.size() > 1 && current.digits.back() == 0)
            current.digits.pop_back();

        int x = 0;
        int l = 0, r = 9;
        while (l <= r) {
            int m = (l + r) / 2;
            BigNum temp = divisor.multiply(BigNum(to_string(m)));
            if (!temp.greaterThan(current)) {
                x = m;
                l = m + 1;
            } else
                r = m - 1;
        }

        result.digits.insert(result.digits.begin(), x);
        BigNum sub = divisor.multiply(BigNum(to_string(x)));
        current = current.subtract(sub);
    }

    while (result.digits.size() > 1 && result.digits.back() == 0)
        result.digits.pop_back();

    if (result.digits.size() == 1 && result.digits[0] == 0)
        result.isNegative = false;

    return result;
}

BigNum BigNum::mod(const BigNum& divisor) {
    if (divisor.digits.size() == 1 && divisor.digits[0] == 0) {
        cout << "Error: Modulo by zero!" << endl;
        return BigNum("0");
    }

    BigNum quotient = divide(divisor);
    BigNum product = quotient.multiply(divisor);
    BigNum remainder = subtract(product);

    if (remainder.isNegative)
        remainder.isNegative = false;

    return remainder;
}

