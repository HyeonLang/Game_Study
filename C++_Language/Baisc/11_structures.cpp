// 11_structures.cpp

#include <iostream>

struct Person {
	/*
		����Լ��� �ڵ� ������ �Ҵ�Ǿ� ����ü ���� ũ�ÿ� ���� ��������.
		�� ���� Person ��ü �����ÿ��� ��� �Լ��� �ϳ��� �����Ͽ� ��� ��ü�� �����ؼ� ���

		�׷��⿡ ��� �Լ��� ȣ���� ��ü�� �����ϱ� ���ؼ� �ش� ��� �Լ��� ȣ����
		��ü�� �����͸� �Ѱܹ޴� �������� ��ü ����
		�� �̷��� ������� �Լ��� ȣ���ϴ� ���� thiscall ��� �̶�� �Ѵ�.
		
		thiscall�� ��� �Լ��� ȣ���ϴ� ��ü�� �����Ͱ� �ʿ��ϱ� ������ ��ü ���� ȣ�� �Ұ��ϴ�.

		//���� : �Լ� ȣ�� �Ծ� (function calling convension) ����
	*/
	void Print(/* Persin* this */) {
		std::cout << this->name << "�� ���̴� " << age << "�Դϴ�." << std::endl;
	}

	int age;
	float weight;
	std::string name;
};

int main() {
	Person p1{ 10, 50.0f, "DIDI" };
	Person p2{ 15, 55.0f, "TITI" };

	p1.age = 15; //�⺻�� ���� ����
	p2.age;

	p1.Print(/* &p1 */);
	p2.Print();
	


	return 0;
}