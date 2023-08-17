// 17_object_slicing_and_reference_wrapper.cpp
// ��ü �����̰̽� ���� wrapper


/*
   Object Slicing - ��ü �����̽� : ū �ڷ����� ���� ���� �ڷ����� ������ �߸������� ��Ÿ�� �� �ִ�.
   - �Ļ� Ŭ����(ū �ڷ���)�� �ν��Ͻ��� ��� Ŭ����(���� �ڷ���)�� �ν��Ͻ��� ������ �� �Ͼ��.
   - �Ļ� Ŭ������ ���� ������ �սǵȴ�.
*/

#include<iostream>
#include<vector>
#include<functional> // reference_wrapper ����� ����ִ�.

using namespace std;

class Base
{
public:
	virtual void Print() { cout << "Base" << endl; }
public:
	int i = 0;
};

class Derived1 : public Base
{
public:
	virtual void Print() override { cout << "Derived1" << endl; }
public:
	int j = 1;
};

class Derived2 : public Base
{
public:
	virtual void Print() override { cout << "Derived2" << endl; }
public:
	int k = 1;
};

void DoSomething(Base b /*Base& b*/)
{
	b.Print();
}

int main()
{
	// 1. reference : ��ĳ����
	Derived1 d1;
	Base& ref1 = d1;// reference : d1�� Base ���·� ����, �޸𸮴� �����ϸ鼭 ũ�⸸ �۰� �����.
	ref1.Print();	// "Derived1" 

	// 2. copy : d1�� Base ������ ���븸 �����Ͽ� �� �޸� ����
	Base base = d1;	// copy : d1�� ���� Derived1�� ��� �����Ͱ� �߸� : object_slicing
	base.Print();	// "Base"

	// �Ű������� Ÿ���� copy, reference ���������� ���� ����� �޶���
	DoSomething(d1); //Base b / Base& b

	// 3.
	// �սǾ��� vector�� �ְ� ���� �� 
	Derived1 derived1;
	Derived1 derived2;
	Derived2 derived3;
	Derived2 derived4;

	// copy ���¶� ������ ����
	//vector<Base> my_vec;

	// -> �����ϴ� ���·� ����
	// * ��� 
	vector<Base*> my_vec1; // �����迭�� vector������ ��������� ���� �ȵ�.

	my_vec1.push_back(&derived1);
	my_vec1.push_back(&derived2);
	my_vec1.push_back(&derived3);
	my_vec1.push_back(&derived4);

	for (auto& vec : my_vec1)
		vec->Print();

	// &�� ���Ϳ� �ȵ� -> ��������� reference_wrapper�� �����͸� �������
	// reference_wrapper ��� : ���ø� Ŭ����

	vector<reference_wrapper<Base>> my_vec2;

	my_vec2.push_back(derived1);
	my_vec2.push_back(derived2);
	my_vec2.push_back(derived3);
	my_vec2.push_back(derived4);

	for (auto& vec : my_vec2)
		vec.get().Print(); //get()

	return 0;
}