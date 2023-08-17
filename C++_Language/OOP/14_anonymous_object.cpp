// 14_anonymous_object.cpp

#include<iostream>
using namespace std;

class A
{
public:
    void print()
    {
        cout << "print" << endl;
    }
};

int main()
{
    // 멤버 함수를 호출하기 위해 인스턴스를 만듬 
    // -> 굳이 인스턴스를 변수로 선언해서 만들지않고 간단하게 멤버 함수를 호출하고싶다면?
    A a;
    a.print();

    // **익명 객체를 사용하면 좀더 편하게 사용가능**
    A().print(); // (기본생성자)생성되고 함수 실행후 사라짐

    return 0;
}