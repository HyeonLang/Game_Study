#pragma once
/*
	�� ���� ť
		�� �����Ͱ� �Ϸķ� �Ǿ��ִ� ����
		�� �����͸� �� �� ������ �����͸� ������ �о������ -> ����� ���̵�

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
			cout << "���� ��!" << endl;
		else
			datas[++rear] = data;
	}

	void Dequeue()
	{
		if (IsEmpty())
		{
			cout << "��� ����!!" << endl;
		}
		else
		{
			/*
				�� ���� �����͸� �����ϴ°��̹Ƿ� �ڿ� �ִ� �����͸� ���
				�� ĭ�� ��ܿ��� rear�� 1 ���ҽ�Ų��.

				front�� +1 ��Ű�� ������� �� ���� ���Ҹ� ������ �����ϴ� ����� ������
				�̷��� �ϸ� front ���� ������ Ȱ���� �� ���� ������ �߻��Ѵ�.
				-> �׷��ٰ� �����͸� ������ ���� ����� ���̵�
				-> ����ť�� �̷� ������ ������ �־� ȯ��ť�� ����Ѵ�.
			*/
			for (int i = 1; i < rear + 1; i++)
				datas[i - 1] = datas[i];
			rear--;
		}
	}

	int& Front() { return datas[0]; }

	int& Back() { return datas[rear]; }

private:
	//�ε����� ���� ��Ű�� �ִ´�.

	int* datas = nullptr;
	int size = 0;
	int front = 0; // �� ���� ������ �ε����� ����Ų��.
	int rear = -1; // ������ �ε����� ����Ų��. �ʱ⿣ �����Ͱ� �����Ƿ� -1
};
//   4       
// 3 6 2 7 5 1 4