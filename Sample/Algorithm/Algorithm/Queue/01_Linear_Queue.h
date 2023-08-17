#pragma once
/*
	※ 선형 큐
		ㄴ 데이터가 일렬로 되어있는 형태
		ㄴ 데이터를 뺄 떄 나머지 데이터를 앞으로 밀어줘야함 -> 비용이 많이듬

*/
#include<iostream>
#include<assert.h>

using namespace std;

class LinearQueue
{
public:
	LinearQueue(int size)
		:size(size)
	{
		datas = new int[size];
	}

	~LinearQueue()
	{
		delete[] datas;
		datas = nullptr;
	}

	bool IsFull() { return rear == (size - 1); }
	bool IsEmpty() { return rear < 0; }

	void Enqueue(int data)
	{
		if (IsFull())
			cout << "가득 참!" << endl;
		else
			datas[++rear] = data;
	}

	void Dequeue()
	{
		if (IsEmpty())
		{
			cout << "비어 있음!!" << endl;
		}
		else
		{
			/*
				맨 앞의 데이터를 제거하는것이므로 뒤에 있는 데이터를 모두
				한 칸씩 당겨오고 rear를 1 감소시킨다.

				front를 +1 시키는 방식으로 맨 앞의 원소를 제외해 구현하는 방법도 있지만
				이렇게 하면 front 앞의 공간을 활용할 수 없는 문제가 발생한다.
				-> 그렇다고 데이터를 앞으로 당기면 비용이 많이듬
				-> 선형큐는 이런 문제를 가지고 있어 환형큐를 사용한다.
			*/
			for (int i = 1; i < rear + 1; i++)
				datas[i - 1] = datas[i];
			rear--;
		}
	}

	int& Front() { return datas[0]; }

	int& Back() { return datas[rear]; }

private:
	//인덱스를 증가 시키고 넣는다.

	int* datas = nullptr;
	int size = 0;
	int front = 0; // 맨 앞의 원소의 인덱스를 가리킨다.
	int rear = -1; // 마지막 인덱스를 가리킨다. 초기엔 데이터가 없으므로 -1
};
//   4       
// 3 6 2 7 5 1 4