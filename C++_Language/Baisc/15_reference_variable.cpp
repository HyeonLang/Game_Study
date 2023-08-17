// 15_reference_variable.cpp

/*
	����, textrpg, ����

	�ָ����� : ���� ����
*/


/*
	L-value : ���߿� �ٽ� ���� ������ ��, �޸𸮸� Ư���� �� �ִ� ��
	R-value : ���� ������ ���� �Ұ����� ��, �޸𸮸� Ư���� �� ���� ��
*/

#include <iostream>

int Test1(int& a) { return a; }; //L-v �Ű����� : ������ �Ѿ�´�. ������ �ܺο� ������ �ش�.
int Test1(int&& a) { return a; }; //R-v �Ű����� : ����(��� ��)�� �Ѿ�´�. ������ �ܺο� ������ ���� �ʴ´�.

int main() {
	//L-v = R-v
	int a = 10;

	//a : l, 15 : r
	a = 15;
	
	//& : L-value reference (����) 
	//a ==l, a�� �� ���� l
	int& l = a;
	//l�� a�� ���� �޸� ����
	//int& l = 12; // �Ұ� 
	
	
	//cout << a; : 15
	l = 20; //a�� ����Ű�� �޸� ���� 10���� ����
	//cout << a; : 20

	//���������� R-value �Է°��� : const
	const int& l1 = 10;
	//const int& l2; const�� ����� �ݵ�� �ʱ�ȭ �ؾ���. 

	//&& : R-value reference (����)
	int&& r = 10;

	return 0;
}