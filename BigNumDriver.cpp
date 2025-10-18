// BigNumDriver.cpp - ULTRA COMPREHENSIVE EXTREME Testing Suite
// Tests EVERY possible edge case, boundary condition, and extreme scenario

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "BigNum.h"

using namespace std;

// Test counter
int testsPassed = 0;
int testsFailed = 0;

// Color codes for better visibility
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

// Helper function to compare BigNum with expected string
bool checkValue(const BigNum &num, const string &expected, const string &testName)
{
    BigNum exp(expected);
    BigNum numCopy(num);
    if (numCopy.equals(exp))
    {
        cout << GREEN << "✓ PASS: " << RESET << testName << endl;
        testsPassed++;
        return true;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << testName << endl;
        cout << "  Expected: " << expected << ", Got: ";
        numCopy.print();
        testsFailed++;
        return false;
    }
}

// Helper to generate random number string
string generateRandomNumber(int digits, bool allowNegative = true)
{
    string result = "";
    if (allowNegative && rand() % 2 == 0)
        result += "-";

    for (int i = 0; i < digits; i++)
    {
        if (i == 0)
            result += char('1' + rand() % 9); // First digit non-zero
        else
            result += char('0' + rand() % 10);
    }
    return result;
}

void testConstructorsExtreme()
{
    cout << BLUE << "\n========== EXTREME CONSTRUCTORS TESTING ==========\n"
         << RESET;

    // Default constructor
    BigNum a;
    checkValue(a, "0", "Default constructor");

    // Single digit
    for (int i = 0; i <= 9; i++)
    {
        BigNum b(to_string(i));
        checkValue(b, to_string(i), "Single digit: " + to_string(i));
    }

    // Negative single digits
    for (int i = -9; i <= -1; i++)
    {
        BigNum c(to_string(i));
        checkValue(c, to_string(i), "Negative single digit: " + to_string(i));
    }

    // Leading zeros - various patterns
    checkValue(BigNum("0"), "0", "Single zero");
    checkValue(BigNum("00"), "0", "Double zero");
    checkValue(BigNum("000000"), "0", "Multiple zeros");
    checkValue(BigNum("00123"), "123", "Leading zeros - simple");
    checkValue(BigNum("000000123456"), "123456", "Many leading zeros");
    checkValue(BigNum("00000000000000000000001"), "1", "Extreme leading zeros to 1");

    // Negative zero variations
    checkValue(BigNum("-0"), "0", "Negative zero -0");
    checkValue(BigNum("-00"), "0", "Negative double zero");
    checkValue(BigNum("-0000"), "0", "Negative multiple zeros");

    // Negative with leading zeros
    checkValue(BigNum("-00123"), "-123", "Negative with leading zeros");
    checkValue(BigNum("-000000456"), "-456", "Negative many leading zeros");

    // Powers of 10
    checkValue(BigNum("10"), "10", "Power of 10: 10");
    checkValue(BigNum("100"), "100", "Power of 10: 100");
    checkValue(BigNum("1000"), "1000", "Power of 10: 1000");
    checkValue(BigNum("10000"), "10000", "Power of 10: 10000");
    checkValue(BigNum("100000"), "100000", "Power of 10: 100000");
    checkValue(BigNum("1000000"), "1000000", "Power of 10: 1000000");

    // Powers of 10 - 1
    checkValue(BigNum("9"), "9", "10^1 - 1");
    checkValue(BigNum("99"), "99", "10^2 - 1");
    checkValue(BigNum("999"), "999", "10^3 - 1");
    checkValue(BigNum("9999"), "9999", "10^4 - 1");
    checkValue(BigNum("99999"), "99999", "10^5 - 1");
    checkValue(BigNum("999999"), "999999", "10^6 - 1");

    // Powers of 10 + 1
    checkValue(BigNum("11"), "11", "10 + 1");
    checkValue(BigNum("101"), "101", "100 + 1");
    checkValue(BigNum("1001"), "1001", "1000 + 1");
    checkValue(BigNum("10001"), "10001", "10000 + 1");

    // Very large numbers - increasing sizes
    checkValue(BigNum("123456789"), "123456789", "9 digits");
    checkValue(BigNum("12345678901234567890"), "12345678901234567890", "20 digits");
    checkValue(BigNum("123456789012345678901234567890"), "123456789012345678901234567890", "30 digits");
    checkValue(BigNum("1234567890123456789012345678901234567890"), "1234567890123456789012345678901234567890", "40 digits");
    checkValue(BigNum("12345678901234567890123456789012345678901234567890"), "12345678901234567890123456789012345678901234567890", "50 digits");

    // Extreme: 100+ digit number
    string hundred = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    checkValue(BigNum(hundred), hundred, "100 digit number");

    // All same digits
    checkValue(BigNum("1111111"), "1111111", "All 1s");
    checkValue(BigNum("22222222"), "22222222", "All 2s");
    checkValue(BigNum("555555555"), "555555555", "All 5s");
    checkValue(BigNum("9999999999"), "9999999999", "All 9s");

    // Integer constructor - boundaries
    checkValue(BigNum(0), "0", "Int: 0");
    checkValue(BigNum(1), "1", "Int: 1");
    checkValue(BigNum(-1), "-1", "Int: -1");
    checkValue(BigNum(2147483647), "2147483647", "Int: INT_MAX");
    checkValue(BigNum(-2147483648), "-2147483648", "Int: INT_MIN");

    // Copy constructor deep test
    BigNum orig("999999999999999999");
    BigNum copied(orig);
    checkValue(copied, "999999999999999999", "Copy constructor");
    orig.increment(); // Modify original
    checkValue(copied, "999999999999999999", "Copy independence - copied unchanged");
    checkValue(orig, "1000000000000000000", "Copy independence - original changed");

    // Invalid inputs
    checkValue(BigNum(""), "0", "Empty string");
    checkValue(BigNum("abc"), "0", "Letters only");
    checkValue(BigNum("12a34"), "0", "Mixed alphanumeric");
    checkValue(BigNum("12.34"), "0", "Decimal point");
    checkValue(BigNum("12,345"), "0", "With comma");
    checkValue(BigNum("+ 123"), "0", "With plus sign");
    checkValue(BigNum("--123"), "0", "Double negative");
    checkValue(BigNum("-"), "0", "Just negative sign");

    cout << YELLOW << "Constructor tests: " << testsPassed << " passed\n"
         << RESET;
}

