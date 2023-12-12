// 10_exception_handling_6.cpp

#include<iostream>
using namespace std;

class Test
{
public:
	Test() = default;

	// ¼Ò¸êÀÚ¿¡¼­´Â throw°¡ ¾ÈµÊ
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
		cout << "¤¤¤·¤«¤·¤¤¤©" << endl;
	}
	return 0;
}