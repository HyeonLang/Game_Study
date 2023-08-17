// 01_arithmatic_operator.cpp

//#define case1
#define case2

#ifdef case1

#include <iostream>
using namespace std;

class Won {
public:
	Won(int value) : value(value) {} // 변환생성자

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
	과제 : 재쉬 함수 
		- 조사 정리
		- 재귀 함수를 사용하여 피보나치 수열 구현
		- 재귀 함수를 사용해 하노이탑 구현
*/


int operator+(const Won& lhs, const Won& rhs) {

	// 반환값에 적절한 생성자가 있을 시 변환 생성자를 이용하여 가능 : int를 Won class의 인스턴스로 변환 가능 
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
	int operator+(const Won& rhs) { // this는 좌항으로 해석
		return value + rhs.value;
	}
	Won operator-(const Won& rhs) {
		return value - rhs.value;
	}

	int operator*(const Won& rhs) { // this는 좌항으로 해석
		return value * rhs.value;
	}

	int operator/(const Won& rhs) { // this는 좌항으로 해석
		return value / rhs.value;
	}

	int operator%(const Won& rhs) { // this는 좌항으로 해석
		return value % rhs.value;
	}

	Won operator+=(const Won& rhs) { // this는 좌항으로 해석
		return value = value + rhs.value;
	}

	Won operator-=(const Won& rhs) { // this는 좌항으로 해석
		return value = value - rhs.value;
	}

	Won operator*=(const Won& rhs) { // this는 좌항으로 해석
		return value = value * rhs.value;
	}

	Won operator/=(const Won& rhs) { // this는 좌항으로 해석
		return value = value / rhs.value;
	}

	Won operator%=(const Won& rhs) { // this는 좌항으로 해석
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
	과제 : Won class에 연산자 오버로딩 추가
		- *, /, %
		- +=, -=, *=, /=, %=
*/