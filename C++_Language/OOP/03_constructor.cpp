// 03_constructor.cpp

#include<iostream>
#include<utility>

using namespace std;

class Fraction
{
public:
    Fraction(int n, int d)
    {
        numerator = n;
        denominator = d;
        cout << "constructor!!" << endl;
    }

    /*
       - default constructor - 기본 생성자
          ㅁ 생성자를 하나도 선언하지 않을경우 기본적으로 제공되는 생성자
          ㅁ 생성자를 하나 정의했을 경우 제공되지 않음

       - copy constructor - 복사 생성자
          ㅁ 자신과 같은 타입의 클래스를 & 형태로 받아 생성되는 경우 호출
          ㅁ 보통 재정의할 경우 외부에 존재하는 원본의 값을 복사하여 사본을 만들려고할때 사용한다.
          ㅁ 얕은 복사와 깊은 복사가 있다.

       - move constructor - 이동 생성자
          ㅁ 자신과 같은 타입의 클래스를 && 형태로 받는경우 호출
          ㅁ 재정의할 경우 원본 자체의 값을 대입하여 값자체를 이동시키려고할때 사용한다.
    */

    //Fraction(){}                  // 기본 생성자
    //Fraction(const Fraction&){}      // 복사 생성자
    //Fraction(Fraction&&){}         // 이동 생성자

    Fraction()
    {
        cout << "default constructor!!" << endl;
    }

    Fraction(const Fraction& frac)
    {
        cout << "copy constructor!!" << endl;
    }

    Fraction(Fraction&& frac) noexcept
    {
        cout << "move constructor!!" << endl;
    }

private:
    int numerator = 10;
    int denominator = 10;
};

class IntArray
{
public:
    IntArray(const int& in_length)
    {
        length = in_length;
        arr = new int[length];
        cout << "constructor!!" << endl;
    }

    ~IntArray()
    {
        delete[] arr;
        cout << "destructor!!" << endl;
    }

private:
    int* arr = nullptr;
    int length = 0;
};

int main()
{
    //Fraction f1();

    //Fraction f1;
    //Fraction f2(10, 20);


    Fraction d;

    Fraction c(d);

    Fraction m(std::move(d));

    {
        while (true)
        {
            IntArray my_arr(1000);
        }

    }

    return 0;
}