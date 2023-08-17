#pragma once
// Prim.h

/*
	�� Prim's Algoritm
		�� ����ġ�� �ִ� ���� �׷������� �ּҺ�� ����Ʈ���� ã�� �˰���.
		�� �׷������� ������ ��带 �����Ͽ� ������ Ʈ���� ����� Ʈ���� ���� ���� ������� ����
		��尣�� ���� �� ���� ����ġ�� ���� ������ ã�� Ʈ���� �߰��Ѵ�.
		�� �ּ� ���� ����Ͽ� ������ �����ϴ�.
		�� ũ�罺Į �˰���� ���� �뵵���� ��Ȳ�� ���� �� �˰����� ȿ���� �޶��� �� �ִ�.
		�� ������ ������ ���� ��쿡�� ũ�罺Į, ������ ������ ���� ��� ������ ȿ�����̴�.


	�� �������
		1. ������ ������ �����Ͽ� ����ִ� T�� ���Խ�Ų��.(T�� ��尡 �Ѱ��� Ʈ��)
		2. T�� �ִ� ���� T�� ���� ���� ������ ���� �� ����ġ�� �ּ��� ������ ã�´�.
		3. ã�� ������ �����ϴ� �� ��� ��, T�� ���� ��带 T�� ���Խ�Ų��.
		4. 2�� 3���� ��� ��尡 T�� ���� �� �� ���� �ݺ��Ѵ�.
*/

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

using PII = pair<int, int>;

class Prim
{
public:
	Prim(int node_count)
		: edges(node_count)
		, visited(node_count, false)
	{
	}

	// ����ġ �ִ� ���� �׷����� ����
	void AddEdge(int v1, int v2, int weight)
	{
		edges[v1].push_back(make_pair(weight, v2));
		edges[v2].push_back(make_pair(weight, v1));
	}

	// �ּ� ��� ����Ʈ���� ����ġ �� ��ȯ
	int MakeMST()
	{
		int min_weight = 0;

		priority_queue<PII, vector<PII>, greater<PII>> queue;

		queue.push(make_pair(0, 0));

		while (queue.empty() != true)
		{
			auto curr_data = queue.top();
			queue.pop();

			if (visited[curr_data.second] == true) continue;
			visited[curr_data.second] = true;
			min_weight += curr_data.first;

			for (const auto& edge : edges[curr_data.second])
			{
				if (visited[edge.second] == true) continue;
				queue.push(edge);
			}
		}

		return min_weight;
	}

public:
	// edges[v1][e].first  = weight;
	// edges[v1][e].second = v2;
	// -> ���� v1�� v2�� �մ� ���� e�� ����ġ weight
	vector<vector<PII>> edges;
	// �ش� ��尡 Ʈ���� ���ԵǾ��°�?
	vector<bool> visited;
};



using namespace std;

int main()
{
	Prim p(6);


	p.AddEdge(0, 1, 25);
	p.AddEdge(0, 2, 20);
	p.AddEdge(0, 3, 15);
	p.AddEdge(0, 4, 10);
	p.AddEdge(1, 5, 17);
	p.AddEdge(4, 5, 13);
	p.AddEdge(4, 3, 7);
	p.AddEdge(3, 2, 23);

	cout << p.MakeMST();


	return 0;
}