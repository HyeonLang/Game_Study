#pragma once
// 08_calc.h

//#include<iostream>
//using namespace std;

void Test(int a);

//class는 다른 곳에서도 쓰이는 경우가 많기 때문에 보통 header에 들어가 있다
//함수의 선언부 헤더파일에 두고 정의부는 소스파일로 넘겨준다.

class Calc
{
public:
	Calc(int value) : value(value) {}

	Calc& Add(int value);
	Calc& Sub(int value);
	Calc& Mul(int value);
	Calc& Div(int value);
	Calc& Mod(int value);

	void Test(int a);

	int GetValue() { return value; }

private:
	int value;
};


