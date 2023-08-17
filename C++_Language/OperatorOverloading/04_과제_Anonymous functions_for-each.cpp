// ���� : ���ٽ� ����, for each��

// 1. ���� �⺻ ���, ����
#define ����_�⺻��
#include<iostream>
#include<string>
using namespace std;

#ifdef ����_�⺻��
/*
* ���ٽ�(Anonymous functions / lambda)

	- ���� ǥ����, ���� �Լ�, �͸� �Լ� ���� �̸����� �Ҹ���.
	- �츮�� �ƴ� �Ϲ� �Լ����� �Լ� �̸��� �������� ���۸� �ִ� �Լ��� ���� �Լ�, �̸� ���� �Լ�, ���� ǥ�����̶�� �Ѵ�.

* ����(����)

	[] ( ) {  } ( )

	[ĸó] (�Ű�����) { �Լ� ���� } (ȣ������)

	ù ��° [] : ĸó
	�� ��° () : �Ű����� ���� �κ� (���� ���� - �Ű����� �ʿ� ���� ��)
	�� ��° {} : �Լ� ���� �κ�
	�� ��° () : �Լ� ȣ�� �� ���� (���� ���� - ȣ�� �ÿ��� ���)
*/

//	* ����


// �Ϲ� �Լ� ����
void sum1(int a, int b)
{
	cout << "sum1 func : " << a + b << endl;
}

int main(void) {

	//�Ϲ� �Լ� ȣ��
	sum1(10, 20);

	//���� �Լ�
	[](int a, int b)
	{
		cout << "sum2 lambda : " << a + b << endl;
	}(30, 40);

	return 0;
}

// ��°�
// sum1 func : 30
// sum2 lamda : 70


/*
	* �⺻ ���� ����

		�Ϲ����� �Լ���

				��ȯ�� �Լ��̸� (�Ű�����)
				{
				  // �Լ�����
				}

		�̷� ������ �Ǿ�������,



		���ٴ�

				[] (int a, int b) {  cout << " " << endl; } (30, 40);

				---> [] (�Ű�����) { // �Լ� ���� } (ȣ�� �� ����) ;



		�̷� ������ �Լ��� �̸��� ��ȯ���� ������ �ʴ� ������ ����� ���� �� �� �ִ�.

		��Ȯ�� ���ϸ�,

		���ٽ� : [] (�Ű�����) { // �Լ� ���� } --> ��������� ���ٽ�

		ȣ������ : �ǵ� ( ) �� ȣ������!



				���� ǥ���� ����. ��, �Լ��� ����⸸ �� ��
				[](int a, intb) {return a + b};

				���� ǥ���� ���. �� �Լ��� ����� ȣ���� ��
				[](int a, intb) {return a + b} (10, 20);


	* ���� ǥ�� 4���� ���

		�Ϲ� �Լ��� ���������� �Ű������� �ִ� ���, �Ű������� ���� ���, ��ȯ�� �ִ� ���, ��ȯ�� ���� ��� ��� ������ �����ϴ�.

			1) �Ű����� ���� ���� ǥ���� : [] { cout << " ���� ���� " << endl; };

			2) �Ű����� �ִ� ���� ǥ���� : [] (int a, int b, int c) { cout << a << b << c << endl; };

			3) �Ű����� ���� ��ȯ �ִ� ���� : [] { return 200; };

			4) �Ű����� �ְ� ��ȯ �ִ� ���� : [] (int a, int b) { return a * b; } ;

				" �̷� ������ 4������ ���� �Լ��� �����Ѵ�. "

				����) �׸��� ���� ǥ���ĵ� ���̱� ������ ������ �����ݷ��� �ٿ��־�� �Ѵ�.

		�� �װ��������� �Լ��� ȣ������ �ʾ����Ƿ� �߰�ȣ �ڿ� () �̷� ���� ���� ���� Ȯ���� �� �ְ�,

		�ռ� ���ҵ� �Ű������� �ִ� ���ٸ� ȣ���ϱ� ���ؼ��� [] (int a, int b) { return a * b; } (10, 20) ;

		�̷� ������ �� �ڿ� �Ű������� �°� ȣ��θ� �ۼ����־�� �Ѵ�.

*/
#endif // ����_�⺻��



// 2. ���� ����

#define ����_ĸ��_����
#include<iostream>
#include<string>
using namespace std;

