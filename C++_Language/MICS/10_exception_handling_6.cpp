// 10_exception_handling_6.cpp

#include<iostream>
using namespace std;

class Test
{
public:
	Test() = default;

	// �Ҹ��ڿ����� throw�� �ȵ�
	~Test()
	{
		throw - 1;
	}

private:

};

int main()
{
	Test* t = new Test;

	try
	{
		delete t;
	}
	catch (...)
	{
		cout << "������������" << endl;
	}
	return 0;
}