#pragma once

/*
	※ 환형 큐
		ㄴ 처음과 끝이 원형으로 이어져 있는 형태
		ㄴ 코드 상으로는 1차원 배열이지만 원형태로 사용함
		ㄴ 공백과 포화 상태를 비교하기위해 하나의 공간을 항상 비워둬야 한다.
			- 공백 상태 : rear == front
			- 포화 상태 : (rear + 1) % size == front

*/

#include<iostream>
using namespace std;
template<typename T>
class CircularQueue
{

public:
	CircularQueue(int size)
		:size(size)
	{
		datas = new T[size];
		// 하나의 공간을 버려야 하니 +1 된 상태로 넣어서 맞춰주는 방법이 있다.
		//datas = new T[size + 1];
		// size++;
	}

	~CircularQueue()
	{
		delete[] datas;
	}

	bool IsFull() { return (rear + 1) % size == front; }

	bool Empty() { return rear == front; }

	void Enqueue(T data)
	{
		if (IsFull() == false)
		{
			rear = (rear + 1) % size;
			datas[rear] = data;
		}
		else
			cout << "가득 참!" << endl;

		ViewIndex();
	}

	void Dequeue()
	{
		if (Empty() == false)
		{
			front = (front + 1) % size;
		}
		else
			cout << "비어있음!" << endl;

		ViewIndex();
	}

	T& Front() { return datas[(front + 1) % size]; }

	// 상태 체크용으로 만듬
	void ViewIndex()
	{
		cout << "Current Front Index : " << front << endl;
		cout << "Current Rear Index : " << rear << endl;
		cout << endl;
	}

private:
	T* datas = nullptr;
	int front = 0; // 첫번 째 원소의 앞 인덱스를 가리킨다.
	int rear = 0; // 마지막 원소의 인덱스를 가리킨다.
	int size = 0;
};

