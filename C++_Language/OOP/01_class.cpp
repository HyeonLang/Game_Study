// 01_class.cpp

/*
	PP	-	Procedure Programing		- 프로시저(함수) 프로그래밍 -> 함수 단위 실행 (절차 지향)
	OOP	-	Object Oriented Programming	- 객체 지향 프로그래밍		-> 객체 단위 실행
*/

/*
	객체(Object) -> class + Instance
	- class
		- 무엇을 만들지에 대한 설계도, 혹은 상상 ex) dna, 붕어빵틀....
		- 사물의 공통된 속성과 동작을 각각 멤버 변수(data)와 멤버 함수(method)로 만들어 표현(추상화)

	- instance
		- class를 통해 만들어진 실체
		- class는 하나지만 하나의 class를 통해 다양한 instance 존재.
		ex) 설계도 하나면 물건을 계속 만들 수 있음.
*/

/*
	객체지향 3요소

	캡슐화(Encapulation)
		- 객체의 속성(멤버 변수)과 동작(멤버 함수)을 클래스로 묶는것
		- 접근 지정자를 통해 외부에 필요한 내용만 공개 -> 정보 은닉(Information hiding)
		- 필요한 정보만 공개해 사용하기 쉽게 한다.

	상속(Inheritance)
		- 상위 클래스의 속성과 기능을 물려받는 하위 클래스를 만들어 속성과 기능을 확장가능
		- 부모, 자식 클래스라고도 부름

	다형성(Polymorphism)
		- 하나의 객체가 여러 형태의 자료형을 가질 수 있는 것.
			-> 다양한 형태로 객체 표현 가능
				- 오버라이딩 : (반환값 매개변수 일치)
					- 부모 클래스에서 상속받은 메서드를 자식 클래스에서 재정의 하는 것
				- 오버로딩
					- 같은 이름을 가진 메서드를 인자값의 형태나 개수를 다르게 하여 다른 기능을 수행하도록 정의 하는 것.

*/

#include <iostream>
#include <string>

class Person {	// 상상, 설계도 -> 추상화
	//캡슐화
public : //접근 지정자 : 접근 범위 제어

	void Work() {
		std::cout << "Person" << std::endl;
	}

	void Sleep() {

	}

	//정보 은닉
protected: //자신과 자식 클래스 에서만 접근가능

private: // 자신(클래스내부)만 접근가능
	std::string name;
	int age;
	float height;
	float weight;

};

//상속
class Worker1 : public Person {
public:
	// Person::Work 함수를 자식클래스에서 재정의
	void Work() {
		std::cout << "Worker1" << std::endl;
	}
};

class Worker2 : public Person {

};

int main()
{
	Person p; // instance, object
	p.Work();
	//p.age; // main()에선 은닉된 정보에 접근 불가
	Worker1 w;
	w.Work();

	Person* p_w = new Worker1(); // 업 캐스팅 : 배열 등으로 사용시 일괄적으로 시행해야 하는 코드를 편하게 작성
	p_w->Work(); //Person : 본인 자료형을 기준으로 함수 호출

	return 0;
}