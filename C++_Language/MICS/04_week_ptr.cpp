// 04_week_ptr.cpp

/*
   strong reference vs weak reference
    - strong reference : 메모리 해제에 영향을 미치는 참조, shared_ptr가 포인터를 참조할 때 증가한다.
    - weak reference   : 메모리 해제에 영향을 주지 않는 참조, weak_ptr가 포인터를 참조할 때 증가한다.

   weak_ptr
      - 다른 두 스마트 포인터와 달리 단독으로 사용하지 못하는 스마트 포인터, shared_ptr와 같이 사용.
      - shared_ptr의 순환 의존성 문제를 해결하기위해 사용한다.
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Person
{
public:
    Person(const string& name) : name(name)
    {
        cout << name << " created" << endl;
    }
    ~Person()
    {
        cout << name << " destroyed" << endl;
    }

    const string& GetName() const { return name; }

    friend bool PartnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
    {
        if (!p1 == true || !p2 == true)
            return false;

        p1->partner = p2; // 강한 참조 + 1
        p2->partner = p1; // 강한 참조 + 1

        cout << p1->name << " is partnered with " << p2->name << endl;

        return true;

    }

private:
    std::string name;

    // 동적 할당 된 객체가 서로를 shared_ptr 형태로 가리키면 순환 의존성 문제가 발생할 수 있다.
    std::shared_ptr<Person> partner;

    // weak_ptr 형태로 소유하여 문제 해결가능 -> 공유 받기는 하지만 메모리해제에 영향 X
    //std::weak_ptr<Person> partner;
};

class Test : public Person
{
public:
    Test(const std::string& name)
        : Person(name)
    {}
};

int main() {
    
    /*
        circular dependency issuses : 순환 의존성 문제
    
        서로가 서로를 참조하는 상황에서 카운팅이 서로에게 물려있어,
        서로 지워지길 기다리고 있기 때문에 카운팅이 되지 않고 대기하고 있음 (메모리가 삭제가 되지 않고 머뭄)
    */
    {
        // 할당된 Lucy 객체를 스마트 포인터 lucy가 소유 : 강한 참조 0 -> 1
        auto lucy = std::make_shared<Person>("Lucy");

        // 할당된 Ricky 객체를 스마트 포인터 ricky가 소유 : 강한 참조 0 -> 1
        auto ricky = std::make_shared<Person>("Ricky");
        
        // shared_ptr<Person> partner : 함수 내부에서 강한 참조만 각각 증가하므로 지역에서 소멸되지 않는다.
        // 동적 메모리 Lucy에서 Ricky를 shared_ptr 형태로 공유 받음
        // 동적 메모리 Ricky에서 Lucy를 shared_ptr 형태로 공유 받음
        // -> 각각의 강한 참조 카운트 1 -> 2  
        PartnerUp(lucy, ricky); 

        // weak_ptr<Person> partner   : 함수 내부에서 약한 참조만 각각 증가하므로 지역에서 소멸된다. 약한 참조는 메모리에 영향 X


    }/* 스마트 포인터 lucy, ricky 소멸 -> 각각의 카운트 감소 2 -> 1

      하지만 동적 할당된 객체 Lucy, Ricky가 멤버 변수로 서로를 shared_ptr 형태로 가지고 있음 

       1. Lucy가 소멸하기 위해 Ricky가 가진 스마트 포인터가 소멸해야함. 
       2. Ricky가 가진 스마트 포인터가 소멸되기 위해서는 Lucy가 소멸해야함.
       3. Ricky가 소멸하기 위해 Lucy가 가진 스마트 포인터가 소멸해야함.
       4. Lucy가 가진 스마트 포인터가 소멸되기 위해서는 Ricky가 소멸해야함.
       -> 1. 부터 반복

       서로가 원형으로 가지고 있다해서 순환 의존성 문제라고 부른다.
       -> 서로를 소유할 때 weak_ptr형태로 소유하여 문제 해결 가능
     */


     // weak_ptr 사용법
    {
        auto test = std::make_shared<Person>("Test");
        std::weak_ptr<Person> weak = test;

        cout << endl << "------------테스트선------------" << endl;

        // 둘다 같은 표현 : 자신만 nullptr로 바꾼다.
        test.reset();
        //test = nullptr;

        // expired() : weak_ptr이 참조한 포인터의 소멸 여부 확인, 소멸시 ture 반환
        if (weak.expired() != true)
            cout << "유효함" << endl;
        else
            cout << "유효하지 않음" << endl;

        cout << "------------테스트선------------" << endl;


        // weak_ptr 형태로는 바로 사용하지 못하고 shared_ptr로 바꾸어서 사용해야한다.
        // -> 왜냐하면 멀티 스레드 환경에서 weak_ptr을 사용해야 할 때 먼저 shared_ptr가 전부 해제될수도있기 때문에 
        // weak_ptr이 참조한 데이터가 소멸하는것을 막기위해 사용전에 최소 1의 강한 참조 횟수를 확보하기 위함이다.

        //weak-> // error
        weak.lock()->GetName(); // ok //lock() : 약한 참조(weak_ptr)을 강한 참조(shared_ptr) 형태로 바꾸어준다.
    }


    // 추가적인 스마트 포인터 사용법 + 주의점
    {
        auto test1 = std::make_shared<Person>("Test1");

        auto test2 = std::make_shared<Person>("Test2");

        //1. 스마트 포인터 끼리 스왑 가능
        test1.swap(test2);

        //2. 해당 스마트 포인터의 dull 포인터 비우기, 해당 스마트 포인터의 참조만 지워준다.
        //  -> 해당 포인터를 참조하는 모든 스마트 포인터에서 해제해주는것 x
        test1.reset();

        //3. 스마트 포인터의 캐스팅 


        //3-1. dull 포인터의 캐스팅.

        // 업캐스팅은 암시적 형변환 가능
        Person* test3 = new Test("Test3");

        // 다운캐스팅은 암시적 형변환 x, 명시적 형변환을 해주어야 한다.
        //Test* test4 = test3; //error
        Test* test4 = static_cast<Test*>(test3); //static cast를 써야함.


        //3-2 스마트 포인터의 캐스팅

        // 스마트 포인터도 업캐스팅 암시적 형변환 가능
        std::shared_ptr<Person> parent = std::make_shared<Test>("Test");

        // 스마트 포인터도 다운캐스팅은 암시적 형변환 x, 명시적 형변환을 해주어야 한다.
        //std::shared_ptr<Test> child = parent; // error
        std::shared_ptr<Test> child = std::static_pointer_cast<Test>(parent); // 스마트 포인터끼리의 명시적 형변환은 static_pointer_cast를 사용한다.

        //4. 스마트 포인터의 dull 포인터 유효 여부 확인법

        cout << endl << "------------테스트선------------" << endl;


        auto test5 = std::make_shared<Test>("Test5");
        auto test6 = test5;

        // 둘다 같은 표현
        //test5.reset();
        //test5 = nullptr;

        cout << test5 << endl;
        cout << test5.get() << endl;

        if (test5 != nullptr)
            cout << "유효함" << endl;
        else
            cout << "유효하지 않음" << endl;

        if (!test5 == false)
            cout << "유효함" << endl;
        else
            cout << "유효하지 않음" << endl;

        cout << "------------테스트선------------" << endl;
    }

    return 0;
}