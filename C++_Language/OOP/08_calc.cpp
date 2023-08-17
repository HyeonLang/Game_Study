// 08_calc.cpp
#include"08_calc.h"

#include<iostream>

void Test(int a)
{
	// using은 내부에 사용해 전역에 적용되지 않도록 하자
	using namespace std;

	cout << "asd";
}

inline Calc& Calc::Add(int value) { this->value += value; return *this; }

inline Calc& Calc::Sub(int value) { this->value -= value; return *this; }

inline Calc& Calc::Mul(int value) { this->value *= value; return *this; }

inline Calc& Calc::Div(int value) { this->value /= value; return *this; }

inline Calc& Calc::Mod(int value) { this->value %= value; return *this; }

// 멤버 함수이기 때문에 어디 클래스의 소속인지를 명시해야 사용가능하다. -> Calc::
void Calc::Test(int a)
{


}
