// 02_my_arr.h
#pragma once
#include <iostream>
using namespace std;
template<class T>
class MyArray {
public:
	MyArray(int length) 
		: length(length) {
		arr = new T[length];
	}

	~MyArray() {
		delete[] arr;
	}

	void Print();
private:
	T* arr = nullptr;
	int length = 0;
};

// 秦搬规过 1.
//template<typename T>
//inline void MyArray<T>::Print()
//{
//	for (int i = 0; i < length; i++) {
//		cout << arr[i] << endl;
//	}
//}

// 秦搬规过 3.
#include "02_my_arr.inl"
