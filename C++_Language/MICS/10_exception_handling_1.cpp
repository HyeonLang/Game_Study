// 10_exception_handling_1.cpp
/*
	����ó��
	try, catch, throw
*/
#include<iostream>
using namespace std;



int main()
{
	double x;
	cin >> x;


	// try : ���ܰ� �߻��� �� �ִ� ������ ǥ���Ѵ�.
	try {
		// throw : ���ܸ� ������ try ������ �����.
		// �Ʒ��� catch���� ���ܸ� �޾� ó�� ���ش�.
		// ���� catch���� ���ܸ� ���� ���� ��� ���� �߻�.
		if (x < 0.0) throw - 1.0; // throw �� ���� �� try �ڵ带 �����ϰ� catch���� ����

		if (x >= 100) throw "100�̻��� ���� �Էµ�.";

		cout << sqrt(x) << endl;
	}
	// catch : throw�� ���ܸ� �޾� ó���Ѵ�.
	// throw�� *Ÿ�԰� ��ġ*�ؾ� catch�� �� �ִ�. ��ĳ������ �����ϰ� ������ ��ġ�ؾ� �Ѵ�.
	catch (double x) { // throw ����
		cerr << x << endl; // cerr : �ܼ� ���� �޼��� ���
	}
	// catch�� ������ �ۼ��Ͽ� �پ��� Ÿ������ throw�ϰ� catch�� �� �ִ�.
	// ��� �����͸� ���� ���·� �޴� ��쿡�� const �� ������� �Ѵ�.
	catch (const char* error_message) { // string => const char* : ���ڿ� ����� ������ �� ����.
		cerr << error_message << endl;
	}
	return 0;
}