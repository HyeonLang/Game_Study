// 02_my_arr.inl
// .inl : 파일 우클릭 > 속성 > 일반 > 아이템속성 : c/c++ 헤더

#include "02_my_arr.h"
#include <iostream>
using namespace std;
 
// 해결방법 3.
template<typename T>
inline void MyArray<T>::Print()
{
	for (int i = 0; i < length; i++) {
		cout << arr[i] << endl;
	}
}
