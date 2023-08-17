// 09_02_RVO_NRVO.cpp

#include<iostream>
using namespace std;

/*
   RVO - Return Value Optimization
   - 어떤 함수가 객체를 반환해야 할 경우, 필요하지 않은 임시 객체를 생성하지 않도록 최적화 하는것
   - Debug/Release에서 된다.
   - 반환 객체가 변수명을 가지지 않은 경우 최적화 된다.
   - 변수명을 가진 경우 최적화가 되지 않았지만 NRVO가 추가되어 가능하게 되었다.

   NRVO - Named Return Value Optimization
   - RVO와 같은 방식으로 최적화를 지원한다.
   - Debug에서는 최적화 x, Release에서만 최적화 o
*/

class Test
{
public:
    Test(int value)
        : value1(value)
        , value2(count++)
    {
        cout << "constructor : " << this->value1 << ", " << this->value2 << endl;
    }

    Test(const Test& rhs)
        : value1(rhs.value1)
        , value2(count++)
    {
        cout << "copy constructor : " << this->value1 << ", " << this->value2 << endl;
    }

    ~Test()
    {
        cout << "destructor : " << this->value1 << ", " << this->value2 << endl;
    }

public:
    static int count;

private:
    int value1;
    int value2;

};

int Test::count = 1;

// Debug, Release : 임시객체 생성/소멸 x 
Test MakeRVO(int value) // RVO -> 반환 객체가 이름이 없을 경우 
{
    return Test(value);
}

// Debug   : 임시객체 생성/소멸 o
// Release   : 임시객체 생성/소멸 x 
Test MakeNRVO(int value) // NRVO -> 반환 객체가 이름이 있을 경우 
{
    Test test(value);   // 임시객체가 만들어진다.
    return test;
}


int main()
{
    cout << "----RVO----" << endl;
    MakeRVO(1);

    cout << "----NRVO----" << endl;
    MakeNRVO(2);

    cout << "----end----" << endl;

    return 0;
}