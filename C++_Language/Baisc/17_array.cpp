// 17_array.cpp

#include <iostream>
#include <array>

int main() {
	using namespace std;

	int arr1[] = { 1,2,3,4,5 };
	int arr2[]{ 1,2,3,4,5 };
	//int arr3[](1, 2, 3, 4, 5); // ���̷�Ʈ �ʱ�ȭ �Ұ�

	std::array<int, 5> arr4; //int 5�� ����
	std::array<int, 5> arr5{1,2,3,4,5};

	arr5[0];    //���� �ʰ� ���� ó�� ���� : ����
	arr5.at(0); //���� �ʰ� ���� ó�� ���� : ����

	return 0;
}