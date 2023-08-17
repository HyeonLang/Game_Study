// 16_virtual_base_class_and_the_diamond_problem.cpp
// 가상 기반 클래스와 다이아몬드 상속
#include<iostream>
using namespace std;

/*
   A       A
   |       |
   B       C
    \     /
      D

   class A {};
   class B : public A {};
   class C : public A {};
   class D : public B, public C {};

   B가 A를 가지고 있다.
   C가 A를 가지고 있다.
   B와 C를 가지는 D는 A를 2개 가진다.
   => D입장에서는 두 A중 어느것을 사용해야 하는지
   몰라 모호성이 발생
*/

/*
      A
     /   \
   B       C
     \   /
      D

   class A {};
   class B : virtual public A {};
   class C : virtual public A {};
   class D : public B, public C {};

   상속시 virtual 키워드를 붙여 가상 상속을 하면
   A객체가 하나만 존재하여 문제가 없다. 
   - 가상 상속시 B와 C가 A를 포인터로 가리킨다.

   다만 B와 C가 A의 요소를 다르게 가져야할때 문제가 생김
   - 따라서 최하위 클래스에서 부모의 생성자를 호출 해준다. 
*/

class PoweredDevice
{
public:
    PoweredDevice(int power) { cout << "PoweredDevice" << power << endl; }

public:
    int i;
};

class Scanner : /*virtual*/ public PoweredDevice // 가상 상속
{
public:
    Scanner(int scanner, int power)
        : PoweredDevice(power)
    {
        cout << "Scanner : " << scanner << endl;
    }
};

class Printer : /*virtual*/ public PoweredDevice // 가상 상속
{
public:
    Printer(int printer, int power)
        : PoweredDevice(power)
    {
        cout << "Printer : " << printer << endl;
    }
};

class Copier : public Scanner, public Printer
{
public:
    Copier(int scanner, int printer, int power1, int power2, int power3)
        : Scanner(scanner, power1)
        , Printer(printer, power2)
        //, PoweredDevice(power3) // 가상 상속시 다이아몬드 상속을 받는 최하위 파생 클래스는 따로 초기화 해줘야 한다. 
    {}
};

int main()
{
    Copier copier(1, 2, 3, 4, 5);

    // 일반 상속시 다른 주소 출력 -> 두개의 A객체가 생성 
    // **가상 상속시 같은 주소 출력 -> 하나의 A객체만 생성**
    cout << &copier.Scanner::PoweredDevice::i << endl;
    cout << &copier.Printer::PoweredDevice::i << endl;

    copier.i; // ambiguous, 가상 상속시 문제X

    return 0;
}

