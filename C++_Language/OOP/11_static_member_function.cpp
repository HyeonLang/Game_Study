// 11_static_member_function.cpp

/*
	static member function
	- 클래스의 객체를 생성하지 않고도 호출가능한 함수
	- 객체가 없으므로 this포인터 사용이 안되기 때문에 정적 멤버 변수만 사용 가능
	- const함수로 만들 수 없다. -> this 포인터가 없기 때문에
*/


#include<iostream>
#include<functional>
using namespace std;

class Test
{
public:
	void Temp1() {
		this->value1; 
		value2;
	}

	static void Temp2(){
		// thiscall 방식이 아니기 때문에 this 포인터 사용이 안됨
		// 클래스에 포함된 일반 함수라 생각하면 된다.
		//this->value1; 
		value2;
	}

private:
	int value1;
	static int value2;

public:
	int test;
};


int main()
{
	Test t1;

	// 일반 함수는 호출시 인스턴스가 필요함
	//Test::Temp1();

	t1.Temp1();

	Test::Temp2();
	t1.Temp2();

	// thiscall이라 일반 함수 포인터 형식과 다름
	//void (*ptr1)() = Test::Temp1;

	// 일반 함수 형식과 일치함
	void (*ptr2)() = Test::Temp2;

	/*
		멤버 포인터
			- 특정 클래스에 속한 멤버를 가리키는 포인터
			- 멤버 포인터를 사용해 멤버 함수를 넣을 수 있다.
			- 특정 인스턴스화된 멤버의 위치가 아닌 멤버가 클래스에
			존재하는 위치를 가지기 때문에 사용하기 위해선 실체를 넣어줘야한다.
			- 주소에 접근할 때 (.*) 연산자를 사용한다.

			- 기본 포인터 형식에서 네임 스페이스를 추가해주면 된다.
			멤버 변수 포인터
			자료형 클래스이름::*포인터이름 = &클래스이름::변수이름

		멤버 함수 포인터
		반환값 (클래스이름::*함수포인터이름) = &클래스이름::함수이름;
	*/

	int Test::* ptr3 = &Test::test;
	t1.*ptr3 = 10;

	void (Test:: *ptr4)() = Test::Temp1;
	(t1.*ptr4)();

	//<functional> 헤더 추가해야함
	std::function<void(Test)> fp = Test::Temp1;
	fp(t1);

	return 0;
}