#pragma once
// 02_student.h

// 전방선언만으로는 모든 것을 알 수 없음 -> 존재유무만 확인 가능
// class Person;

/*
	파생클래스가 상속을 받기 위해서는 기반 클래스의 구체적인 정보를 알아랴 한다.
	그렇기에 전방선언만으로는 내용을 알 수 없어 상속 불가.
	따라서 상속을 받기 위해서는 기반클래스가 위치한 헤더파일을 포함시켜야 한다.
*/
#include "02_person.h"

class Student : public Person {
public:

	//Student(const std::string& name) {
	//	//: name(name)	// 상속받은 멤버는 멤버 초기화 리스트에서 값을 넣어줄 수 없다.
	//					// 생성과 동시에 초기화 되는 곳인데 이미 name이 Person생성시 존재하고 있기 때문
	//	// 생성된 후에는 가능
	//	this->name = name;
	//}

	//Student(const std::string& name) 
	//	/*
	//		기반 클래스가 생성되고 파생클래스가 생성된다.
	//		그렇기 때문에 보이진 않지만 기반 클래스의 생성자를 명시적으로 적지 않을 셩우
	//		기본생성자가 포함된다.
	//		-> 만약 부모 클래스에서 기본생성자가 없다면 에러가 난다.
	//	*/
	//	//	: Person() 
	//	: Person(name) // 기반클래스의 생성자를 명시적으로 호출 : 원하는 형태로 기반클래스 생성 가능
	//{
	//}

	// 부모의 생성자를 그대로 상속받아 사용가능 : 자식에서 딱히 할 것이 없을 경우
	using Person::Person; 

	// 멤버를 추가하여 기능을 확장
	void Study() {}


private:

};

Student s1;
Student s2("name");