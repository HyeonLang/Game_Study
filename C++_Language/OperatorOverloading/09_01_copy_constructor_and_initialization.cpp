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
    Fraction f2(f1); //���� ������

    f1 = f2; //���� ���� ������

    //���� �����̱� ������ f2(f1)�� ����.
    Fraction f3 = f1; //���� ������

    cout << "###################" << endl;
    CreateFraction(); //����ȭ��  copy constructor ����

    return 0;
}