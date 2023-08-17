// 03_template_and_non_type_parameter.cpp
// ���ø��� �ڷ����� �ƴ� �Ű�����

#include <iostream>
#include <array>
using namespace std;

/*
	non-type parameter : �ڷ����� �ƴ� ���ø� �Ű�����
	- �ڷ����� �ƴ� ������� �־��ش�
*/

template<class T, unsigned int SIZE> // non_type_parameter
class MyArray {
public:
	MyArray() = default;
	~MyArray() = default;
private:
	T arr1[10];
	T arr2[SIZE]; // ���ø� ��üȭ ����(������ Ÿ��) �� SIZE�� ��ũ�� ���ó�� ����
};

int main() {
	array<int, 10> stl_arr; // 10 : non_type_parameter (���� �ȵ�)

	MyArray<int, 10> arr1;
	MyArray<double, 10> arr2;

}
