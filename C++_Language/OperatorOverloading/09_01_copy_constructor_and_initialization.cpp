// 09_01_copy_constructor_and_initialization.cpp

#include<iostream>
#include<cassert>
using namespace std;

class Fraction
{
public:
    Fraction(int num = 0, int den = 0)
        : numerator(num)
        , denominator(den)
    {
        cout << "constructor!!" << endl;
    }

    Fraction(const Fraction& fraction) // copy constructor 
    {
        numerator = fraction.numerator;
        denominator = fraction.denominator;
        cout << "copy constructor!!" << endl;
    }

    Fraction& operator = (const Fraction& rhs) {
        cout << "copy assignment operator" << endl;
        //TODO:
        return *this;
    }

private:
    int numerator;
    int denominator;
};

Fraction CreateFraction()
{
    Fraction temp(5, 2); // constructor

    return temp; // copy constructor
}

int main() {
    Fraction f1;
    Fraction f2(f1); //복사 생성자

    f1 = f2; //복사 대입 생성자

    //생성 시점이기 때문에 f2(f1)과 같다.
    Fraction f3 = f1; //복사 생성자

    cout << "###################" << endl;
    CreateFraction(); //최적화시  copy constructor 생략

    return 0;
}