// 10_conversion_constructor.cpp

#include<iostream>
#include<cassert>
using namespace std;

/*
   conversion constructor - 변환 생성자
   - 매개변수가 하나인 생성자
   - 다른 자료형이 들어오게 되면 묵시적 형변환이 일어나면서 호출이 된다.
   - 함수에서 변환 생성자가 있는 클래스의 매개변수를 값으로 받을 때 임시 객체가 생성될 수 있다.
      -> explicit키워드를 추가하여 예방가능
*/

class Fraction
{
public:
    Fraction(int num, int den)
        : numerator(num)
        , denominator(den)
    {
        cout << "constructor" << endl;
    }

    Fraction(const Fraction& other)
        : numerator(other.numerator)
        , denominator(other.denominator)
    {
        cout << "copy constructor" << endl;
    }

    Fraction(int a) // 매개변수가 딱 하나만 있으면 conversion constructor가 된다. 
        : numerator(a), denominator(1)
    {
        cout << "conversion constructor" << endl;
    }

    //explicit Fraction(int a) // explicit를 넣으면 형변환기능이 안된다. 
    //   : numerator(a), denominator(1)
    //{
    //   cout << "conversion constructor" << endl;
    //}

    friend std::ostream& operator <<(std::ostream& out, const Fraction frac)
    {
        cout << frac.numerator << " / " << frac.denominator << endl;
        return out;
    }

private:
    int numerator;
    int denominator;
};

void PrintFraction(Fraction frac)
{
    cout << frac << endl;
}

int main()
{
    Fraction frac1(10, 20); // constructor -> 디폴트아니고 그냥 우리가 만든 일반 생성자
    Fraction frac2(frac1);  // copy constructor

    // 다른 자료형이 들어와도 값을 형변환하여 생성자 호출
    Fraction frac3(1);      // 알맞은 자료형이 들어온 변환 생성자 호출
    Fraction frac4('a');    // **자료형이 다름 -> int로 형변환 -> 묵시적 형변환이 일어남**
    Fraction frac5(3.14f);  // ***형변환 되지만 자료가 잘린다. -> 자료가 잘릴 수 있으니 주의하자*** 

    PrintFraction(frac1);
    PrintFraction(frac2);

    // 변환 생성자가 있을시 인스턴스가 아닌 값으로 매개변수를 넣으면 임시객체를 만들어 함수가 호출이 된다. 
    // 편하지만 형변환 떄문에 자료가 잘려 문제가 생길 수 있다. -> 함수 호출 시 임시 객체 생성을 막고 싶다. -> explicit 사용
    PrintFraction('a');
    PrintFraction(3.14f);
    PrintFraction(100);

    return 0;
}