void testAdditionExtreme()
{
    cout << BLUE << "\n========== EXTREME ADDITION TESTING ==========\n"
         << RESET;

    // Zero additions
    checkValue(BigNum("0").add(BigNum("0")), "0", "0 + 0");
    checkValue(BigNum("0").add(BigNum("1")), "1", "0 + 1");
    checkValue(BigNum("1").add(BigNum("0")), "1", "1 + 0");
    checkValue(BigNum("0").add(BigNum("-1")), "-1", "0 + (-1)");
    checkValue(BigNum("-1").add(BigNum("0")), "-1", "(-1) + 0");

    // Single digit additions - all combinations
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            BigNum a(to_string(i));
            BigNum b(to_string(j));
            checkValue(a.add(b), to_string(i + j),
                       to_string(i) + " + " + to_string(j));
        }
    }

    // Carry propagation tests
    checkValue(BigNum("9").add(BigNum("1")), "10", "9 + 1 (single carry)");
    checkValue(BigNum("99").add(BigNum("1")), "100", "99 + 1 (double carry)");
    checkValue(BigNum("999").add(BigNum("1")), "1000", "999 + 1 (triple carry)");
    checkValue(BigNum("9999").add(BigNum("1")), "10000", "9999 + 1");
    checkValue(BigNum("99999").add(BigNum("1")), "100000", "99999 + 1");
    checkValue(BigNum("999999").add(BigNum("1")), "1000000", "999999 + 1");
    checkValue(BigNum("9999999999").add(BigNum("1")), "10000000000", "All 9s + 1");

    // Multiple carries
    checkValue(BigNum("999").add(BigNum("999")), "1998", "999 + 999");
    checkValue(BigNum("9999").add(BigNum("9999")), "19998", "9999 + 9999");
    checkValue(BigNum("99999").add(BigNum("99999")), "199998", "99999 + 99999");

    // Same numbers
    checkValue(BigNum("123").add(BigNum("123")), "246", "Same: 123 + 123");
    checkValue(BigNum("456789").add(BigNum("456789")), "913578", "Same: 456789 + 456789");

    // Different sizes
    checkValue(BigNum("1").add(BigNum("999")), "1000", "1 + 999");
    checkValue(BigNum("999").add(BigNum("1")), "1000", "999 + 1");
    checkValue(BigNum("12").add(BigNum("9988")), "10000", "12 + 9988");
    checkValue(BigNum("1").add(BigNum("999999999")), "1000000000", "1 + 999999999");

    // Negative + Positive = Positive
    checkValue(BigNum("-50").add(BigNum("100")), "50", "-50 + 100 = 50");
    checkValue(BigNum("-1").add(BigNum("100")), "99", "-1 + 100 = 99");
    checkValue(BigNum("-999").add(BigNum("1000")), "1", "-999 + 1000 = 1");

    // Negative + Positive = Negative
    checkValue(BigNum("-100").add(BigNum("50")), "-50", "-100 + 50 = -50");
    checkValue(BigNum("-1000").add(BigNum("999")), "-1", "-1000 + 999 = -1");

    // Negative + Positive = Zero
    checkValue(BigNum("-50").add(BigNum("50")), "0", "-50 + 50 = 0");
    checkValue(BigNum("-999").add(BigNum("999")), "0", "-999 + 999 = 0");
    checkValue(BigNum("-123456").add(BigNum("123456")), "0", "Large cancel to zero");

    // Both negative
    checkValue(BigNum("-10").add(BigNum("-20")), "-30", "-10 + (-20)");
    checkValue(BigNum("-999").add(BigNum("-1")), "-1000", "-999 + (-1)");
    checkValue(BigNum("-500").add(BigNum("-500")), "-1000", "-500 + (-500)");

    // Very large additions
    checkValue(BigNum("999999999999999999").add(BigNum("1")),
               "1000000000000000000", "Large: 18 nines + 1");
    checkValue(BigNum("123456789123456789").add(BigNum("987654321987654321")),
               "1111111111111111110", "Large different numbers");

    // Assignment examples
    checkValue(BigNum("1111111111111111111111111").add(BigNum("1111111111111111111111111")),
               "2222222222222222222222222", "Assignment example 1");
    checkValue(BigNum("987654321987654321987654321987654321").add(BigNum("123456789123456789123456789123456789")),
               "1111111111111111111111111111111111110", "Assignment example 2");

    // Add integer overloads
    checkValue(BigNum("100").add(50), "150", "Add int: 100 + 50");
    checkValue(BigNum("999").add(1), "1000", "Add int: 999 + 1");
    checkValue(BigNum("0").add(100), "100", "Add int: 0 + 100");

    // Increment tests
    BigNum inc1("0");
    inc1.increment();
    checkValue(inc1, "1", "Increment: 0 -> 1");

    BigNum inc2("999");
    inc2.increment();
    checkValue(inc2, "1000", "Increment: 999 -> 1000");

    BigNum inc3("-1");
    inc3.increment();
    checkValue(inc3, "0", "Increment: -1 -> 0");

    BigNum inc4("-100");
    inc4.increment();
    checkValue(inc4, "-99", "Increment: -100 -> -99");

    // Compound add
    BigNum comp1("100");
    comp1.compoundAdd(BigNum("200"));
    checkValue(comp1, "300", "Compound add: 100 += 200");

    BigNum comp2("999");
    comp2.compoundAdd(1);
    checkValue(comp2, "1000", "Compound add int: 999 += 1");

    // Chain additions
    BigNum chain("10");
    chain.compoundAdd(BigNum("20"));
    chain.compoundAdd(BigNum("30"));
    chain.compoundAdd(BigNum("40"));
    checkValue(chain, "100", "Chain additions: 10+20+30+40");

    cout << YELLOW << "Addition tests: " << testsPassed << " passed\n"
         << RESET;
}

