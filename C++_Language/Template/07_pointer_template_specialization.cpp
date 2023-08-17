// 07_pointer_template_specialization.cpp

#include<iostream>
using namespace std;

// 1. 포인터 타입이 들어올 경우 Print() 함수에서 멤버 변수가 가진 주소값이 출력된다.
// -> T가 포인터 자료형이라면 특수화 하여 Print() 함수에서 주고사 가진 데이터를 출력해보자.
template <class T>
class A
{
public:
    A(const T& value)
        : value(value)
    {}

    void Print()
    {
        cout << value << endl;
    }

private:
    T value;
};


// 2. 포인터 템플릿 특수화
template <class T> // 모든 포인터 타입에 대해 특수화를 해야하기 때문에 자료형을 명시
class A<T*> // 포인터 타비에 대한 특수화
{
public:
    A(T* value)
        : value(value)
    {}

    void Print()
    {
        cout << *value << endl;
    }

private:
    T* value;
};


int main()
{
    A<int> a_int(123);
    a_int.Print();

    int temp = 456;

    A<int*> a_int_ptr(&temp);
    a_int_ptr.Print();

    return 0;
}