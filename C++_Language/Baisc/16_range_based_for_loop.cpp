// 16_range_based_for_loop.cpp

#include <iostream>

int main() {
	using namespace std;

	int fibonacci[]{ 0,1,1,2,3,5,8,13,21,34,55,89 };

	//for (int i = 0; i < sizeof(fibonacci) / sizeof(int); i++)
	//	cout << fibonacci[i] << endl;


	/*
		���ӵ� �����͸� ������ �����ϴ� ��
	*/
	for (const auto& num : fibonacci) {
		cout << num << endl;
	}
	
	for (const auto& num : { 0,1,1,2,3,5,8,13,21,34,55,89 }) { //�͸� �迭
		cout << num << endl;
	}

	int* test1 = new int[10];
	//for (auto t : test1) // �����Ҵ��� �迭�� ����ϸ� ���� : ���� Ư�� ������ �ڷ����� ����

	struct Test
	{
		int arr[10] = { 0 };
		int a = 10;

		int* begin() {
			return arr; //�迭�� ���� �ּ�
		}

		int* end() {
			//return &arr[9] + 1; //������ ���� : �迭�� �� �ּ�
			return &a + 1;	//arr �� a�� ��� ��� : arr�� a�� ����ü�̹Ƿ� �޸� ������
		}
	};

	Test test2;
	for (auto t : test2)
		cout << t << endl;

	return 0;
}