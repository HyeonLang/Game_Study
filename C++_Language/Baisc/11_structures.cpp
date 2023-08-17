// 11_structures.cpp

#include <iostream>

struct Person {
	/*
		멤버함수는 코드 영역에 할당되어 구조체 변수 크시에 포함 되지않음.
		즉 여러 Person 객체 생성시에도 멤버 함수는 하나만 존재하여 모든 객체가 공유해서 사용

		그렇기에 멤버 함수를 호출한 객체를 구분하기 위해서 해당 멤버 함수를 호출한
		객체의 포인터를 넘겨받는 형식으로 객체 구별
		즉 이러한 방식으로 함수를 호출하는 것을 thiscall 방식 이라고 한다.
		
		thiscall은 멤버 함수를 호출하는 객체의 포인터가 필요하기 때문에 객체 없이 호출 불가하다.

		//과제 : 함수 호출 규약 (function calling convension) 조사
	*/
	void Print(/* Persin* this */) {
		std::cout << this->name << "의 나이는 " << age << "입니다." << std::endl;
	}

	int age;
	float weight;
	std::string name;
};

int main() {
	Person p1{ 10, 50.0f, "DIDI" };
	Person p2{ 15, 55.0f, "TITI" };

	p1.age = 15; //기본값 예약 가능
	p2.age;

	p1.Print(/* &p1 */);
	p2.Print();
	


	return 0;
}