// 08_typecast_operator.cpp

#include<iostream>
using namespace std;

class Won
{
public:
	Won(int value = 0) : value(value) {}

	//Won -> int ����ȯ operator
	operator int() { //��ȯ�� ����
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

	//float �迭�� ����ȯ :  �迭�� �Ű������� �ѱ� �� �����ͷ� ����
	//-> ĳ������ �����ͷ� ó��
	operator float* () {
		return &x; //x,y,z(���)�� ���������� �پ������Ƿ� x�� �ּҰ� �����ּҰ� ��.
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