#ifdef ����_ĸ��_����
/*

* ���� ĸ��[] ����

	[]

	- �̸� : ĸ��

	- ��� : ���� �ܺο� ���ǵǾ��ִ� ������ ����� ���� ���ο��� ����ϱ� ���ؼ� ����Ѵ�.

			��> �Ű������� �Ѱܼ� ����ϸ� ���� ������?
				: ��� ����, ����� �Ű������� ������ ���� ����, STL���� ����� ���� �Ű����� ������ ���� �� �ֱ� ������
				�̷� ��Ȳ���� ĸó�� ����϶�� ĸ�ĸ� ����� �� ������ �Ǵܵ�.

	- ĸ�� ��� (call by value /  call by reference)

	1) ���� call by value(=)

		- ���縦 �Ҷ��� �׳� ���� �̸��� ����ϸ� �ȴ�.
		- ��� �ܺ� ������ ���ؼ� ���縦 �Ϸ��� [=]���� ����ϸ� �ȴ�.

	2) ���� call by reference(&)

		- ������ �� ���� & ��ȣ�� ���δ�.
		- ��� �ܺ� ������ ���ؼ� ������ �Ϸ��� [&]��� ����ϸ� �ȴ�.
*/


int main(void) {
	int result1 = 1;
	int result2 = 2;
	int result3 = 3;
	int result4 = 4;

	// �Ϻ� ����
	cout << "1. Ư������ ����" << endl;
	[result1, result2](int a, int b) {

		cout << "result1, result2 : " << result1 << ", " << result2 << endl;
		cout << "result1 + a + b : " << result1 + a + b << endl << endl;

		// ������ �������� ���� �Ұ���
		// result1 = a + b; 
		// result2 = 99999;

	}(10, 20);



	// �Ϻ� ����
	cout << "2. Ư������ ����" << endl;

	[&result3, &result4](int a, int b) {

		// �����ؼ� ���� �� �ٲٱ� ����
		result3 = 22222;

		cout << "(����) result3 : " << result3 << endl;
		result4 = a + b;

	}(10, 20);

	cout << "(�ܺ�) result3, result4 : " << result3 << ", " << result4 << endl << endl << endl;


	/*
		��°�)

		1. Ư������ ����
		result1, result2 : 1, 2
		result1 + a + b : 31

		2. Ư������ ����
		(����) result3 : 22222
		(�ܺ�) result3, result4 : 22222, 30
	*/




	int result5 = 1;
	int result6 = 2;
	int result7 = 3;
	int result8 = 4;


	// ��ü ����
	cout << "3. ��ü ����" << endl;

	[=](int x)
	{
		cout << "result5, 6 : " << result5 << ", " << result6 << endl;
		cout << "result7, 8 : " << result7 << ", " << result8 << endl;
		cout << "�Ű����� : " << x << endl;
	}(30);


	cout << endl;


	// ��ü ����
	[&](int y)
	{
		cout << "result5, 6 : " << result5 << ", " << result6 << endl;
		cout << "result7, 8 : " << result7 << ", " << result8 << endl;
		cout << "�Ű����� : " << y << endl;

		result5 += y;
		result6 += y;
		result7 += y;
		result8 += y;
	}(99);

	cout << "result5, 6 : " << result5 << ", " << result6 << endl;
	cout << "result7, 8 : " << result7 << ", " << result8 << endl;


	/*
		��°�)

		3. ��ü ����
		result5, 6 : 1, 2
		result7, 8 : 3, 4
		�Ű����� : 30

		result5, 6 : 1, 2
		result7, 8 : 3, 4
		�Ű����� : 99
		result5, 6 : 100, 101
		result7, 8 : 102, 103

	*/

	return 0;

	/*
		[=, & ����, & ����] �̷� ������ ��ü �ܺ� ������ ���� �ϵ�, "�Ϻ�" ������ ������ ������ �� �� �ְ�,

		[&, ����, ����] ��� ������ ������ ������ ����, "�Ϻ�" ������ ����� ������ �� �� �ִ�.

		��,

		[&, &����] �̷������� ��� ���� �����ϰ� "�Ϻ�"�� �����Ϸ� �ϰų�,

		[=, ����, ����] �̷� ������ ��� ���� �����ϰ� "�Ϻ�"�� �����Ϸ��� ���� �翬�ϰԵ� ������ �߻��Ѵ�.
	*/
}
#endif // ����_ĸ��_����




