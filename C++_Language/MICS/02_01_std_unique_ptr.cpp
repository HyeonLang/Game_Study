// 02_01_std_unique_ptr.cpp

/*
   unique_ptr
   - 특정 개체를 *하나의 스마트 포인터만* 소유권을 가지게 하는 스마트 포인터
   - auto_ptr의 문제점을 개선한 포인터
   - unique_ptr가 소멸할때, 자신이 소유한 dull 포인터를 해제한다.
      ㅁ dull(raw) pointer : 스마트 포인터가 소유한 원시 포인터
*/

#include <iostream>
#include <memory>
#include "02_02_resource.h"
using namespace std;

void DoSomething(std::unique_ptr<Resource> res)
{
    res->SetAll(10);
    res->Print();
}

int main() 
{
    //1.
    {
        std::unique_ptr<Resource> res1(new Resource(5));

        auto res2 = make_unique<Resource>(5); // unique_ptr을 만들어 주는 함수 : 생성시점 일치를 위해

        res2->SetAll(5);
        res2->Print();

        //res2 = res1; // 유니크 해야하므로 복사 대입(L-value)이 안됨. 

        res2 = std::move(res1); // L-value를 R-value로 바꾸어 이동 대입 연산자 호출
                                // res2가 원래 가지고 있던 데이터는 삭제됨.

        // res2로 옮기는 순간 res1은 소유권을 상실하기 때문에 이동 대입 후 접근 시도시 에러
        //res1->Print(); // error
    }

    //2.
    {
        auto res1 = std::make_unique<Resource>(5);

        // 복사 생성자를 호출하므로 error 
        //DoSomething(res1); 

        // R-value 형태로 넘기면 가능.
        // -> 대신 원본의 데이터가 이동하게 된다.
        // -> 원본의 데이터의 소유권을 넘기는게 문제가 된다면 참조 형태로 받고 넘기는게 좋다.
        DoSomething(std::move(res1)); // res1는 nullptr이 됨. 

        // 스마트 포인터가 가지고 있는 실질적인 dull 포인터를 반환
        res1.get();
    }

    //3.
    {
        // dull 포인터와 스마트 포인터를 같이 사용하면 발생할 수 있는 문제점

        Resource* res = new Resource(5);

        // res가 소유한 주소를 넘겨준다. res는 스마트 포인터가 아니기 때문에 소유권을 상실하지 않는다. 
        // -> unique_ptr은 한 객체에 대하여 하나의 포인터만 존재해야하는데 두개 이상의 포인터가 소유하게 됨
        std::unique_ptr<Resource> res1(res);
        // res = nullptr; // nullptr로 초기화해주면 되긴함

        //...

        // res1과 res2가 같은 주소를 소유하게 된다.
        std::unique_ptr<Resource> res2(res);

        // 해당 지역을 벗어나면 res1과 res2 소멸 -> 둘다 자기가 소유한 res의 주소를 해제한다.
        // 같은 주소를 두번 해제하려고 시도함 -> 허상 포인터 문제가 발생
        // 때문에 dull 포인터 변수를 통해 할당하는 것은 하지 않는게 좋다.
    }

    const std::unique_ptr<Resource> res1(new Resource(5)); // 스마트 포인터를 수정하게 하지 못하기 위한 const
    std::unique_ptr<const Resource> res2(new Resource(5)); // Resource를 수정하게 하지 못하기 위한 const

    return 0;
}