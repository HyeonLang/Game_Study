// 02_Encapsula.cpp
#include <iostream>

struct Data1
{
	//public: ����ü�� public�� �⺻ ���� ������
	int hp;
	int attack;
	float luck;
};

class Data2
{
	//private: class�� private�� �⺻ ���� ������
public:
	/*member function*/
	/*getter, setter : �α� üũ�� ����׽� ������*/

	// setter : ��� ������ �ʱ�ȭ/ ����
	int SetHp(int hp) { this->hp = hp; }
	int SetAttack(int attack) { this->attack = attack; }

	// getter : ��������� ���� ��� ��
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
		throw "~~~���� �߻�";
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