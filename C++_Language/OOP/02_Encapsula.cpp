// 02_Encapsula.cpp
#include <iostream>

struct Data1
{
	//public: 구조체는 public이 기본 접근 지정자
	int hp;
	int attack;
	float luck;
};

class Data2
{
	//private: class는 private가 기본 접근 지정자
public:
	/*member function*/
	/*getter, setter : 로그 체크나 디버그시 편리해짐*/

	// setter : 멤버 변수를 초기화/ 수정
	int SetHp(int hp) { this->hp = hp; }
	int SetAttack(int attack) { this->attack = attack; }

	// getter : 멤버변수의 값을 얻는 것
	int GetHp() { return hp; }
	int GetAttack() { return attack; }
private:
	/*member variable*/
	int hp;
	int attack;
	float luck;
};

void T() {
	if (true)
		throw "~~~문제 발생";
}

int main() {
	Data1 d1;
	Data2 d2;

	try {
		T();
	}
	catch (const char* s) {
		std::cout << s;
	}
	

	return 0;
}