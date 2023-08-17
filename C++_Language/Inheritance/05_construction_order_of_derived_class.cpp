//05_construction_order_of_derived_class.cpp


#include<iostream>
using namespace std;

class Parent
{
public:
    Parent()
        : a(10)
    {
        cout << "Base constructor" << endl;
    }

private:
    int a;
};

class Child : public Parent
{
public:
    Child()
        : /*Parent()*/b(10.0)  // 보이지 않지만 기본 클래스의 생성자가 있다. -> 생성자가 아니라 초기화 방식을 정하는 것이다. -> {}도 가능
    {                          // 디버깅 해보면 파생 클래스 생성자 보다 기본 클래스의 생성자가 먼저 호출된다.
                               // 초기화 리스트에서  기반 클래스 생성자를 어느 위치에 적어도 기반 클래스 생성자가 먼저 호출
        cout << "Derived constructor" << endl;
    }

private:
    double b;
};

// 이럴경우 D 클래스 객체 생성시 타고 올라가서 전부 호출됨 
class A { public: A() { cout << "A constructor" << endl; } };
class B : public A { public: B() { cout << "B constructor" << endl; } };
class C : public B { public: C() { cout << "C constructor" << endl; } };
class D : public C { public: D() { cout << "D constructor" << endl; } };

int main() {
    // 상속받은 기반 클래스의 생성자 우선 호출
    Child child;

    cout << "#################" << endl;
    D d;

    return 0;
}