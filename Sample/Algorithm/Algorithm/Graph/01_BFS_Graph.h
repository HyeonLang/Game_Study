#pragma once

// 01_BFS_Graph.h

/*
	�� �ʺ� �켱 Ž��(BFS Breadth First Search)
		�� ��Ʈ ���(Ȥ�� ������ �ٸ� ���)���� �����ؼ� ������ ��带 ���� Ž���ϴ� ���
		�� ���� �������� ����� ������ ���� �湮�ϰ� �ָ� ������ �ִ� ������ ���߿� ��ȸ�ϴ� ���.
		�� �� ���� Ž���ϱ� ���� �а� Ž���ϴ� �����.

	�� ����ϴ� ���̽�
		�� ��ã�� �˰�����. (�̷�ã�� ���)
		�� prim, ���ͽ�Ʈ�� �˰������ �����ϴ�.

	�� �ʺ�켱 Ž���� ����ϴ� ����
		�� ����ġ ���� �׷������� �ִܰ�θ� ã���� ����Ѵ�.
		DFS�ε� �ִܰ�θ� ã������ ������, BFS�� ��������� ������.
		DFS�� ��� ��츦 �˻��� �ؾ��Ѵ�.
		������, BFS�� ���̼����� �˻��� �ϱ� ������, ���� ���� ���̿���
		�������� ã�� ��ΰ� �ִ� ������� ������ �� �ִ�.

	�� Ž�� ����
		�����̰� 1�� ��� ��带 �湮�ϰ�, �� �������� ���̰� 2�� ���, �״��� 3�� ��带
		�̷������� ��� �湮�� �ϴٰ�, �� �̻� �湮�� ���� ������ Ž���� ��ģ��.

		1. ���� ��带 �湮�Ѵ�(�湮�� ��带 üũ���ش�)
			ť�� �湮�� ��带 �����Ѵ�.
			�ʱ� ������ ť���� ���۳�常�� ����ȴ�.

		2. ť���� ���� ���� ������ ������ ��� ���ʷ� �湮�Ѵ�.
			������ ��尡 ���ٸ�, ť�� �տ��� ��带 ������.
			ť�� �湮�� ��带 �����Ѵ�.

		3. ť�� ������������� �ݺ��Ѵ�.
*/

#include<Windows.h>
#include<iostream>
#include<queue>
using namespace std;

class Graph
{
public:
	Graph(int nodeCount)
		: nodeCount(nodeCount)
	{
		graph = new int* [nodeCount];
		for (int i = 0; i < nodeCount; i++)
			graph[i] = new int[nodeCount];

		for (int i = 0; i < nodeCount; i++)
			ZeroMemory(graph[i], sizeof(int) * nodeCount);

		visit = new int[nodeCount];
		ZeroMemory(visit, sizeof(int) * (nodeCount));
	}

	~Graph()
	{
		for (int i = 0; i < nodeCount; i++)
			delete[] graph[i];
		delete graph;

		delete[] visit;
	}

	void MakeLink(int x, int y)
	{
		graph[x][y] = graph[y][x] = 1;
	}

	void Display()
	{
		for (int i = 0; i < nodeCount; i++)
		{
			for (int j = 0; j < nodeCount; j++)
				cout << graph[i][j] << "\t";

			cout << endl;
		}
	}

	void BFS(int start)
	{
		cout << start << " ";
		q.push(start);
		visit[start] = 1;

		while (q.empty() != true)
		{
			int node = q.front();
			q.pop();

			for (int i = 0; i < nodeCount; i++)
			{
				if (graph[node][i] == 1 && visit[i] == 0)
				{
					visit[i] = 1;
					q.push(i);
					cout << i << " ";
				}
			}
		}

	}

private:
	int** graph = nullptr;
	int nodeCount = 0;

	int* visit = nullptr;
	queue<int> q;
};

int main()
{
	Graph graph(5);

	graph.Display();
	cout << endl;

	graph.MakeLink(0, 1);
	graph.MakeLink(0, 4);

	graph.MakeLink(1, 2);
	graph.MakeLink(1, 4);

	graph.MakeLink(2, 3);

	graph.Display();
	cout << endl;

	// 0�� ���������� Ž��
	graph.BFS(0);

}