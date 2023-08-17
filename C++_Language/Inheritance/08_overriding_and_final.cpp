// 08_overriding_and_final.cpp

/*
	Overriding
	- 파생 클래스가 기반 클래스에게 상속받은 함수들을 파생 클래스에서 *재정의* 하는 것.

	- **리턴 타입과 매개변수 구성이 서로 일치**해야 한다.

	- 오버라이딩된 기반클래스의 함수는 가려지고 파생클래스의 함수가 호출된다.

	- 단순히 함수를 오버라이딩할 경우, 업캐스팅시 파생 클래스의 함수가 아닌 기반 클래스의 함수가 호출된다.
	그 이유는 c++컴파일러가 실제로 가리키는 객체의 자료형을 기준으로 하는게 아니라 *포인터 변수의 자료형을 기준*으로 하기 때문이다.
	*** virtual *** 키워드 사용시 해결 가능
	
	- virtual
		ㅁ 자신을 호출하는 객체의 **실제 타입**에 맞게 함수를 호출할 수 있게 해주는 키워드
		ㅁ 기반 클래스의 함수에 키워드를 추가해주면 *파생클래스에 자동으로 상속*된다.

*/

#include <iostream>
using namespace std;

class A {
public:
	// virtual 키워드가 포함된 함수 : 가상 함수
	virtual void Print(int x) { cout << "A" << endl; }
private:
	int i = 0;
};

class B : public A {
public:
	/*
		오버로딩 : 중복된 이름을 가지는 함수들을 매개변수 차이로 구분하여 다양하게 만들어 사용
		오버라이딩 : 상속받은 함수들을 재정의하여 덮어 씌우는 것

		오버라이딩은 부모의 함수를 재정의하여 사용하는 것이기 때문에 부모의 함수 형태와 일치.
	*/
	void Print(int x) override /*final*/ { cout << "B" << endl; } // 같은 함수를 overrding : 함수를 덮어 쓰기

	/*
		override - 오버라이드 키워드
		- 파생 클래스에서 오버라이딩한 함수에 붙일 수 있다.
		- 오버라이딩이 가능한 함수인지 판단해주고(맞는 형태가 있는지) 없다면 에러 발생
		- 오버라이딩이 된 함수임을 명시적으로 표시한다. -> 코드 가독성이 향상됨.
	*/
};

// final : 클래스를 상속시킬 수 없게 제한하는 키워드, 함수에 붙이면 해당 함수를 파생클래스에서 오버라이딩 하지 않게 제한
class C final : public B {
public:
	// 상속받은 메서드에 final 키워드가 존재한다면 오버라이딩 불가
	void Print(int x) override { cout << "C" << endl; }
private:
};

int main() {
	A a;
	B b;
	C c;

	a.Print(1);
	b.Print(1);
	c.Print(1);

	cout << "=================" << endl;

	//업 캐스팅
	A& ab = b; 
	A& ac = c;

	a.Print(0);
	ab.Print(0);
	ac.Print(0);

	return 0;
}