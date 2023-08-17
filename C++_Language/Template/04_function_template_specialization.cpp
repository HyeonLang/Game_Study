// 04_function_template_specialization.cpp

#include <iostream>
using namespace std;

template<typename T>
T GetMAX(T x, T y)
{
	return (x > y) ? x : y;
}

template<> // 특수화 하고싶은 템플릿 매개변수만 지워준다.
char GetMAX(char x, char y) // 지워준 템플릿 매개변수에 특수화 할 자료형을 넣어준다.
{
	cout << "경고 : 문자끼리 비교중" << endl;
	return (x > y) ? x : y;
}


template <class T>
class Storage
{
public:
	Storage(T value)
		:value(value)
	{}

	void Print()
	{
		cout << value << endl;
	}

private:
	T value;
};

template <>
void Storage<double>::Print() // 멤버 함수만 특수화 (T가 double일 때)
{
	cout << scientific << value << endl;
}



int main() 
{
	cout << GetMAX<int>(1u, 2) << endl;
	cout << GetMAX<float>(2.0f, 4.0f) << endl;
	cout << GetMAX<char>('a', 'b') << endl << endl;

	Storage<int> s1(10);
	s1.Print();

	Storage<double> s2(10.123);
	s2.Print();


	return 0;
}