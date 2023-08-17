// 01_class.cpp

/*
	PP	-	Procedure Programing		- ���ν���(�Լ�) ���α׷��� -> �Լ� ���� ���� (���� ����)
	OOP	-	Object Oriented Programming	- ��ü ���� ���α׷���		-> ��ü ���� ����
*/

/*
	��ü(Object) -> class + Instance
	- class
		- ������ �������� ���� ���赵, Ȥ�� ��� ex) dna, �ؾƲ....
		- �繰�� ����� �Ӽ��� ������ ���� ��� ����(data)�� ��� �Լ�(method)�� ����� ǥ��(�߻�ȭ)

	- instance
		- class�� ���� ������� ��ü
		- class�� �ϳ����� �ϳ��� class�� ���� �پ��� instance ����.
		ex) ���赵 �ϳ��� ������ ��� ���� �� ����.
*/

/*
	��ü���� 3���

	ĸ��ȭ(Encapulation)
		- ��ü�� �Ӽ�(��� ����)�� ����(��� �Լ�)�� Ŭ������ ���°�
		- ���� �����ڸ� ���� �ܺο� �ʿ��� ���븸 ���� -> ���� ����(Information hiding)
		- �ʿ��� ������ ������ ����ϱ� ���� �Ѵ�.

	���(Inheritance)
		- ���� Ŭ������ �Ӽ��� ����� �����޴� ���� Ŭ������ ����� �Ӽ��� ����� Ȯ�尡��
		- �θ�, �ڽ� Ŭ������� �θ�

	������(Polymorphism)
		- �ϳ��� ��ü�� ���� ������ �ڷ����� ���� �� �ִ� ��.
			-> �پ��� ���·� ��ü ǥ�� ����
				- �������̵� : (��ȯ�� �Ű����� ��ġ)
					- �θ� Ŭ�������� ��ӹ��� �޼��带 �ڽ� Ŭ�������� ������ �ϴ� ��
				- �����ε�
					- ���� �̸��� ���� �޼��带 ���ڰ��� ���³� ������ �ٸ��� �Ͽ� �ٸ� ����� �����ϵ��� ���� �ϴ� ��.

*/

#include <iostream>
#include <string>

class Person {	// ���, ���赵 -> �߻�ȭ
	//ĸ��ȭ
public : //���� ������ : ���� ���� ����

	void Work() {
		std::cout << "Person" << std::endl;
	}

	void Sleep() {

	}

	//���� ����
protected: //�ڽŰ� �ڽ� Ŭ���� ������ ���ٰ���

private: // �ڽ�(Ŭ��������)�� ���ٰ���
	std::string name;
	int age;
	float height;
	float weight;

};

//���
class Worker1 : public Person {
public:
	// Person::Work �Լ��� �ڽ�Ŭ�������� ������
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
	//p.age; // main()���� ���е� ������ ���� �Ұ�
	Worker1 w;
	w.Work();

	Person* p_w = new Worker1(); // �� ĳ���� : �迭 ������ ���� �ϰ������� �����ؾ� �ϴ� �ڵ带 ���ϰ� �ۼ�
	p_w->Work(); //Person : ���� �ڷ����� �������� �Լ� ȣ��

	return 0;
}