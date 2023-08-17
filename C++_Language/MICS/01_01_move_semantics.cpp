// 01_01_move_semantics.cpp

/*
   스마트 포인터
   - 포인터처럼 동작하는 클래스 템플릿.
   - 허상(dangling) 포인터, 메모리 누수(memory leack)를 줄이기 위해 등장함
   - memory 헤더에 포함되어 있다.

   스마트 포인터의 종류
   - auto_ptr -> 삭제
   ->개선
   - unique_ptr
   - shared_ptr
   - weak_ptr
*/

#include <iostream>
#include <memory>
#include "01_02_resource.h"
#include "01_03_auto_ptr.h"
using namespace std;

/*
   RAII 원칙 : Resource Acquisition is initialization
   - 생성한 지역에서 삭제 하는 것
   - RAII의 원칙이 스마트 포인터에 적용되어 있음
*/

/* Early Return : 이른 반환 */
void DoSomthing1()
{
	Resource* resource = new Resource;

	//...

	// if (true) return; // early return -> 메모리 누수 발생

	if (true)
	{
		//해결법1 : 리턴하는 곳마다 해제해준다.
		//단점    : 코드가 길어지면 까먹고 안해줄 수 있음
		//        -> 신경쓰지 않아도 저절도 해제되게 만들고 싶다 -> 스마트 포인터

		delete resource;
		return;
	}

	delete resource;
}

/* fix */
void Dosomething2()
{
	// 해결법2 : 소멸자에서 해제해주기
	// 객체가 소멸하면서 소멸자가 호출된다.
    // 소멸자에 동적해제를 해주는 코드가 있어서
    // 신경 써주지 않아도 자동으로 메모리를 해제해준다.
    // -> 스마트 포인터가 이런 원리로 만들어져 있다.
	AutoPtr<Resource> resource(new Resource);

	if (true)
		return;
}


void DoSomething3(AutoPtr<Resource> temp)
{

}

int main()
{
	// 지역을 벗어날 떄 자동으로 소멸시킨다.
	{
		cout << "{" << endl;
		AutoPtr<Resource> res = new Resource; // 스마트 포인터 생성
		cout << "}" << endl;
	} // 스마트 포인터 소멸

	// 스마트 포인터 주의점
	AutoPtr<Resource> res1 = new Resource;

	// . 연산자를 통해 나오는것은 스마트 포인터의 멤버 함수이다.
	res1.Test();

	// 소유한 포인터의 멤버에 접근하기위해서는 -> 연산자를 통해 접근한다.
	//res1->


	// AutoPtr의 문제점 1
	AutoPtr<Resource> res2 = new Resource;

	// autoptr이 가진 포인터의 소유권이 넘어가 버리게 된다.
	DoSomething3(res2); // copy 매개변수이기 때문에 포인터 값이 함수로 넘어감. 즉 res2는 nullptr

	//res2-> // 소유권이 사라져 에러 발생함


	// 문제점 2 
	// autoptr은 *배열 단위*의 생성, 해제를 해주지 않는다.
	// delete만 있고 delete[]가 없음 


	// 이러한 문제가 있어 autoptr은 사용하지 않는다. -> 3가지 형태로 바뀜 - unique_ptr -shared_ptr - weak_ptr

	return 0;
}