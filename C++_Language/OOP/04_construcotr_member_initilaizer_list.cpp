// 04_constructor_member_initializer_list.cpp

#include<iostream>
using namespace std;

class Data
{
public:
	Data(int a, int b, int c)
		// 멤버 초기화 리스트를 사용해 생성과 동시에 값을 넣어줄 수 있다.
		: a(a)
		, b{b}
		, c(this->a - c)
		, d(c)
	{
		// 이미 a,b,c 메모리가 만들어진 상태로 실행되어
		// const 멤버 변수는 수정이 안됨
		//this->a = a;
		//this->b = b;
		//this->c = c;
	}

private:
	const int a = 10;
	const int b = 10;
	const int c = 10;
	int& d;
};

int main()
{
	Data d(10, 20, 30);

	return 0;
}