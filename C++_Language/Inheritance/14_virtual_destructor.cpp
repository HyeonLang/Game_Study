// 14_virtual_destructor.cpp
// 가상 소멸자


#include<iostream>
using namespace std;

class Base
{
public:
    //1. 업 캐스팅시 파생클래스의 소멸자가 호출이 안됨
    //~Base() { cout << "~Base()" << endl; }


    //2. virtual 키워드를 사용하여 각 객체에 맞는 소멸자 호출되도록 해야함
    virtual ~Base() { cout << "~Base()" << endl; } // !! 상속할 기반 클래스는 무조건 virtual !!
};

class Derived : public Base
{
public:
    ~Derived() {
        cout << "~Derived()" << endl;
        //TODO: arr멤버 동적 해제 
    }

private:
    int* arr = nullptr; // 동적 할당 받은 멤버는 특이한 경우가 아니면 소멸자에서 해제해주어야 한다.
};


// 상속할거 같으면 소멸자에 virtual붙이자
// 상속하지 않을거면 final붙이기 

int main()
{
    //{
    //   Derived d;
    //}

    // 상위 클래스로 업 캐스팅 하게 되면 하위 클래스의 소멸자가 은닉되어
    // 소멸자가 호출이 안되는 문제가 발생한다. 여기서 하위 클래스에서 동적할당 받은
    // 멤버가 있다면 해제가 되지않아 메모리 누수가 발생한다. 따라서 virtual 키워드를 붙여
    // 가상 소멸자로 만들어 주어야 한다.
    {
        Base* base = new Derived;

        delete base; // virtual 키워드가 없으면 base 소멸자만 호출됨!!
    }

    // 클래스를 상속하지 않을거면 final키워드를 넣자.
    // 클래스를 상속할 생각이면 무조건 소멸자에 virtual 키워드를 붙이자
    // -> 소멸자가 필요없을 경우 메모리를 더 차지할 수 있지만 누수 현상을 방지하는 좋다.



    return 0;
}