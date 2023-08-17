#pragma once

// 02_DFS_Graph.h

/*
	�� DFS(depth - first search)
		�� ��Ʈ���(Ȥ�� ������ �ٸ� ���)���� �����ؼ� ���� �б�� �Ѿ�� ���� �ش� �б⸦ �Ϻ��ϰ� Ž���ϴ� ���.
		�� �̷θ� Ž�� �Ҷ� �� �������� ���� �� �� ���� ������ ��� ���ٰ� ���̻� �� �� ���� �Ǹ� �ٽ� ���� ����� �������
		���ƿͼ� �̰����κ��� �ٸ� �������� �ٽ� Ž���� �����ϴ� ���.
		�� �ʺ� �켱 Ž���� ���� ������ ���� �����ϴ�.
		�� �ܼ� �˻��ӵ��� BFS�� ���� ������.

	�� Ư¡
		�� �ڱ� �ڽ��� ȣ���ϴ� ��ȯ �˰����� ���¸� �ڴ�.
		�� ���� ��ȸ�� ������ �ٸ� ������ Ʈ�� ��ȸ�� ��� DFS�� �� ������.

	�� ����
		�� ���� �� ��λ��� ���鸸 ����ϸ� �Ǳ� ������ ��������� ���䰡 ���� ����.
		�� ��ǥ ��尡 ���� �ܰ迡 ������� ���� �ظ� ���Ҽ� �ִ�.

	�� ����
		�� �ذ� ���� ��ο� ���� ���� ���ɼ��� �����Ѵ�. ���� �����δ�
		�̸� ������ ������ ���̱����� Ž���ϰ�, ��ǥ��带 �߰����� ���ϸ�
		���� ��θ� ���� Ž���ϴ� ����� ����Ѵ�.

		�� ����� �ذ� �ִ� ��ΰ� �ȴٴ� ������ ����.
		�̴� ��ǥ�� �̸��� ��ΰ� �ټ��� ������ ���� ���� �켱Ž����
		��ǥ�� �ٴٸ��� Ž���� ���������� ������, �̶� ����� �ش� ������ �ƴҼ��� �ִ�.
*/

#include<Windows.h>
#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

// ���� �׷���
class Graph
{
public:
	Graph(int nodeCount)
		:nodeCount(nodeCount)
	{
		// assign(����, ��) : ���� ��ŭ�� ���Ҹ� �ش� ������ �ʱ�ȭ�Ѵ�.
		graph.assign(nodeCount, vector<int>());
		visited.assign(nodeCount, false);
	}

	void MakeLink(int node, int next)
	{
		graph[node].push_back(next);
		sort(graph[node].begin(), graph[node].end());
	}

	void Display();

	// ����Լ��� �̿��� DFS
	void DFS1(int start)
	{
		visited[start] = true;
		cout << start << " ";
		for (int next : graph[start])
			if (visited[next] == false)
				DFS1(next);
	}

	// ������ Ȱ���� DFS
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
			���� DFS1, DFS2�� Ž���� ��� ���� �׷����� �ƴѰ�� ��� ��忡���� Ž��x
			-> DFS3�� ����� ��� ��带 Ž���ϵ��� �ڵ� �ۼ�

			�׷����� �ɰ����ִ� ��� �� �κ� �׷����� ������Ʈ Ȥ�� ��Ҷ�� �θ���.
			DFS3�� �־��� �׷����� ��� ������Ʈ�� �����Ǿ����� Ȯ�� ����
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