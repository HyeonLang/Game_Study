// 02_my_arr.inl
// .inl : ���� ��Ŭ�� > �Ӽ� > �Ϲ� > �����ۼӼ� : c/c++ ���

#include "02_my_arr.h"
#include <iostream>
using namespace std;
 
// �ذ��� 3.
template<typename T>
inline void MyArray<T>::Print()
{
	for (int i = 0; i < length; i++) {
		cout << arr[i] << endl;
	}
}
