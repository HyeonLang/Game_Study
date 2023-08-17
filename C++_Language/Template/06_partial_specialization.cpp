// 06_partial_specialization.cpp
// 부분 특수화
#include <iostream>
using namespace std;

//#define 일반_함수_부분_특수화
#define 클래스_멤버_함수_부분_특수화

#ifdef 일반_함수_부분_특수화

template <class T, int size>
class StaticArray
{
public:
    T* GetArray() { return arr; }
    T& operator[](int index)
    {
        return arr[index];
    }

    void Print1()
    {
        for (int i = 0; i < size; i++)
            cout << (*this)[i] << ' ';
        cout << endl;
    }

private:
    T arr[size];
};


template <typename T, int size>
void Print2(StaticArray<T, size>& arr)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

// 부분 특수화
// - 일부 매개변수 타입에 대해서만 특수화
template <int size>
void Print2(StaticArray<char, size>& arr)
{
    for (int i = 0; i < size; i++)
        cout << arr[i];
    cout << endl;
}

#endif // 일반_함수_부분_특수화

#ifdef 클래스_멤버_함수_부분_특수화

// 클래스 멤버 함수의 부분 특수화는 상속을 통해 구현한다.
template <class T, int size>
class StaticArray_Base
{
public:
    T* GetArray() { return arr; }
    T& operator[](int index)
    {
        return arr[index];
    }

    virtual void Print1()
    {
        for (int i = 0; i < size; i++)
            cout << (*this)[i] << ' ';
        cout << endl;
    }

private:
    T arr[size];
};

template<class T, int size>
class StaticArray : public StaticArray_Base<T, size>
{

};

// 상속을 이용한 부분 특수화
template<int size>
class StaticArray<char, size> : public StaticArray_Base<char, size>
{
public:
    void Print1() override // 멤버 함수 오버라이딩
    {
        for (int i = 0; i < size; i++)
            cout << (*this)[i];
        cout << endl;
    }
};

#endif // 클래스_멤버_함수_부분_특수화


int main()
{
    StaticArray<int, 4> int4;
    int4[0] = 1;
    int4[1] = 2;
    int4[2] = 3;
    int4[3] = 4;

    //int4.Print1();
    //Print2(int4);

    StaticArray<char, 6> char6;
    char6[0] = 'H';
    char6[1] = 'E';
    char6[2] = 'L';
    char6[3] = 'L';
    char6[4] = 'O';
    char6[5] = '\0';


    //char6.Print1();
    //Print2(char6);


    return 0;
}