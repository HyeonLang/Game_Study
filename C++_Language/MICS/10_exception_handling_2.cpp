// 10_exception_handling_2.cpp

#include<iostream>
using namespace std;

/*
	Stack Unwinding : ���� �ǰ���
	- ���ܸ� throw�� ��� ���� ���ܸ� catch�� �� ���������� ������ �ǰ��°�
*/

void first();
void second();
void third();
void last();

// exception specifier

// ��� ������ ���ܸ� throw�� �� �ִٴ� ǥ��
//void Test() throw(...);
//void Test() noexcept(false);

// int���� ���ܸ� throw�� �� �ִٴ� ǥ��
// �Ʒ��� ���� ������� noexcept(false);�� �ؼ��ϰ� 17���� ���� : �����Ϸ��� C5040 ������ ������
// �׷��� ������ ���� ���� ���·� ���°��� ��õ��
//void Test() throw(int); 

// ���ܸ� throw���� �ʰڴٴ� ǥ��
//void Test() noexcept;
//void Test() noexcept(true);

// �̰͵� ���ܸ� throw���� �ʰڴٴ� ǥ�������� ��忡 ���� �������� �������� ������
// ���� ���� ���·� ����ϴ°� ��õ�Ѵ�.
//void Test() throw(); 

int main()
{
	cout << "Start" << endl;

	try
	{
		first();
	}
	catch (char)
	{
		cerr << "main caught char exception" << endl;
	}
	catch (...)// catch-all handlers ��� ���� Ÿ���� ������ ����
	{
		cerr << "main caught elipses exception" << endl;
	}

	cout << "End main" << endl;
	return 0;

	return 0;
}

void first()
{
	cout << "first" << endl;

	try
	{
		second();
	}
	catch (int)
	{
		cerr << "first caught int exception" << endl;
	}

	cout << "End first" << endl;
}

void second()
{
	cout << "second" << endl;

	try
	{
		third();
	}
	catch (double)
	{
		cerr << "second caught int exception" << endl;
	}

	cout << "End second" << endl;
}

void third()
{
	cout << "third" << endl;

	last();

	cout << "End third" << endl;

}

void last()
{
	cout << "last" << endl;

	cout << "Throw exception" << endl;
	throw - 1;
	// throw�ϴ� ���� �Ʒ� �ڵ� ���� ���ϰ� ����
	// ������ third�� �̵�  -> catch�� ���� 
	// ������ second�� �̵� -> double���̶� ������
	// ������ first�� �̵�  -> int���̶� ����
	// ���� ó���� first���� ����
	// thorw�� �Ǵ� ���� ���ܸ� ���� �����ϱ����� �Լ��� ������ 
	// �������� �ʰ� �´� ������ catch�� ã�´�.

	cout << "End last" << endl;
}
