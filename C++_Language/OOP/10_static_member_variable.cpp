// 10_static_member_variable.cpp

/*
	staic member variable
	- 클래스 내부에 하나만 존재하는, 클래스 모든 객체가 공유하는 변수
	- 선언을 클래스에서, 초기화는 파일 영역(cpp)에서 해주어야 중복 문제를 방지할 수 있다.
*/

#include<iostream>
using namespace std;

class Test
{
public:
	int value;

	void Add();

	/*
		정적 멤버 변수는 프로그램이 시작할때 메모리가 생성되어야 함
		그러나 class는 상상의 개념 
		-> 여기서는 그저 예약만 가능하고 생성이 되지 않는다.
		-> 실 메모리에 올라가지 않는다.
	*/
	//static int count = 10; // error
	static int count;

	// 예외적으로 const 키워드를 붙이면 가능
	static const int test1 = 10;

	static constexpr float test2 = 10.0f;
};

// 헤더 파일에서 초기화할 경우 중복문제가 발생할 수 있다.
int Test::count = 0;

int main()
{
	Test t1;
	Test t2;

	t1.count = 10;
	t1.value = 10;

	t2.count = 20;
	t2.value = 20;

	cout << &t1.value << ", " << t1.value << endl;
	cout << &t2.value << ", " << t2.value << endl;

	// 인스턴스가 존재하지 않아도 접근이 가능하다.
	cout << &Test::count << ", " << Test::count << endl;

	// 하나만 존재하기 때문에 값을 공유함 
	cout << &t1.count << ", " << t1.count << endl;
	cout << &t2.count << ", " << t2.count << endl;

	return 0;
}

/*
	과제 : 싱글톤 패턴 조사
*/