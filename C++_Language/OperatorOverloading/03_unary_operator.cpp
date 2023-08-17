// 03_unary_operator.cpp

#include<iostream>
using namespace std;

class Won
{
public:
    Won(int value = 0) : value(value) {}

    auto Getvalue()const { return value; }

    // ���� �����ڴ� �ǿ����ڰ� �ϳ��� �ʿ��ϴ�.
    // �׷��� ������ Ŭ���� ���ο� ����쿡�� �Ű������� ����.
    // **�Ű������� ������ ����, ������ �����Ѵ�.**
    Won operator - () const
    {
        return -value; //���ϰ��� �´� �����ڰ� �ִٸ� ���������� �����ڸ� ȣ���Ͽ� �纻�� �����.
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