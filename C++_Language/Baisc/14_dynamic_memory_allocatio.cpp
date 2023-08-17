// 14_dynamic_memory_allocation.cpp

#include <iostream>
#include <string>

//int main() {
//	int* ptr1 = new int;	//�Ҵ�
//	delete ptr1;			//����
//
//	int num = 1;
//	int* ptr2 = new int(num);	//�Ҵ�� ���ÿ� �ʱ�ȭ ���� (���̷�Ʈ(), ������{})
//	delete ptr2;				//����
//
//	// new�� �Ҵ� ���н� nullptr�� �������� ����
//	// c�� ���� ����ó���� �ϰ�ʹٸ� (std::nothrow)�� �����Ͽ� nullptr ���� ����
//	int* ptr3 = new(std::nothrow) int{7};
//	delete ptr3;
//
//	//�迭 �Ҵ�, ����, �ʱ�ȭ
//	int* ptr4 = new(std::nothrow) int[10]{ 0,1,2,3,4,5 };
//	delete[] ptr4;
//
//	return 0;
//}

//���� : new�� malloc�� ���̸� �����ϰ� �Ʒ� �ڵ��� ������ ã�ƺ���
//�����ڿ� ������ ���� : ������ ���� new�� malloc�� ������ ���̿��� ������ ������

struct Test
{
	int a;
	int b;
	std::string str;
};

int main()
{
	//Test* test = new Test;
	Test* test = (Test*)malloc(sizeof(Test));

	test->a = 10;
	test->b = 20;
	test->str = "Hello!!";

	std::cout << test->a << std::endl;
	std::cout << test->b << std::endl;
	std::cout << test->str << std::endl;

	return 0;
}

//struct A
//{
//	A()
//	{
//		std::cout << "A��ü�� ������1" << std::endl;
//	}
//
//	A(int a)
//	{
//		std::cout << "A��ü�� ������2" << std::endl;
//	}
//
//	int a;
//};
//
//
//int main()
//{
//	//A* a1 = new A;
//	A* a2 = (A*)malloc(sizeof(A));
//
//	return 0;