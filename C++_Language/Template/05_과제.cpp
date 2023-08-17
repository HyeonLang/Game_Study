/*
   과제 : Storage<bool>형 특수화

   아래의 클래스는 들어온 템플릿 인자에 따라 데이터를 8개 생성해주는 클래스이다.

   여기서 문제가 생기는데 bool형을 만들 시 공간을 낭비하게 된다.
   -> bool형은 1바이트 크기만으로도 8가지를 표현할 수 있지만 아래와
   같이 생성될 경우 1바이트 * 8의 크기를 가진다.

   아래의 클래스를 템플릿 특수화로 bool형일시
   1바이트를 가지고 8개의 불값을 처리할 수 있게 만들자
*/
#include <iostream>
using namespace std;

template<typename T>
class Storage8
{
public:
    void Set(int index, const T& value)
    {
        arr[index] = value;
    }

    const T& Get(int index)
    {
        return arr[index];
    }

private:
    T arr[8];
};

template<>
class Storage8<bool>
{
public:
    void Set(int index, const bool& value)
    {
        if (value == 1) {
            bool_arr = (1 << index) | bool_arr;
        }
        if (value == 0) {
            bool_arr = (~(1 << index)) & bool_arr;
        }
    }

    const bool& Get(int index)
    {
        return (bool_arr << index) & 1;
    }

private:
    char bool_arr;
};

int main() {
    Storage8<int> i;
    Storage8<bool> b;

    i.Set(5, 5);
    cout << i.Get(5) << endl;
    b.Set(0, 1);
    b.Set(0, 0);
    cout << b.Get(0) << endl;


/*
   과제 : 비트 연산자를 사용하여 아래의 문제를 해결

   2진수와, bool대수 문제, 비트연산


   1.
   int a = 123;

      a = 0;

      a = a ? a -> ?에 무슨 연산자가 들어가야 위 코드보다 빠르게 될까?

   2. swap:
   int a = 123;
   int b = 456;

   a = a ? b
   b = a ? b
   a = a ? b

   temp를 사용하지 않고 바꾸는법 찾기

   3.
      짝수/홀수 판별 -> %사용하지 않고

   4.
      음수/양수 판별 -> 관계연산자 사용 x


   5.
      2의 승수인지 아닌지 판별 -> 반복문 사용하지 않고
      연산 두번만 하면 알 수 있음

   6.
      대문자/소문자 변환 -> +, - 안쓰고
      아스키 코드의 대문자는 여섯번째 비트가 모두 0이고
      소문자는 모두 1 이다.
*/
    // 1.
    int a = 123;

    a = 0;

    a = a ^ a;

    cout << a << endl;

    // 2. swap:
    int a2 = 123;
    int b2 = 456;

    a2 = a2 ^ b2;
    b2 = a2 ^ b2;
    a2 = a2 ^ b2;

    cout << a2 << " " << b2 << endl;

    // 3. 짝수 / 홀수 판별 -> % 사용하지 않고
    int odd = 11;
    int even = 12;
    cout << (odd & 1);
    cout << endl;
    cout << (even & 1);
    cout << endl << endl;

    // 4. 음수 / 양수 판별->관계연산자 사용 x
    int minus = -121;
    int plus = 2211;
    cout << (minus & 0x80000000);
    cout << endl;
    cout << (plus & 0x80000000);
    cout << endl << endl;
    // 5.2의 승수인지 아닌지 판별->반복문 사용하지 않고, 연산 두번만 하면 알 수 있음
    int bit = 64;
    int no_bit = 20;
    cout << ((bit - 1) & bit) << endl;
    cout << ((no_bit - 1) & no_bit) << endl;


    // 6. 대문자 / 소문자 변환 -> + , -안쓰고, 아스키 코드의 대문자는 여섯번째 비트가 모두 0이고, 소문자는 모두 1 이다.
    char capital = 'A';
    char small = 'a';
    cout << char(capital ^ 32) << endl;
    cout << char(small ^ 32) << endl;

    return 0;
}


/*
   과제 : 비트 연산자를 사용하여 아래의 문제를 해결

   2진수와, bool대수 문제, 비트연산


   1.
   int a = 123;

      a = 0;

      a = a ? a -> ?에 무슨 연산자가 들어가야 위 코드보다 빠르게 될까?

   2. swap:
   int a = 123;
   int b = 456;

   a = a ? b
   b = a ? b
   a = a ? b

   temp를 사용하지 않고 바꾸는법 찾기

   3.
      짝수/홀수 판별 -> %사용하지 않고

   4.
      음수/양수 판별 -> 관계연산자 사용 x


   5.
      2의 승수인지 아닌지 판별 -> 반복문 사용하지 않고
      연산 두번만 하면 알 수 있음

   6.
      대문자/소문자 변환 -> +, - 안쓰고
      아스키 코드의 대문자는 여섯번째 비트가 모두 0이고
      소문자는 모두 1 이다.
*/
#include <iostream>
using namespace std;

int main() {
    // 1.
    int a = 123;

    a = 0;

    a = a ^ a;

    cout << a << endl;

    // 2. swap:
    int a2 = 123;
    int b2 = 456;

    a2 = a2 ^ b2;
    b2 = a2 ^ b2;
    a2 = a2 ^ b2;

    cout << a2 << " " << b2 << endl;

    // 3. 짝수 / 홀수 판별 -> % 사용하지 않고
    int odd = 11;
    int even = 12;
    cout << (odd & 1);
    cout << endl;
    cout << (even & 1);
    cout << endl << endl;

    // 4. 음수 / 양수 판별->관계연산자 사용 x
    int minus = -121;
    int plus = 2211;
    cout << (minus & 0x80000000);
    cout << endl;
    cout << (plus & 0x80000000);
    cout << endl << endl;
    // 5.2의 승수인지 아닌지 판별->반복문 사용하지 않고, 연산 두번만 하면 알 수 있음
    int bit = 64;
    int no_bit = 20;
    cout << ((bit - 1) & bit) << endl;
    cout << ((no_bit - 1) & no_bit) << endl;


    // 6. 대문자 / 소문자 변환 -> + , -안쓰고, 아스키 코드의 대문자는 여섯번째 비트가 모두 0이고, 소문자는 모두 1 이다.
    char capital = 'A';
    char small = 'a';
    cout << char(capital ^ 32) << endl;
    cout << char(small ^ 32) << endl;

    return 0;
}