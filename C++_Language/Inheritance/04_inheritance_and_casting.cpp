// 04_inheritance_and_casting.cpp

/*
	Up Casting
	- 자식 클래스를 부모 클래스 형태로 참조하여 가리키는 것
	- 자식 클래스가 더 크긴 하지만 개념적으로 더 큰 개념으로 가는 것 : 암시적 형변환 가능
	- 다양한 자식 클래스를 하나의 부모 클래스 자료형으로  묶어 일괄적으로 처리 가능

	Down Casting
	- 부모 클래스 형태로 참조하던 자식 클래스의 객체를 다시 자식 클래스의 참조 형태로 가리키는 것
	- 부모 클래스에서 자식 클래스로의 변환을 암시적 형변환이 되지 않음.
*/

#include<iostream>
using namespace std;

class Snack {};

class Chitos : public Snack {};
class ChocoChip : public Snack {};
class Homerunball : public Snack {};

int main() {

	Chitos* chitos1 = new Chitos();

	Snack* chitos = new Chitos(); // 업 캐스팅 : 부모의 포인터로 동적 할당 : 자식 클래스에 상속된 부모 클래스 부분만 접근 가능
	Snack* chocochip = new ChocoChip();

	//서로 다른 자식 클래스를 공통된 부모 클래스로 묶어 사용 가능
	Snack* sneck[2] = { chitos, chocochip };

	//다운 캐스팅
	//Chitos test1 = chitos;  //암시적 형변환 불가

	//명시적 형변환으로 처리해야 한다.
	Chitos* test2 = static_cast<Chitos*>(chitos);

	return 0;
}