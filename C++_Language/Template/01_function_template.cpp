// 01_function_template.cpp

/*
	Template
	- ���α׷��Ӱ� ���ϴ� Ÿ���� �־��ָ� �˸°� �ڵ带 ���ִ� Ʋ
	- int�� double���� ��ü���� �ڷ����� ������ �� �ִ� �Ϲ�(generic type)���� �����Ѵ�.
	- � ���������� ���ø��� �Ű������� �����ϸ� �����Ϸ��� �� ���������� �´� �ڵ� ����.
	- ��ü���� �������� ��� �Ϲ����� ����Ͽ� ���α׷����� �ϰ� �� : *�Ϲ�ȭ ���α׷���*
	- �پ��� �ڷ����� ������ �˰����� ������ �� ���ø��� ����ϴ� ���� �����ϴ�.
*/

#include <iostream>
using namespace std;

/*
	�����ε����� �� Ÿ�Կ� �°� ó���� �� ������ 
	���ο� Ÿ���� ���°� �ʿ��ϸ� �߰��� ����� 
	-> ���ŷӰ� �˰��� ��ü�� �������� ����� ��� �����ؾ���, ���������� �����.
*/
//int GetMax(int x, int y) { return (x > y) ? x : y; }
//double GetMax(double x, double y) { return (x > y) ? x : y; }
//short GetMax(short x, short y) { return (x > y) ? x : y; }
//char GetMax(char x, char y) { return (x > y) ? x : y; }
//long long GetMax(long long x, long long y) { return (x > y) ? x : y; }


template<typename T>	// ���ø� �Ű����� T ����
//template<class T>		// class��� ���� ����. ���� x
T GetMax(T x, T y) {	// T�� �ϳ��� �ڷ���ó�� �����Ͽ� ���
	return (x > y) ? x : y;
}

// ������ Ÿ�ӿ� template �ڷ����� ġȯ�Ͽ� �ڵ����� �ڵ带 �ۼ��Ѵ�.


class Won
{
public:
	Won(int value = 0) : value(value) {}

	bool operator > (const Won& rhs) // template �Լ��� ���� ������ �����ε�
	{
		return value > rhs.value;
	}

	friend ostream& operator << (ostream& out, const Won& won)
	{
		out << won.value;
		return out;
	}

private:
	int value = 0;
};


int main() {
	
	// <>�� ���ø� ���ڸ� �Ѱ� ���ϴ� ������ �Լ��� �ۼ��ϵ��� �����Ѵ�.
	//cout << GetMax<int>(1, 2) << endl;
	//cout << GetMax<float>(1.0f, 2.0f) << endl;
	 
	// ���� Ÿ���� ��ġ �����ָ� <>�� Ÿ���� ��������� ���������� �ʾƵ� ����
	cout << GetMax(1, 2) << endl;  
	cout << GetMax(1.0f, 2.0f) << endl;

	// ���� Ÿ���� ��ġ���� �ʾ� error
	//cout << GetMax(1, 2u) << endl;


	 // ����ڰ� ������ �ڷ����� ��� ����
	cout << GetMax(Won(6), Won(2)) << endl;

	return 0;
}