void testSubtractionExtreme()
{
    cout << BLUE << "\n========== EXTREME SUBTRACTION TESTING ==========\n"
         << RESET;

    // Zero subtractions
    checkValue(BigNum("0").subtract(BigNum("0")), "0", "0 - 0");
    checkValue(BigNum("1").subtract(BigNum("0")), "1", "1 - 0");
    checkValue(BigNum("0").subtract(BigNum("1")), "-1", "0 - 1");
    checkValue(BigNum("100").subtract(BigNum("0")), "100", "100 - 0");

    // Same number subtractions
    checkValue(BigNum("1").subtract(BigNum("1")), "0", "1 - 1");
    checkValue(BigNum("100").subtract(BigNum("100")), "0", "100 - 100");
    checkValue(BigNum("999").subtract(BigNum("999")), "0", "999 - 999");
    checkValue(BigNum("123456789").subtract(BigNum("123456789")), "0", "Large same - 0");

    // Single digit subtractions
    for (int i = 9; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            BigNum a(to_string(i));
            BigNum b(to_string(j));
            checkValue(a.subtract(b), to_string(i - j),
                       to_string(i) + " - " + to_string(j));
        }
    }

    // Borrowing tests
    checkValue(BigNum("10").subtract(BigNum("1")), "9", "10 - 1 (single borrow)");
    checkValue(BigNum("100").subtract(BigNum("1")), "99", "100 - 1 (double borrow)");
    checkValue(BigNum("1000").subtract(BigNum("1")), "999", "1000 - 1 (triple borrow)");
    checkValue(BigNum("10000").subtract(BigNum("1")), "9999", "10000 - 1");
    checkValue(BigNum("100000").subtract(BigNum("1")), "99999", "100000 - 1");
    checkValue(BigNum("1000000").subtract(BigNum("1")), "999999", "1000000 - 1");
    checkValue(BigNum("10000000000").subtract(BigNum("1")), "9999999999", "All borrows");

    // Result negative
    checkValue(BigNum("1").subtract(BigNum("2")), "-1", "1 - 2 = -1");
    checkValue(BigNum("100").subtract(BigNum("200")), "-100", "100 - 200 = -100");
    checkValue(BigNum("50").subtract(BigNum("100")), "-50", "50 - 100 = -50");
    checkValue(BigNum("1").subtract(BigNum("999")), "-998", "1 - 999 = -998");

    // Negative - Positive
    checkValue(BigNum("-10").subtract(BigNum("20")), "-30", "-10 - 20 = -30");
    checkValue(BigNum("-100").subtract(BigNum("50")), "-150", "-100 - 50 = -150");
    checkValue(BigNum("-999").subtract(BigNum("1")), "-1000", "-999 - 1 = -1000");

    // Positive - Negative (becomes addition)
    checkValue(BigNum("10").subtract(BigNum("-20")), "30", "10 - (-20) = 30");
    checkValue(BigNum("100").subtract(BigNum("-50")), "150", "100 - (-50) = 150");
    checkValue(BigNum("999").subtract(BigNum("-1")), "1000", "999 - (-1) = 1000");

    // Both negative
    checkValue(BigNum("-10").subtract(BigNum("-5")), "-5", "-10 - (-5) = -5");
    checkValue(BigNum("-100").subtract(BigNum("-50")), "-50", "-100 - (-50) = -50");
    checkValue(BigNum("-50").subtract(BigNum("-100")), "50", "-50 - (-100) = 50");
    checkValue(BigNum("-999").subtract(BigNum("-999")), "0", "-999 - (-999) = 0");

    // Large subtractions
    checkValue(BigNum("1000000000000000000").subtract(BigNum("1")),
               "999999999999999999", "18 zeros - 1");
    checkValue(BigNum("999999999999999999").subtract(BigNum("999999999999999998")),
               "1", "Large consecutive");

    // Subtract integer
    checkValue(BigNum("100").subtract(30), "70", "Subtract int: 100 - 30");
    checkValue(BigNum("1000").subtract(1), "999", "Subtract int: 1000 - 1");

    // Decrement tests
    BigNum dec1("1");
    dec1.decrement();
    checkValue(dec1, "0", "Decrement: 1 -> 0");

    BigNum dec2("1000");
    dec2.decrement();
    checkValue(dec2, "999", "Decrement: 1000 -> 999");

    BigNum dec3("0");
    dec3.decrement();
    checkValue(dec3, "-1", "Decrement: 0 -> -1");

    BigNum dec4("-99");
    dec4.decrement();
    checkValue(dec4, "-100", "Decrement: -99 -> -100");

    // Compound subtract
    BigNum comp1("500");
    comp1.compoundSubtract(BigNum("200"));
    checkValue(comp1, "300", "Compound sub: 500 -= 200");

    BigNum comp2("1000");
    comp2.compoundSubtract(1);
    checkValue(comp2, "999", "Compound sub int: 1000 -= 1");

    cout << YELLOW << "Subtraction tests: " << testsPassed << " passed\n"
         << RESET;
}

