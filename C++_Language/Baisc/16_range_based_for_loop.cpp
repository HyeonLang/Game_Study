// 16_range_based_for_loop.cpp

#include <iostream>

int main() {
	using namespace std;

	int fibonacci[]{ 0,1,1,2,3,5,8,13,21,34,55,89 };

	//for (int i = 0; i < sizeof(fibonacci) / sizeof(int); i++)
	//	cout << fibonacci[i] << endl;


	/*
		연속된 데이터를 끝까지 접근하는 것
	*/
	for (const auto& num : fibonacci) {
		cout << num << endl;
	}
	
	for (const auto& num : { 0,1,1,2,3,5,8,13,21,34,55,89 }) { //익명 배열
		cout << num << endl;
	}

	int* test1 = new int[10];
	//for (auto t : test1) // 동적할당한 배열을 사용하면 에러 : 범위 특정 가능한 자료형만 가능

	struct Test
	{
		int arr[10] = { 0 };
		int a = 10;

		int* begin() {
			return arr; //배열의 시작 주소
		}

		int* end() {
			//return &arr[9] + 1; //포인터 연산 : 배열의 끝 주소
			return &a + 1;	//arr 과 a를 모두 출력 : arr과 a는 구조체이므로 메모리 연속적
		}
	};

	Test test2;
	for (auto t : test2)
		cout << t << endl;

	return 0;
}