// 17_array.cpp

#include <iostream>
#include <array>

int main() {
	using namespace std;

	int arr1[] = { 1,2,3,4,5 };
	int arr2[]{ 1,2,3,4,5 };
	//int arr3[](1, 2, 3, 4, 5); // 다이렉트 초기화 불가

	std::array<int, 5> arr4; //int 5개 저장
	std::array<int, 5> arr5{1,2,3,4,5};

	arr5[0];    //범위 초과 예외 처리 없음 : 빠름
	arr5.at(0); //범위 초과 예외 처리 있음 : 느림

	return 0;
}