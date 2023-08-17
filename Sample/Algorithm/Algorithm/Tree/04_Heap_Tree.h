#pragma once
/*
	※우선순위큐
		ㄴ 프린터, 시뮬레이션 시스템, 네트워크 트레픽 제어, 운영체제의 작업 스케쥴링에 사용
		ㄴ 우선순위 큐는 배열, 연결리스트, 힙으로 구현가능
		ㄴ 힙트리는 우선순위큐를 위해 만들어짐

	※ 힙 트리(Heap Tree)
		ㄴ 완전 이진트리의 일종, 짧게 힙이라고도 부른다.
		ㄴ 우선순위 큐를 위하여 만들어진 자료구조
		ㄴ 여러개의 값들 중에서 최대값이거나 최소값을 빠르게 찾아내도록 만들어진 자료구조.
		ㄴ 부모노드의 키값이 자식노드보다 항상크다(작다) -> 오름차순 내림차순의 차이.
		ㄴ 큰 값이 상위 레벨에 있고, 작은 값이 하위 레벨에 있다.
		ㄴ 중복키값을 허용함

	※ 힙의 종류

	1. 최대힙(max heap)
		ㄴ 부모 노드의 키값이 자식 노드의 키값 보다 크거나 같은 완전 이진트리

	2. 최소힙(min heap)
		ㄴ 부모 노드의 키값이 자식 노드의 키값 보다 작거나 같은 완전 이진트리


	※ 힙에서의 부모 노드와 자식 노드의 관계
		ㄴ 계산편하게 하기위해서 인덱스를 1번부터 시작함. 0으로 하는 경우도 있음
		ㄴ 현재 노드의 인덱스를 current라고 했을때
			- 부모 노드의 인덱스 : current / 2
			- 자식 Left의 인덱스 : current * 2
			- 자식 Right의 인덱스 : current * 2 + 1

	※ 힙의 삽입 삭제
		ㄴ 힙의 삽입
			- 힙에 새로운 요소가 들어오면 새로운 노드를 힙의 마지막 위치에 삽입한다.
			- 새로운 노드를 부모 노드들과 교환해가면서 힙의 성질 만족시킨다.

		ㄴ 힙의 삭제
			- 루트의 값을 반환을 하고, 루트와 마지막노드를 스왑한다.
			- 다시 값을 비교해 가면서 정렬을 한다.
*/

void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

#include<Windows.h>
#define MAX_ARRAY_SIZE 256

class MaxHeap
{
public:
	MaxHeap()
	{
		ZeroMemory(values, sizeof(int) * MAX_ARRAY_SIZE);
	}

	void Push(int data)
	{
		values[++heap_count] = data;

		int current = heap_count;
		int parent = current / 2;
		while (current > 1 && values[current] > values[parent])
		{
			Swap(&values[parent], &values[current]);

			current = parent;
			parent = current / 2;
		}
	}

	int Pop()
	{
		int result = values[1];

		Swap(&values[1], &values[heap_count--]);

		int current = 1;
		int child = current * 2;

		if (child + 1 <= heap_count)
		{
			child = values[child] > values[child + 1] ? child : child + 1;
		}

		while (child <= heap_count && values[current] < values[child])
		{
			Swap(&values[current], &values[child]);

			current = child;
			child = current * 2;

			if (child + 1 <= heap_count)
			{
				child = values[child] > values[child + 1] ? child : child + 1;
			}
		}

		return result;
	}

private:
	int values[MAX_ARRAY_SIZE];
	int heap_count = 0;
};

class MinHeap
{
public:
	MinHeap()
	{
		ZeroMemory(values, sizeof(int) * MAX_ARRAY_SIZE);
	}

	void Push(int data)
	{
		values[++heap_count] = data;

		int current = heap_count;
		int parent = current / 2;
		while (current > 1 && values[current] < values[parent])
		{
			Swap(&values[parent], &values[current]);

			current = parent;
			parent = current / 2;
		}
	}

	int Pop()
	{
		int result = values[1];

		Swap(&values[1], &values[heap_count--]);

		int current = 1;
		int child = current * 2;

		if (child + 1 <= heap_count)
		{
			child = values[child] < values[child + 1] ? child : child + 1;
		}

		while (child <= heap_count && values[current] > values[child])
		{
			Swap(&values[current], &values[child]);

			current = child;
			child = current * 2;

			if (child + 1 <= heap_count)
			{
				child = values[child] < values[child + 1] ? child : child + 1;
			}
		}

		return result;
	}

private:
	int values[MAX_ARRAY_SIZE];
	int heap_count = 0;
};

#include<iostream>
using namespace std;

int main()
{
	MaxHeap mh;
	for (int i = 0; i < 255; i++)
		mh.Push(rand() % 10);

	for (int i = 0; i < 255; i++)
		cout << mh.Pop() << endl;
}