// 03_shared_ptr.cpp

/*
   shared_ptr
      - 유니크 포인터와 달리 소유권 공유가 가능한 포인터.
      - 포인터를 함수에 자주 전달해야 할 떄, 유니크 포인터 대신 사용하기 적합하다.
      - 참조 카운팅 방식을 사용한다.
         ㄴ 해당 dull포인터를 소유하고 있는 스마트 포인터의 *개수를 카운팅*하여 마지막
         스마트 포인터가 소멸할때 해제해주는 방식
*/
#include <iostream>
#include <memory>
#include "02_02_resource.h"
using namespace std;

int main()
{
    {
        // dull ptr를 받아 res1 기준으로 카운트 증가 : 0 -> 1
        std::shared_ptr<Resource> res1 = std::make_shared<Resource>(5);

        res1->SetAll(2);
        res1->Print();

        cout << "Count : " << res1.use_count() << endl;
        
        {
            // res2가 res1이 가리키는 주소를 받아 카운트 증가 : 1 -> 2
            auto res2(res1);

            res2->SetAll(3);
            res2->Print();

            cout << "Count : " << res1.use_count() << endl; // res2.use_count() 여도 상관 없음.
        } // res2 소멸로 카운트 감소 : 2 -> 1 , 아직 dull ptr를 소유한 스마트 포인터가 있어 메모리 해제는 하지 않음.

        cout << "Count : " << res1.use_count() << endl;
    } // res1 소멸로 카운트 증가 : 1 -> 0, dull ptr을 소유한 마지막 스마트 포인터가 소멸하여 메모리를 해제한다.



    // shared_ptr를 사용할때 주의점
    Resource* ptr = new Resource(10);

    {

        // dull 포인터를 받아 res1를 기준으로 카운트 0 -> 1 증가
        std::shared_ptr<Resource> res1(ptr);

        res1->SetAll(2);
        res1->Print();
        cout << "Count : " << res1.use_count() << endl;

        {
            // dull 포인터를 받아 res2를 기준으로 카운트 0 -> 1 증가
            // dull 포인터 형태로 받았으므로 res1과 연관이 없어 카운트를 따로 가지게 된다.
            std::shared_ptr<Resource> res2(ptr);


            res2->SetAll(3);
            res2->Print();
            // res1과 연관이 없으므로 count : 1 출력
            cout << "Count : " << res2.use_count() << endl;

        } // res2 소멸, res2 기준으로 카운트 감소 1 -> 0, 마지막 스마트 포인터 소멸하여 소유한 dull pointer 해제


        cout << "Count : " << res1.use_count() << endl;

        system("pause");
    } // res1 소멸, res1 기준으로카운트 감소 0 -> 1, 마지막 스마트 포인터 소멸하여 소유한 dull pointer 해제 
    // 하지만 res2에서 먼저 해당 포인터를 해제하였으므로 -> 허상포인터 문제 발생 -> *error*

    return 0;
}