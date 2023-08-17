// 05_increment_decrement_operater.cpp

#include<iostream>
using namespace std;

class Number
{
public:
    Number(const int& num = 0) :num(num) {}

    // prefix
    Number& operator ++ () {
        ++num;
        return *this;
    }

    Number& operator ++ (int) { // ���� �ڷ��� : ������ �ν� : �ڷ����� ������ ������ ������ ����
        Number temp(*this);
        ++(*this);
        return temp;
    }

    friend ostream& operator << (ostream& out, const Number& number)
    {
        out << number.num;
        return out;
    }



private:
    int num;
};

int main()
{

    {
        Number num{ 0 };

        cout << ++num << endl;
        cout << num << endl;
    }

    {
        Number num{ 0 };

        cout << num++ << endl;
        cout << num << endl;
    }

    for (int i = 0; i < 100; i++) {} // 1
    for (int i = 0; i < 100; ++i) {} // 2
    return 0;
}