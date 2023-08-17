#pragma once

// 01_BFS_Graph.h

/*
	※ 너비 우선 탐색(BFS Breadth First Search)
		ㄴ 루트 노드(혹은 임의의 다른 노드)에서 시작해서 인접한 노드를 먼저 탐색하는 방법
		ㄴ 시작 정점에서 가까운 정점을 먼저 방문하고 멀리 떨어져 있는 정점을 나중에 순회하는 방식.
		ㄴ 즉 깊게 탐색하기 전에 넓게 탐색하는 방식임.

	※ 사용하는 케이스
		ㄴ 길찾기 알고리즘. (미로찾기 등등)
		ㄴ prim, 다익스트라 알고리즘과 유사하다.

	※ 너비우선 탐색을 사용하는 이유
		ㄴ 가중치 없는 그래프에서 최단경로를 찾을때 사용한다.
		DFS로도 최단경로를 찾을수는 있지만, BFS가 평균적으로 빠르다.
		DFS는 모든 경우를 검색을 해야한다.
		하지만, BFS는 깊이순으로 검색을 하기 때문에, 가장 얕은 깊이에서
		목적지를 찾은 경로가 최단 경로임을 보장할 수 있다.

	※ 탐색 과정
		ㄴ깊이가 1인 모든 모드를 방문하고, 그 다음에는 깊이가 2인 노드, 그다음 3인 노드를
		이런식으로 계속 방문을 하다가, 더 이상 방문할 곳이 없으면 탐색을 마친다.

		1. 시작 노드를 방문한다(방문한 노드를 체크해준다)
			큐에 방문한 노드를 삽입한다.
			초기 상태의 큐에는 시작노드만이 저장된다.

		2. 큐에서 꺼낸 노드와 인접한 노드들을 모두 차례로 방문한다.
			인접한 노드가 없다면, 큐의 앞에서 노드를 꺼낸다.
			큐에 방문한 노드를 삽입한다.

		3. 큐가 비어있을때까지 반복한다.
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

	// 0을 시작점으로 탐색
	graph.BFS(0);

}