void testMultiplicationExtreme()
{
    cout << BLUE << "\n========== EXTREME MULTIPLICATION TESTING ==========\n"
         << RESET;

    // Zero multiplications
    checkValue(BigNum("0").multiply(BigNum("0")), "0", "0 x 0");
    checkValue(BigNum("0").multiply(BigNum("1")), "0", "0 x 1");
    checkValue(BigNum("1").multiply(BigNum("0")), "0", "1 x 0");
    checkValue(BigNum("0").multiply(BigNum("999")), "0", "0 x 999");
    checkValue(BigNum("999").multiply(BigNum("0")), "0", "999 x 0");
    checkValue(BigNum("123456789").multiply(BigNum("0")), "0", "Large x 0");

    // One multiplications
    checkValue(BigNum("1").multiply(BigNum("1")), "1", "1 x 1");
    checkValue(BigNum("1").multiply(BigNum("123")), "123", "1 x 123");
    checkValue(BigNum("456").multiply(BigNum("1")), "456", "456 x 1");
    checkValue(BigNum("999999").multiply(BigNum("1")), "999999", "Large x 1");

    // Single digit multiplications - all combinations
    int products[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {0, 2, 4, 6, 8, 10, 12, 14, 16, 18},
        {0, 3, 6, 9, 12, 15, 18, 21, 24, 27},
        {0, 4, 8, 12, 16, 20, 24, 28, 32, 36},
        {0, 5, 10, 15, 20, 25, 30, 35, 40, 45},
        {0, 6, 12, 18, 24, 30, 36, 42, 48, 54},
        {0, 7, 14, 21, 28, 35, 42, 49, 56, 63},
        {0, 8, 16, 24, 32, 40, 48, 56, 64, 72},
        {0, 9, 18, 27, 36, 45, 54, 63, 72, 81}};

    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            BigNum a(to_string(i));
            BigNum b(to_string(j));
            checkValue(a.multiply(b), to_string(products[i][j]),
                       to_string(i) + " x " + to_string(j));
        }
    }

    // Powers of 10
    checkValue(BigNum("10").multiply(BigNum("10")), "100", "10 x 10");
    checkValue(BigNum("10").multiply(BigNum("100")), "1000", "10 x 100");
    checkValue(BigNum("100").multiply(BigNum("100")), "10000", "100 x 100");
    checkValue(BigNum("100").multiply(BigNum("1000")), "100000", "100 x 1000");

    // Multiply by powers of 10
    checkValue(BigNum("123").multiply(BigNum("10")), "1230", "123 x 10");
    checkValue(BigNum("123").multiply(BigNum("100")), "12300", "123 x 100");
    checkValue(BigNum("123").multiply(BigNum("1000")), "123000", "123 x 1000");
    checkValue(BigNum("456").multiply(BigNum("10000")), "4560000", "456 x 10000");

    // Same number multiplications
    checkValue(BigNum("11").multiply(BigNum("11")), "121", "11 x 11");
    checkValue(BigNum("12").multiply(BigNum("12")), "144", "12 x 12");
    checkValue(BigNum("99").multiply(BigNum("99")), "9801", "99 x 99");
    checkValue(BigNum("111").multiply(BigNum("111")), "12321", "111 x 111");
    checkValue(BigNum("999").multiply(BigNum("999")), "998001", "999 x 999");

    // Assignment examples
    checkValue(BigNum("1111111111111111111111111").multiply(BigNum("1111111111111111111111111")),
               "1234567901234567901234567654320987654320987654321",
               "Assignment multiplication 1");

    checkValue(BigNum("987654321987654321987654321987654321").multiply(BigNum("123456789123456789123456789123456789")),
               "121932631356500531591068431825636331816338969581771069347203169112635269",
               "Assignment multiplication 2");

    // Sign combinations
    checkValue(BigNum("10").multiply(BigNum("-5")), "-50", "Positive x Negative");
    checkValue(BigNum("-10").multiply(BigNum("5")), "-50", "Negative x Positive");
    checkValue(BigNum("-10").multiply(BigNum("-5")), "50", "Negative x Negative");
    checkValue(BigNum("100").multiply(BigNum("-3")), "-300", "Large Pos x Neg");
    checkValue(BigNum("-999").multiply(BigNum("-999")), "998001", "Large Neg x Neg");

    // Large multiplications
    checkValue(BigNum("12345").multiply(BigNum("67890")), "838102050", "5 digit x 5 digit");
    checkValue(BigNum("999999").multiply(BigNum("999999")), "999998000001", "6 nines x 6 nines");

    // Extreme sizes
    checkValue(BigNum("99999999999999999999").multiply(BigNum("99999999999999999999")),
               "9999999999999999999800000000000000000001", "20 nines x 20 nines");

    cout << YELLOW << "Multiplication tests: " << testsPassed << " passed\n"
         << RESET;
}

