// 09_typename_and_nested_dependent_type_name.cpp
// Ÿ�� �̸��� ��ø ���� Ÿ�� �̸�

#include <iostream>
#include <vector>
using namespace std;

class A
{
public:
	using my_int = int; // ��ø Ÿ��
};

template<typename T>
class B
{
public:

	/*
		���ø� ���ο��� ��ø ���� Ÿ�� �̸��� ����� �� typename�� ����ؾ� �Ѵ�.

		dependent - ���� �̸�
		- ���� <typename T>ó�� Ÿ���� ���ڷ� �޾� ����� �� T�� ���� �̸��̶�� �θ���.

		nested dependent type name - ��ø ���� Ÿ�� �̸�
		- ���� �̸��ӿ� �ٸ� Ÿ���� ���ǵ� ��쿡 ��ø ���� Ÿ�� �̸��̶�� �θ���.
			-> EX) T::my_int
	*/

	//T::my_int i;

	typename T::my_int i; // Ÿ������ ��� : ��ø ���� Ÿ�� �̸�
	
};

int main() {

	B<A> test;

	return 0;
}