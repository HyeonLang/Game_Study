// 02_input_output_operator.cpp

#include <iostream>
using namespace std;

class Point
{
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {};

    auto Getx() const { return x; }
    auto Gety() const { return y; }

    void Print()
    {
        cout << "(" << x << ", " << y << ")" << endl;
    }

    // ostream : 출력 스트림
    friend ostream& operator<<(ostream& out, const Point p) {
        out << "(" << p.x << ", " << p.y << ")" << endl;
        return out;
    }

    // istream : 입력 스트림
    friend istream& operator>>(istream& in, Point& p) {
        in >> p.x >> p.y;
        return in;
    }

private:
    int x = 0;
    int y = 0;
};

int main()
{
    Point p1(0, 1), p2{ 5,5 };
    cout << p1 << ", " << p2 << endl;


    Point p3, p4;
    cin >> p3 >> p4;
    cout << p3 << ", " << p4 << endl;

    return 0;
}