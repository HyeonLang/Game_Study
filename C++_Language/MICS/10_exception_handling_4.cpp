// 10_exception_handling_4.cpp

// std_exception.cpp

#include<iostream>
//1.
// _3���� ���� ó���� Ŭ������ ��������� �̹� std���� ������ 
#include<exception>
#include<string>
using namespace std;

//2.
// �̹� ���ǵ� Ŭ������ ��ӹ޾� �츮�� ���ϴ� ���·� thorw����
class customException : public std::exception
{
public:
	// c++11 ���� �߰�
	// ���ܽ� ����� ������ what()�� �������̵��Ͽ� Ŀ������ �� �ִ�.
	const char* what() const noexcept override
	{
		return "Custom exception";
	}

private:

};

int main()
{
	try
	{
		//2.
		throw customException();

		string str;

		// ���ڿ��� ���̴� ������ ����.
		// -1�ϰ�� ��� �÷ο� �Ͼ�� �ִ밪�� �ȴ�.
		// ������ ���� �ñ��Ѱ� ������ cppreference.com ����
		//1.
		str.resize(-1);
	}
	//1.
	//catch (const std::length_error& exception)
	//{
	//	cout << "Length Error" << endl;
	//	cout << exception.what() << endl;
	//}
	//2.
	catch (const std::exception& exception)
	{
		cout << typeid(exception).name() << endl;
		cerr << exception.what() << endl;
	}

	return 0;
}