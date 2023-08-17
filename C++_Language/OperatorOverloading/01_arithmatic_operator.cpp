// 01_arithmatic_operator.cpp

//#define case1
#define case2

#ifdef case1

#include <iostream>
using namespace std;

class Won {
public:
	Won(int value) : value(value) {} // ��ȯ������

	int GetValue() const
	{
		return value;
	}

private:
	int value;
	
	friend int operator+(const Won& lhs, const Won& rhs);

	friend Won operator-(const Won& lhs, const Won& rhs) {
		return lhs.value - rhs.value;
	}

};

/*
	���� : �罬 �Լ� 
		- ���� ����
		- ��� �Լ��� ����Ͽ� �Ǻ���ġ ���� ����
		- ��� �Լ��� ����� �ϳ���ž ����
*/


int operator+(const Won& lhs, const Won& rhs) {

	// ��ȯ���� ������ �����ڰ� ���� �� ��ȯ �����ڸ� �̿��Ͽ� ���� : int�� Won class�� �ν��Ͻ��� ��ȯ ���� 
	return lhs.value + rhs.value;
}

int main() {
	Won l(10), r(20);

	int r1 = l + r;

	cout << r1 << endl;

	cout << (l - r).GetValue() << endl;

	return 0;
}
#endif


#ifdef case2

#include <iostream>
using namespace std;

class Won {
public:
	Won(int value) : value(value) {} 

	int GetValue() const
	{
		return value;
	}

	// l + r -> l.operator+(r)
	int operator+(const Won& rhs) { // this�� �������� �ؼ�
		return value + rhs.value;
	}
	Won operator-(const Won& rhs) {
		return value - rhs.value;
	}

	int operator*(const Won& rhs) { // this�� �������� �ؼ�
		return value * rhs.value;
	}

	int operator/(const Won& rhs) { // this�� �������� �ؼ�
		return value / rhs.value;
	}

	int operator%(const Won& rhs) { // this�� �������� �ؼ�
		return value % rhs.value;
	}

	Won operator+=(const Won& rhs) { // this�� �������� �ؼ�
		return value = value + rhs.value;
	}

	Won operator-=(const Won& rhs) { // this�� �������� �ؼ�
		return value = value - rhs.value;
	}

	Won operator*=(const Won& rhs) { // this�� �������� �ؼ�
		return value = value * rhs.value;
	}

	Won operator/=(const Won& rhs) { // this�� �������� �ؼ�
		return value = value / rhs.value;
	}

	Won operator%=(const Won& rhs) { // this�� �������� �ؼ�
		return value = value % rhs.value;
	}

private:
	int value;
};

int main() {
	Won l(10), r(20);

	l.operator+(r);

	int r1 = l + r;

	//cout << r1 << endl;

	//cout << (l - r).GetValue() << endl;
	l += r;
	cout << l.GetValue() << endl;

	return 0;
}
#endif

/*
	���� : Won class�� ������ �����ε� �߰�
		- *, /, %
		- +=, -=, *=, /=, %=
*/