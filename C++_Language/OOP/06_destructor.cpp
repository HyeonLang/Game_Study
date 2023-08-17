// 06_destructor.cpp

#include<iostream>
using namespace std;

class Test
{
public:
	Test()
	{
		cout << "constructor" << endl;
	}

	// ~ : tilde(not, 부정의 의미)
	~Test() // 소멸자
	{
		cout << "destructor" << endl;
	}

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

	{
	cout << "-------------------1" << endl;
	Test t1;
	cout << "-------------------2" << endl;
	}
	cout << "-------------------3" << endl;

	cout << "-------------------4" << endl;

	{
		while (true)
		{
			// 소멸할때 내부적으로 생성한 메모리를 해제하지 못한다면 메모리 누수 발생
			// -> 소멸할때 메모리를 해제할 것이므로 소멸자에 메모리 해제 코드를 적어주는게 안전하고 편함
			IntArray my_arr(10000);
		}
	}

	return 0;
}