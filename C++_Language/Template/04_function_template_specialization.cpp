// 04_function_template_specialization.cpp

#include <iostream>
using namespace std;

template<typename T>
T GetMAX(T x, T y)
{
	return (x > y) ? x : y;
}

template<> // Ư��ȭ �ϰ���� ���ø� �Ű������� �����ش�.
char GetMAX(char x, char y) // ������ ���ø� �Ű������� Ư��ȭ �� �ڷ����� �־��ش�.
{
	cout << "��� : ���ڳ��� ����" << endl;
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
void Storage<double>::Print() // ��� �Լ��� Ư��ȭ (T�� double�� ��)
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