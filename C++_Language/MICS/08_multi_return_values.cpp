// 08_multi_return_values.cpp

#include<iostream>
#include<tuple>
using namespace std;

//반환값 다양하게 하기
//int float func()
//{
//   //함수는 두개를 반환할 수 없다.
//   // 구조체를 만들어 해결하는 방법도 있지만 더 간편한 방법이 있음 -> tuple
//   return 0, 0.1f; 
//}

/*
   tuple - 여러개의 데이터의 집합
*/

//1.
tuple<int, int> func1() // int, int 두개 형태 리턴
{

	return tuple<int, int>(123, 456);
}

//2
auto func2() // auto 키워드를 사용하여 간단하게 반환형 작성 가능
{
	return tuple<int, int, int>(123, 456, 789);
}

int main()
{
	//1.
	tuple<int, int> resul1 = func1();
	// get<>을 사용해 tuple의 데이터를 빼올 수 있다.
	cout << get<0>(resul1) << ", " << get<1>(resul1) << endl;

	//2.
	auto resul2 = func2();
	cout << get<0>(resul2) << ", " << get<1>(resul2) << ", " << get<2>(resul2) << endl;

	return 0;
}