// 3. ���� ������ ��Ȳ
#define ����_�ʿ�����_����
#include<iostream>
#include<string>
#include<algorithm>
#include<array>
using namespace std;

#ifdef ����_�ʿ�����_����

#define ����1

#ifndef ����1

/*
	1) ���ٿ� auto

	���� �Լ��� auto�� �̿��ؼ� Ư�� ������ �־�� �� �ִ�.

			auto func1 = [] (int a, int b) { return a * b };

	�̷� ������ �Լ��� ������ �κ��� func1 �̶�� ������ ���� �־ ������ ����Ҷ���

	fun1(10, 20); �̷������� ����� �����ϴ�.
*/

int main(void) {

	// ���� �Լ�1
	auto func1 = [](int a, int b) {return a * b; };

	cout << "func1(2, 10) : " << func1(2, 10) << endl << endl;


	// ���� �Լ�2
	int num = 20;
	auto func2 = [&num](int a) { num += a; };

	func2(100); // num = num + 100 

	cout << "num : " << num << endl;
	return 0;
}

/*
	��°�)

	func1(2, 10) : 20

	num : 120
*/
#endif // ����1


//	2) �Լ��� �ʿ��ѵ� ���� ���� �� ���� �ʰ�, �ָ� �� ��
// ex) sort �Լ� - �Լ��� �ʿ��ѵ� �̹� �ѹ� ����ϰ� ��ó���Ǵ� 1ȸ�� �Լ��� �ʿ��� �� 


bool compare(int a, int b) { return a > b; }

int main(void) {
	std::array<int, 10> arr1 = { 5, 4, 2, 1, 100, 32, 2, 4, 6, 9 };
	std::array<int, 10> arr2 = { 5, 4, 2, 1, 100, 32, 2, 4, 6, 9 };
	std::array<int, 10> arr3 = { 5, 4, 2, 1, 100, 32, 2, 4, 6, 9 };

	// 1) sort �Լ�
	sort(arr1.begin(), arr1.end());
	cout << "std::sort(arr1, arr1 + 10)" << endl;
	for (int val : arr1)
	{
		cout << val << " ";
	}
	cout << endl << endl;


	// 2) sort �Լ��� �Ϲ� �Լ� �̿�
	cout << "std::sort(arr, arr + 10, compare) : " << endl;
	sort(arr2.begin(), arr2.end(), compare);
	for (int val : arr2)
	{
		cout << val << " ";
	}
	cout << endl << endl;


	// 3) sort �Լ��� ���� �Լ� �̿�
	cout << "std::sort(arr, arr + 10, [](int a, int b) {return a > b; })" << endl;
	sort(arr3.begin(), arr3.end(), [](int a, int b) {return a > b; });
	for (int val : arr3)
	{
		cout << val << " ";
	}

	return 0;
}

/*
	��°�)

	std::sort(arr1, arr1 + 10)
	1 2 2 4 4 5 6 9 32 100

	std::sort(arr, arr + 10, compare) :
	100 32 9 6 5 4 4 2 2 1

	std::sort(arr, arr + 10, [](int a, int b) {return a > b; })
	100 32 9 6 5 4 4 2 2 1
*/

/*
	1) sort�Լ�

		����Ʈ�� ������������ ������ �ȴ�.

	2) �⺻ �Լ� �̿�

		sort() �Լ����� �� ��° ���ڿ� ���� ������ ���ϴ� �Լ��� ����. ������������ ����.

		sort(arr2.begin(), arr2.end(), compare); ���� ���� �� ��° ���ڷ� �Լ��� ���� ���� �� �� �ִ�.

		�������� �̷� ������ sort �Լ��� �̿��ؿԴµ� ���� �Լ��� �̿��ϸ� �� �� �����ϰ� ó���� �� �ִ�.

	3) ����
		sort(arr3.begin(), arr3.end(), [](int a, int b){return a > b;});

		�̷� ������ sort �Լ��� �� ��° ���ڿ� �Ϲ� �Լ� ���, ���� �Լ��� ������� ���� �� �� �ִ�.

		�̷� ������ �Լ��� �ʿ��� ���� �Լ� ��� ���� �Լ��� ����� �� �ִ�.
*/
#endif // ����_�ʿ�����_����