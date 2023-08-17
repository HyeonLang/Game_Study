// 07_this_pointer_and_chaining_member_functions.cpp

#include<iostream>
using namespace std;

#define THIS_POINTER
#define CHAINING_MEMBER_FUNCTION

#ifdef THIS_POINTER

/*
	this pointer : 함수가 호출한 객체를 구별하기 위해
	기본적으로 넣어주는 해당 객체의 포인터
*/

class Test // 12
{
public:
	Test() {}
	~Test() {}


	// this : 해당 함수를 호출한 객체의 포인터
	auto /*this call*/ GetA()
	{
		// this의 주소는 그 실체의 주소
		cout << this << endl;
		return a;
	}

	// 매개변수와 멤버 변수의 이름이 같으면 네임 하이딩 발생
	//void SetA(const int& a) { a = a; } // 매개변수가 우선시 된다.

	// 구분하기 위해 이름을 변경
	//void SetA(const int& in_a) { a = in_a; }

	// this를 사용하면 매개변수와 이름이 동일하더라도 멤버 변수를 사용할 수 있다.
	void SetA(const int& a) { this->a = a; }

	auto GetB() { return b; }
	void SetB(const int& in_b) { b = in_b; }

private:
	int a;
	int b;
	int c;
};

int main()
{

	Test test1;
	test1.GetA();

	Test test2;
	test2.GetA();

	cout << &test1 << ", " << &test2 << endl;

	return 0;
}

#endif // THIS_POINTER


#ifdef CHAINING_MEMBER_FUNCTION
/*
	chaining member function
	- 자신을 연쇄적으로 호출하는 함수
*/

class Calc
{
public:
	Calc(int value) : value(value) {}

	//1.
	//void Add(int value) { this->value += value; }
	//void Sub(int value) { this->value -= value; }
	//void Mul(int value) { this->value *= value; }
	//void Div(int value) { this->value /= value; }
	//void Mod(int value) { this->value %= value; }

	// Calc a;
	// this  == &a
	// *this == *&a == a;

	//2.
	// reference 형태로 리턴
	// 반환값이 Calc& (나 자체)
	Calc& Add(int value) { this->value += value; return *this; }
	Calc& Sub(int value) { this->value -= value; return *this; }
	Calc& Mul(int value) { this->value *= value; return *this; }
	Calc& Div(int value) { this->value /= value; return *this; }
	Calc& Mod(int value) { this->value %= value; return *this; }

private:
	int value;
};


int test() { return 10; }

int main()
{
	cout << "a" << "b" << "c" << "d" << "e" << endl;

	//1.
	//Calc calc(10);
	//calc.Add(5);
	//calc.Div(2);
	//calc.Mul(3);
	//calc.Mod(5);
	//calc.Sub(2);

	//2. 위의 연산을 한줄로 처리하고 싶을때 

	Calc calc(10);

	// 이렇게 연쇄적으로 사용 가능 = chaining
	// 이렇게 쓰면 우선순위 상관없이 앞에서부터 계산
	calc.Add(5).Div(2).Mul(3).Mod(5).Sub(2);


	//3. 익명 객체를 사용해서 호출 가능
	Calc(10).Add(5).Div(2).Mul(3).Mod(5).Sub(2);

	return 0;
}

#endif
