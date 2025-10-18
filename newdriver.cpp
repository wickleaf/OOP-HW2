#include <iostream>
#include "BigNum.h"
using namespace std;

int main() {
    BigNum num1("1111111111111111111111111");
    BigNum num2("1111111111111111111111111");

    cout << "num1 = "; num1.print(); cout << endl;
    cout << "num2 = "; num2.print(); cout << endl;

    cout << "Addition: "; num1.add(num2).print(); cout << endl;
    cout << "Subtraction: "; num1.subtract(num2).print(); cout << endl;
    cout << "Multiplication: "; num1.multiply(num2).print(); cout << endl;
    cout << "Div: "; num1.div(num2).print(); cout << endl;
    cout << "Mod: "; num1.mod(num2).print(); cout << endl;
}
