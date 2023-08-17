// 08_typecast_operator.cpp

#include<iostream>
using namespace std;

class Won
{
public:
	Won(int value = 0) : value(value) {}

	//Won -> int 형변환 operator
	operator int() { //반환값 생략
		return value;
	}

private:
	int value = 0;
};

class Point
{
public:
	Point(float x, float y, float z)
		: x(x), y(y), z(z)
	{

	}

	//float 배열로 형변환 :  배열은 매개변수로 넘길 때 포인터로 받음
	//-> 캐스팅을 포인터로 처리
	operator float* () {
		return &x; //x,y,z(멤버)가 연속적으로 붙어있으므로 x의 주소가 시작주소가 됨.
	}

private:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

void PrintPoint(float points[3])
{
	cout << points[0] << endl;
	cout << points[1] << endl;
	cout << points[2] << endl;
}

void Print(int val)
{
	cout << val << endl;
}

int main()
{
	Won w(10);

	Print(w);

	Point p(1.0f, 2.0f, 3.0f);

	PrintPoint(p);

	return 0;
}