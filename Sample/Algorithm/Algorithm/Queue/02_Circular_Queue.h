#pragma once

/*
	�� ȯ�� ť
		�� ó���� ���� �������� �̾��� �ִ� ����
		�� �ڵ� �����δ� 1���� �迭������ �����·� �����
		�� ����� ��ȭ ���¸� ���ϱ����� �ϳ��� ������ �׻� ����־� �Ѵ�.
			- ���� ���� : rear == front
			- ��ȭ ���� : (rear + 1) % size == front

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
		// �ϳ��� ������ ������ �ϴ� +1 �� ���·� �־ �����ִ� ����� �ִ�.
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
			cout << "���� ��!" << endl;

		ViewIndex();
	}

	void Dequeue()
	{
		if (Empty() == false)
		{
			front = (front + 1) % size;
		}
		else
			cout << "�������!" << endl;

		ViewIndex();
	}

	T& Front() { return datas[(front + 1) % size]; }

	// ���� üũ������ ����
	void ViewIndex()
	{
		cout << "Current Front Index : " << front << endl;
		cout << "Current Rear Index : " << rear << endl;
		cout << endl;
	}

private:
	T* datas = nullptr;
	int front = 0; // ù�� ° ������ �� �ε����� ����Ų��.
	int rear = 0; // ������ ������ �ε����� ����Ų��.
	int size = 0;
};

