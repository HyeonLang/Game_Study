// 14_dynamic_memory_allocation.cpp

#include <iostream>
#include <string>

//int main() {
//	int* ptr1 = new int;	//할당
//	delete ptr1;			//해제
//
//	int num = 1;
//	int* ptr2 = new int(num);	//할당과 동시에 초기화 가능 (다이렉트(), 유니콘{})
//	delete ptr2;				//해제
//
//	// new는 할당 실패시 nullptr을 리턴하지 않음
//	// c와 같이 예외처리를 하고싶다면 (std::nothrow)를 포함하여 nullptr 리턴 가능
//	int* ptr3 = new(std::nothrow) int{7};
//	delete ptr3;
//
//	//배열 할당, 해제, 초기화
//	int* ptr4 = new(std::nothrow) int[10]{ 0,1,2,3,4,5 };
//	delete[] ptr4;
//
//	return 0;
//}

//과제 : new와 malloc의 차이를 조사하고 아래 코드의 문제점 찾아보기
//생성자와 연관이 있음 : 생성자 조사 new와 malloc의 생성자 차이에서 나오는 문제점

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
//		std::cout << "A객체가 생성됨1" << std::endl;
//	}
//
//	A(int a)
//	{
//		std::cout << "A객체가 생성됨2" << std::endl;
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