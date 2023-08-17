#pragma once

// 02_DFS_Graph.h

/*
	※ DFS(depth - first search)
		ㄴ 루트노드(혹은 임의의 다른 노드)에서 시작해서 다음 분기로 넘어가기 전에 해당 분기를 완벽하게 탐색하는 방법.
		ㄴ 미로를 탐색 할때 한 방향으로 부터 갈 수 있을 때까지 계속 가다가 더이상 갈 수 없게 되면 다시 가장 가까운 갈림길로
		돌아와서 이곳으로부터 다른 방향으로 다시 탐색을 진행하는 방식.
		ㄴ 너비 우선 탐색에 비해 구현이 좀더 간단하다.
		ㄴ 단순 검색속도는 BFS에 비해 느리다.

	※ 특징
		ㄴ 자기 자신을 호출하는 순환 알고리즘의 형태를 뛴다.
		ㄴ 전위 순회를 포함한 다른 형태의 트리 순회는 모두 DFS의 한 종류다.

	※ 장점
		ㄴ 단지 현 경로상의 노드들만 기억하면 되기 때문에 저장공간의 수요가 비교적 적다.
		ㄴ 목표 노드가 깊은 단계에 있을경우 빨리 해를 구할수 있다.

	※ 단점
		ㄴ 해가 없는 경로에 깊이 빠질 가능성이 존재한다. 따라서 실제로는
		미리 지정한 임의의 깊이까지만 탐색하고, 목표노드를 발견하지 못하면
		다음 경로를 따라 탐색하는 방법을 사용한다.

		ㄴ 얻어진 해가 최단 경로가 된다는 보장이 없다.
		이는 목표에 이르는 경로가 다수인 문제에 대해 깊이 우선탐색은
		목표에 다다르면 탐색을 끝내버리기 때문에, 이때 얻어진 해는 최적이 아닐수도 있다.
*/

#include<Windows.h>
#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

// 방향 그래프
class Graph
{
public:
	Graph(int nodeCount)
		:nodeCount(nodeCount)
	{
		// assign(범위, 값) : 범위 만큼의 원소를 해당 값으로 초기화한다.
		graph.assign(nodeCount, vector<int>());
		visited.assign(nodeCount, false);
	}

	void MakeLink(int node, int next)
	{
		graph[node].push_back(next);
		sort(graph[node].begin(), graph[node].end());
	}

	void Display();

	// 재귀함수를 이용한 DFS
	void DFS1(int start)
	{
		visited[start] = true;
		cout << start << " ";
		for (int next : graph[start])
			if (visited[next] == false)
				DFS1(next);
	}

	// 스택을 활용한 DFS
	void DFS2(int start)
	{
		stack<int> s;
		s.push(start);
		while (s.empty() != true)
		{
			int cur = s.top();
			s.pop();

			if (visited[cur] == true)
				continue;

			cout << cur << " ";
			visited[cur] = true;

			for (int i = 0; i < graph[cur].size(); i++)
			{
				if (visited[graph[cur][i]] != true)
					s.push(graph[cur][i]);
			}
		}
	}

	void DFS3()
	{
		/*
			위의 DFS1, DFS2로 탐색할 경우 연결 그래프가 아닌경우 모든 노드에대한 탐색x
			-> DFS3를 사용해 모든 노드를 탐색하도록 코드 작성

			그래프가 쪼개져있는 경우 각 부분 그래프를 컴포넌트 혹은 요소라고 부른다.
			DFS3로 주어진 그래프가 몇개의 컴포넌트로 구성되었는지 확인 가능
		*/

		int count = 0;

		for (int i = 0; i < nodeCount; i++)
			if (visited[i] == false)
			{
				count++;
				DFS1(i);
			}
	}

	void ClearVisitedInfo()
	{
		fill(visited.begin(), visited.end(), 0);
	}

private:
	vector<vector<int>> graph;
	vector<bool> visited;
	int nodeCount;
};

int main()
{
	Graph graph(5);

	graph.MakeLink(0, 1);
	graph.MakeLink(0, 2);

	graph.MakeLink(1, 3);

	graph.MakeLink(2, 3);

	graph.MakeLink(3, 4);

	graph.MakeLink(4, 0);

	graph.Display();
	cout << endl;

	graph.DFS1(0);
	cout << endl;

	graph.ClearVisitedInfo();
	graph.DFS2(0);
	cout << endl;

}