void testDivisionExtreme()
{
    cout << BLUE << "\n========== EXTREME DIVISION TESTING ==========\n"
         << RESET;

    // Division by zero
    cout << "Testing division by zero (should see error):\n";
    checkValue(BigNum("100").div(BigNum("0")), "0", "100 / 0 (error case)");
    checkValue(BigNum("999").div(BigNum("0")), "0", "999 / 0 (error case)");

    // Division by one
    checkValue(BigNum("1").div(BigNum("1")), "1", "1 / 1");
    checkValue(BigNum("100").div(BigNum("1")), "100", "100 / 1");
    checkValue(BigNum("999").div(BigNum("1")), "999", "999 / 1");
    checkValue(BigNum("123456789").div(BigNum("1")), "123456789", "Large / 1");

    // Same numbers
    checkValue(BigNum("5").div(BigNum("5")), "1", "5 / 5");
    checkValue(BigNum("100").div(BigNum("100")), "1", "100 / 100");
    checkValue(BigNum("999").div(BigNum("999")), "1", "999 / 999");
    checkValue(BigNum("123456789").div(BigNum("123456789")), "1", "Large / same");

    // Smaller / Larger = 0
    checkValue(BigNum("1").div(BigNum("2")), "0", "1 / 2 = 0");
    checkValue(BigNum("5").div(BigNum("10")), "0", "5 / 10 = 0");
    checkValue(BigNum("50").div(BigNum("100")), "0", "50 / 100 = 0");
    checkValue(BigNum("999").div(BigNum("1000")), "0", "999 / 1000 = 0");

    // Exact divisions
    checkValue(BigNum("10").div(BigNum("2")), "5", "10 / 2");
    checkValue(BigNum("100").div(BigNum("10")), "10", "100 / 10");
    checkValue(BigNum("1000").div(BigNum("100")), "10", "1000 / 100");
    checkValue(BigNum("1000").div(BigNum("10")), "100", "1000 / 10");
    checkValue(BigNum("10000").div(BigNum("100")), "100", "10000 / 100");

    // Integer divisions
    checkValue(BigNum("10").div(BigNum("3")), "3", "10 / 3");
    checkValue(BigNum("100").div(BigNum("7")), "14", "100 / 7");
    checkValue(BigNum("456").div(BigNum("123")), "3", "456 / 123");
    checkValue(BigNum("1000").div(BigNum("9")), "111", "1000 / 9");

    // Powers of 10 divisions
    checkValue(BigNum("1000").div(BigNum("10")), "100", "1000 / 10");
    checkValue(BigNum("10000").div(BigNum("100")), "100", "10000 / 100");
    checkValue(BigNum("100000").div(BigNum("1000")), "100", "100000 / 1000");

    // Single digit divisions
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            BigNum a(to_string(i));
            BigNum b(to_string(j));
            checkValue(a.div(b), to_string(i / j),
                       to_string(i) + " / " + to_string(j));
        }
    }

    // Assignment example
    checkValue(BigNum("987654321987654321987654321987654321").div(BigNum("123456789123456789123456789123456789")),
               "8", "Assignment division example");

    // Sign combinations
    checkValue(BigNum("100").div(BigNum("-10")), "-10", "Positive / Negative");
    checkValue(BigNum("-100").div(BigNum("10")), "-10", "Negative / Positive");
    checkValue(BigNum("-100").div(BigNum("-10")), "10", "Negative / Negative");
    checkValue(BigNum("999").div(BigNum("-3")), "-333", "Large Pos / Neg");
    checkValue(BigNum("-1000").div(BigNum("-10")), "100", "Large Neg / Neg");

    // Large divisions
    checkValue(BigNum("999999999999999999999999").div(BigNum("999999999999")),
               "1000000000001", "Very large division");
    checkValue(BigNum("123456789012345678901234567890").div(BigNum("123456789")),
               "1000000000100000000010", "30 digit / 9 digit");

    // Edge case: result is 1
    checkValue(BigNum("1000").div(BigNum("999")), "1", "1000 / 999 = 1");
    checkValue(BigNum("2000").div(BigNum("1999")), "1", "2000 / 1999 = 1");

    cout << YELLOW << "Division tests: " << testsPassed << " passed\n"
         << RESET;
}

void testModuloExtreme()
{
    cout << BLUE << "\n========== EXTREME MODULO TESTING ==========\n"
         << RESET;

    // Modulo by zero
    cout << "Testing modulo by zero (should see error):\n";
    checkValue(BigNum("100").mod(BigNum("0")), "0", "100 % 0 (error case)");

    // Modulo by one (always 0)
    checkValue(BigNum("1").mod(BigNum("1")), "0", "1 % 1");
    checkValue(BigNum("100").mod(BigNum("1")), "0", "100 % 1");
    checkValue(BigNum("999").mod(BigNum("1")), "0", "999 % 1");
    checkValue(BigNum("123456789").mod(BigNum("1")), "0", "Large % 1");

    // Same numbers (always 0)
    checkValue(BigNum("5").mod(BigNum("5")), "0", "5 % 5");
    checkValue(BigNum("100").mod(BigNum("100")), "0", "100 % 100");
    checkValue(BigNum("999").mod(BigNum("999")), "0", "999 % 999");

    // Smaller % Larger = smaller
    checkValue(BigNum("1").mod(BigNum("2")), "1", "1 % 2");
    checkValue(BigNum("5").mod(BigNum("10")), "5", "5 % 10");
    checkValue(BigNum("50").mod(BigNum("100")), "50", "50 % 100");
    checkValue(BigNum("999").mod(BigNum("1000")), "999", "999 % 1000");

    // Exact divisions (remainder 0)
    checkValue(BigNum("10").mod(BigNum("2")), "0", "10 % 2");
    checkValue(BigNum("100").mod(BigNum("10")), "0", "100 % 10");
    checkValue(BigNum("1000").mod(BigNum("100")), "0", "1000 % 100");

    // Basic modulo operations
    checkValue(BigNum("10").mod(BigNum("3")), "1", "10 % 3");
    checkValue(BigNum("10").mod(BigNum("4")), "2", "10 % 4");
    checkValue(BigNum("100").mod(BigNum("7")), "2", "100 % 7");
    checkValue(BigNum("456").mod(BigNum("123")), "87", "456 % 123");

    // Single digit modulo
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            BigNum a(to_string(i));
            BigNum b(to_string(j));
            checkValue(a.mod(b), to_string(i % j),
                       to_string(i) + " % " + to_string(j));
        }
    }

    // Assignment example
    checkValue(BigNum("987654321987654321987654321987654321").mod(BigNum("123456789123456789123456789123456789")),
               "9000000009000000009000000009", "Assignment modulo example");

    // Powers of 10 modulo
    checkValue(BigNum("12345").mod(BigNum("10")), "5", "12345 % 10");
    checkValue(BigNum("12345").mod(BigNum("100")), "45", "12345 % 100");
    checkValue(BigNum("12345").mod(BigNum("1000")), "345", "12345 % 1000");

    // Large modulo
    checkValue(BigNum("999999999999999999").mod(BigNum("7")), "0", "Large % 7");
    checkValue(BigNum("123456789012345678901234567890").mod(BigNum("9")), "0", "Large % 9");

    cout << YELLOW << "Modulo tests: " << testsPassed << " passed\n"
         << RESET;
}

