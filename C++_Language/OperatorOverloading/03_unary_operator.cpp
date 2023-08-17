// 03_unary_operator.cpp

#include<iostream>
using namespace std;

class Won
{
public:
    Won(int value = 0) : value(value) {}

    auto Getvalue()const { return value; }

    // 단항 연산자는 피연산자가 하나가 필요하다.
    // 그렇기 때문에 클래스 내부에 쓸경우에는 매개변수가 없다.
    // **매개변수의 개수로 이항, 단항을 구분한다.**
    Won operator - () const
    {
        return -value; //리턴값에 맞는 생성자가 있다면 내부적으로 생성자를 호출하여 사본을 만든다.
    }

    bool operator ! () const
    {
        return (value == 0) ? true : false;
    }

    friend ostream& operator << (ostream& out, const Won& won)
    {
        out << won.value;
        return out;
    }

private:
    int value;
};


int main()
{
    const Won w1(10);
    const Won w2{ 0 };

    cout << w1 << endl;
    cout << w2 << endl;

    cout << -w1 << endl;

    cout << boolalpha;
    cout << !w1 << endl;
    cout << !w2 << endl;

    return 0;
}