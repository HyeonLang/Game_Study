#pragma once

// 01_Array_Stack.h


/*
	※ 배열로 구현한 스택
		ㄴ 가장 윗 데이터의 인덱스를 top이라는 변수를 두어 관리한다.
		ㄴ 처음 top의 위치는 아무 데이터도 없으니 -1에서 시작한다.
*/
#include<iostream>
#include<assert.h>

template<typename T>
class ArrayStack
{
public:
	ArrayStack(int size)
		:size(size)
	{
		datas = new T[size];
	}

	~ArrayStack()
	{
		delete[] datas;
	}

	bool Push(T data)
	{
		if (top < size - 1)
		{
			datas[++top] = data;
			return true;
		}
		else
			return false;
	}

	T& Top()
	{
		assert(top != -1);
		return datas[top];
	}

	void Pop()
	{
		assert(top != -1);
		--top;
	}

	bool IsEmpty()
	{
		return top == -1;
	}

private:
	T* datas = nullptr;	// 데이터
	int top = -1;		// 최상위 데이터의 위치
	int size = 0;		// 최대 사이즈
};


int main()
{

}