void testComparisonExtreme()
{
    cout << BLUE << "\n========== EXTREME COMPARISON TESTING ==========\n"
         << RESET;

    // Equals tests
    if (BigNum("0").equals(BigNum("0")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "0 == 0\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "0 == 0\n";
        testsFailed++;
    }

    if (BigNum("1").equals(BigNum("1")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "1 == 1\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "1 == 1\n";
        testsFailed++;
    }

    if (BigNum("999").equals(BigNum("999")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "999 == 999\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "999 == 999\n";
        testsFailed++;
    }

    if (BigNum("-100").equals(BigNum("-100")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "-100 == -100\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "-100 == -100\n";
        testsFailed++;
    }

    if (!BigNum("100").equals(BigNum("99")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "100 != 99\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "100 != 99\n";
        testsFailed++;
    }

    if (!BigNum("100").equals(BigNum("-100")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "100 != -100\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "100 != -100\n";
        testsFailed++;
    }

    // Not equals tests
    if (BigNum("1").notEquals(BigNum("2")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "1 != 2\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "1 != 2\n";
        testsFailed++;
    }

    if (!BigNum("5").notEquals(BigNum("5")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "!(5 != 5)\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "!(5 != 5)\n";
        testsFailed++;
    }

    // Less than tests - positive numbers
    if (BigNum("1").lessThan(BigNum("2")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "1 < 2\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "1 < 2\n";
        testsFailed++;
    }

    if (BigNum("99").lessThan(BigNum("100")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "99 < 100\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "99 < 100\n";
        testsFailed++;
    }

    if (BigNum("999").lessThan(BigNum("1000")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "999 < 1000\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "999 < 1000\n";
        testsFailed++;
    }

    if (!BigNum("100").lessThan(BigNum("100")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "!(100 < 100)\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "!(100 < 100)\n";
        testsFailed++;
    }

    // Less than tests - negative numbers
    if (BigNum("-100").lessThan(BigNum("-50")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "-100 < -50\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "-100 < -50\n";
        testsFailed++;
    }

    if (BigNum("-999").lessThan(BigNum("-1")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "-999 < -1\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "-999 < -1\n";
        testsFailed++;
    }

    // Less than tests - mixed signs
    if (BigNum("-1").lessThan(BigNum("0")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "-1 < 0\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "-1 < 0\n";
        testsFailed++;
    }

    if (BigNum("-100").lessThan(BigNum("1")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "-100 < 1\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "-100 < 1\n";
        testsFailed++;
    }

    // Greater than tests - positive
    if (BigNum("2").greaterThan(BigNum("1")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "2 > 1\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "2 > 1\n";
        testsFailed++;
    }

    if (BigNum("100").greaterThan(BigNum("99")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "100 > 99\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "100 > 99\n";
        testsFailed++;
    }

    if (BigNum("1000").greaterThan(BigNum("999")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "1000 > 999\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "1000 > 999\n";
        testsFailed++;
    }

    // Greater than tests - negative
    if (BigNum("-50").greaterThan(BigNum("-100")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "-50 > -100\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "-50 > -100\n";
        testsFailed++;
    }

    // Greater than tests - mixed
    if (BigNum("0").greaterThan(BigNum("-1")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "0 > -1\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "0 > -1\n";
        testsFailed++;
    }

    if (BigNum("1").greaterThan(BigNum("-100")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "1 > -100\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "1 > -100\n";
        testsFailed++;
    }

    // Different lengths comparison
    if (BigNum("1000").greaterThan(BigNum("999")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "1000 > 999 (different length)\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "1000 > 999 (different length)\n";
        testsFailed++;
    }

    if (BigNum("10000").greaterThan(BigNum("9999")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "10000 > 9999 (different length)\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "10000 > 9999 (different length)\n";
        testsFailed++;
    }

    // Large number comparisons
    if (BigNum("999999999999999999999999").lessThan(BigNum("1000000000000000000000000")))
    {
        cout << GREEN << "✓ PASS: " << RESET << "Large: 24 nines < 1 with 24 zeros\n";
        testsPassed++;
    }
    else
    {
        cout << RED << "✗ FAIL: " << RESET << "Large comparison\n";
        testsFailed++;
    }

    cout << YELLOW << "Comparison tests: " << testsPassed << " passed\n"
         << RESET;
}

void testCopyAndAssignmentExtreme()
{
    cout << BLUE << "\n========== EXTREME COPY & ASSIGNMENT TESTING ==========\n"
         << RESET;

    // Copy function
    BigNum a("0");
    BigNum b;
    b.copy(a);
    checkValue(b, "0", "Copy: 0");

    BigNum c("999999999");
    BigNum d;
    d.copy(c);
    checkValue(d, "999999999", "Copy: large number");

    BigNum e("-12345");
    BigNum f;
    f.copy(e);
    checkValue(f, "-12345", "Copy: negative");

    // Assignment operator
    BigNum g("1");
    BigNum h;
    h = g;
    checkValue(h, "1", "Assignment: 1");

    BigNum i("123456789012345678901234567890");
    BigNum j;
    j = i;
    checkValue(j, "123456789012345678901234567890", "Assignment: very large");

    // Self-assignment
    BigNum k("500");
    k = k;
    checkValue(k, "500", "Self-assignment");



    // Independence test
    BigNum orig("1000");
    BigNum copied;
    copied.copy(orig);
    orig.compoundAdd(500);
    checkValue(copied, "1000", "Copy independence: copied unchanged");
    checkValue(orig, "1500", "Copy independence: original modified");

    // Zerofy tests
    BigNum z1("999");
    z1.zerofy();
    checkValue(z1, "0", "Zerofy: 999");

    BigNum z2("-999");
    z2.zerofy();
    checkValue(z2, "0", "Zerofy: -999");

    BigNum z3("0");
    z3.zerofy();
    checkValue(z3, "0", "Zerofy: already 0");

    cout << YELLOW << "Copy & Assignment tests: " << testsPassed << " passed\n"
         << RESET;
}

void testFileIOExtreme()
{
    cout << BLUE << "\n========== EXTREME FILE I/O TESTING ==========\n"
         << RESET;

    // Basic file I/O
    BigNum a("123456789");
    string file1 = "test_basic.txt";
    a.printToFile(file1);
    BigNum b;
    b.inputFromFile(file1);
    checkValue(b, "123456789", "File I/O: basic");

    // Zero
    BigNum c("0");
    string file2 = "test_zero.txt";
    c.printToFile(file2);
    BigNum d;
    d.inputFromFile(file2);
    checkValue(d, "0", "File I/O: zero");

    // Negative
    BigNum e("-987654321");
    string file3 = "test_negative.txt";
    e.printToFile(file3);
    BigNum f;
    f.inputFromFile(file3);
    checkValue(f, "-987654321", "File I/O: negative");

    // Very large
    BigNum g("999999999999999999999999999999999999999999999999");
    string file4 = "test_large.txt";
    g.printToFile(file4);
    BigNum h;
    h.inputFromFile(file4);
    checkValue(h, "999999999999999999999999999999999999999999999999", "File I/O: 48 digit number");

    // Single digit
    BigNum i("7");
    string file5 = "test_single.txt";
    i.printToFile(file5);
    BigNum j;
    j.inputFromFile(file5);
    checkValue(j, "7", "File I/O: single digit");

    // Negative single digit
    BigNum k("-5");
    string file6 = "test_neg_single.txt";
    k.printToFile(file6);
    BigNum l;
    l.inputFromFile(file6);
    checkValue(l, "-5", "File I/O: negative single digit");

    // Multiple file operations
    for (int i = 0; i < 5; i++)
    {
        string num = to_string((i + 1) * 111);
        BigNum m(num);
        string fname = "test_multi_" + to_string(i) + ".txt";
        m.printToFile(fname);
        BigNum n;
        n.inputFromFile(fname);
        checkValue(n, num, "File I/O multi " + to_string(i));
    }

    cout << YELLOW << "File I/O tests: " << testsPassed << " passed\n"
         << RESET;
}

void testEdgeCasesUltraExtreme()
{
    cout << BLUE << "\n========== ULTRA EXTREME EDGE CASES ==========\n"
         << RESET;

    // Boundary transitions
    checkValue(BigNum("9").add(BigNum("1")), "10", "9->10 boundary");
    checkValue(BigNum("99").add(BigNum("1")), "100", "99->100 boundary");
    checkValue(BigNum("999").add(BigNum("1")), "1000", "999->1000 boundary");
    checkValue(BigNum("9999").add(BigNum("1")), "10000", "9999->10000 boundary");

    checkValue(BigNum("10").subtract(BigNum("1")), "9", "10->9 boundary");
    checkValue(BigNum("100").subtract(BigNum("1")), "99", "100->99 boundary");
    checkValue(BigNum("1000").subtract(BigNum("1")), "999", "1000->999 boundary");

    // Zero crossing
    checkValue(BigNum("1").subtract(BigNum("1")), "0", "Positive to zero");
    checkValue(BigNum("-1").add(BigNum("1")), "0", "Negative to zero");
    checkValue(BigNum("0").add(BigNum("1")), "1", "Zero to positive");
    checkValue(BigNum("0").subtract(BigNum("1")), "-1", "Zero to negative");

    // Sign changes through operations
    BigNum pos("100");
    pos.compoundSubtract(BigNum("200"));
    checkValue(pos, "-100", "Positive becomes negative");

    BigNum neg("-100");
    neg.compoundAdd(BigNum("200"));
    checkValue(neg, "100", "Negative becomes positive");

    // Alternating operations
    BigNum alt("1000");
    for (int i = 0; i < 10; i++)
    {
        alt.increment();
        alt.decrement();
    }
    checkValue(alt, "1000", "10x increment/decrement cancel");

    // Repeated operations
    BigNum rep("1");
    for (int i = 0; i < 10; i++)
    {
        rep.compoundAdd(BigNum("1"));
    }
    checkValue(rep, "11", "Add 1 ten times");

    // Large chain
    BigNum chain("0");
    chain.compoundAdd(BigNum("100"));
    chain.compoundAdd(BigNum("200"));
    chain.compoundSubtract(BigNum("50"));
    chain.compoundAdd(BigNum("50"));
    checkValue(chain, "300", "Complex chain: 0+100+200-50+50");

    // Multiplication then division
    BigNum md("123");
    BigNum temp1 = md.multiply(BigNum("456"));
    BigNum result1 = temp1.div(BigNum("456"));
    checkValue(result1, "123", "Multiply then divide (inverse)");

    // Addition then subtraction
    BigNum as("999");
    BigNum temp2 = as.add(BigNum("111"));
    BigNum result2 = temp2.subtract(BigNum("111"));
    checkValue(result2, "999", "Add then subtract (inverse)");

    // Powers of 2
    BigNum pow2("1");
    for (int i = 0; i < 10; i++)
    {
        pow2 = pow2.multiply(BigNum("2"));
    }
    checkValue(pow2, "1024", "2^10 = 1024");

    // Factorial-like (5!)
    BigNum fact("1");
    for (int i = 2; i <= 5; i++)
    {
        fact = fact.multiply(BigNum(to_string(i)));
    }
    checkValue(fact, "120", "5! = 120");

    // All operations on same number
    BigNum all("100");
    BigNum res1 = all.add(BigNum("50"));
    BigNum res2 = all.subtract(BigNum("50"));
    BigNum res3 = all.multiply(BigNum("2"));
    BigNum res4 = all.div(BigNum("2"));
    checkValue(res1, "150", "Same number: add");
    checkValue(res2, "50", "Same number: subtract");
    checkValue(res3, "200", "Same number: multiply");
    checkValue(res4, "50", "Same number: divide");

    cout << YELLOW << "Ultra extreme edge cases: " << testsPassed << " passed\n"
         << RESET;
}

void testStressExtreme()
{
    cout << BLUE << "\n========== STRESS TESTING EXTREME ==========\n"
         << RESET;

    // 100+ digit number
    string huge = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    BigNum h1(huge);
    checkValue(h1, huge, "100 digit construction");

    // 200+ digit number
    string giant = huge + huge;
    BigNum h2(giant);
    checkValue(h2, giant, "200 digit construction");

    // Massive addition
    BigNum m1("999999999999999999999999999999999999999999");
    BigNum m2("1");
    BigNum m3 = m1.add(m2);
    checkValue(m3, "1000000000000000000000000000000000000000000", "Massive carry propagation");

    // Massive multiplication
    BigNum m4("999999999999");
    BigNum m5("999999999999");
    BigNum m6 = m4.multiply(m5);
    checkValue(m6, "999999999998000000000001", "12 nines x 12 nines");

    // 1000 increments
    BigNum inc("0");
    for (int i = 0; i < 1000; i++)
    {
        inc.increment();
    }
    checkValue(inc, "1000", "1000 increments from 0");

    // 100 additions
    BigNum add("0");
    for (int i = 0; i < 100; i++)
    {
        add.compoundAdd(BigNum("10"));
    }
    checkValue(add, "1000", "100 additions of 10");

    // Repeated doubling
    BigNum dbl("1");
    for (int i = 0; i < 20; i++)
    {
        dbl = dbl.multiply(BigNum("2"));
    }
    checkValue(dbl, "1048576", "2^20");

    // Fibonacci-like sequence (small)
    BigNum fib1("1");
    BigNum fib2("1");
    for (int i = 1; i < 8; i++)
    {
        BigNum temp = fib1.add(fib2);
        fib1 = fib2;
        fib2 = temp;
    }
    checkValue(fib2, "34", "Fibonacci F(9)");

    // Large powers of 10 addition
    BigNum p1("1000000000000000000000000");
    BigNum p2("1000000000000000000000000");
    BigNum p3 = p1.add(p2);
    checkValue(p3, "2000000000000000000000000", "10^24 + 10^24");

    // Division stress
    BigNum d1("999999999999999999999999999");
    BigNum d2("3");
    BigNum d3 = d1.div(d2);
    checkValue(d3, "333333333333333333333333333", "27 nines / 3");

    cout << GREEN << "\n✓ STRESS TESTS COMPLETE!\n"
         << RESET;
}

void testRandomCases()
{
    cout << BLUE << "\n========== RANDOM TEST CASES ==========\n"
         << RESET;

    srand(time(0));

    // Random additions
    for (int i = 0; i < 20; i++)
    {
        int a = rand() % 1000;
        int b = rand() % 1000;
        BigNum ba(to_string(a));
        BigNum bb(to_string(b));
        checkValue(ba.add(bb), to_string(a + b),
                   "Random add: " + to_string(a) + " + " + to_string(b));
    }

    // Random subtractions
    for (int i = 0; i < 20; i++)
    {
        int a = rand() % 1000;
        int b = rand() % 1000;
        BigNum ba(to_string(a));
        BigNum bb(to_string(b));
        checkValue(ba.subtract(bb), to_string(a - b),
                   "Random sub: " + to_string(a) + " - " + to_string(b));
    }

    // Random multiplications
    for (int i = 0; i < 20; i++)
    {
        int a = rand() % 100;
        int b = rand() % 100;
        BigNum ba(to_string(a));
        BigNum bb(to_string(b));
        checkValue(ba.multiply(bb), to_string(a * b),
                   "Random mul: " + to_string(a) + " x " + to_string(b));
    }

    // Random divisions
    for (int i = 0; i < 20; i++)
    {
        int a = rand() % 1000 + 1;
        int b = rand() % 100 + 1;
        BigNum ba(to_string(a));
        BigNum bb(to_string(b));
        checkValue(ba.div(bb), to_string(a / b),
                   "Random div: " + to_string(a) + " / " + to_string(b));
    }

    cout << YELLOW << "Random test cases: completed\n"
         << RESET;
}

int main()
{
    cout << BLUE << "========================================\n";
    cout << "   BIGNUM ULTRA EXTREME TEST SUITE     \n";
    cout << "     INFINITELY ROBUST TESTING         \n";
    cout << "========================================\n"
         << RESET;

    testConstructorsExtreme();
    testAdditionExtreme();
    testSubtractionExtreme();
    testMultiplicationExtreme();
    testDivisionExtreme();
    testModuloExtreme();
    testComparisonExtreme();
    testCopyAndAssignmentExtreme();
    testFileIOExtreme();
    testEdgeCasesUltraExtreme();
    testStressExtreme();
    testRandomCases();

    // Final summary
    cout << BLUE << "\n========================================\n";
    cout << "         FINAL TEST SUMMARY             \n";
    cout << "========================================\n"
         << RESET;
    cout << GREEN << "Total Tests Passed: " << testsPassed << "\n"
         << RESET;
    cout << RED << "Total Tests Failed: " << testsFailed << "\n"
         << RESET;

    double successRate = (testsPassed * 100.0) / (testsPassed + testsFailed);
    cout << YELLOW << "Success Rate: " << successRate << "%\n"
         << RESET;

    if (testsFailed == 0)
    {
        cout << GREEN << "\nALL TESTS PASSED! Your BigNum is ULTRA EXTREME!\n"
             << RESET;
    }
    else
    {
        cout << RED << "\nSome tests failed. Review your BigNum implementation.\n"
             << RESET;
    }

    return 0;
}