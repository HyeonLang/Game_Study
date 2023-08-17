#pragma once

// Kruskal.h

/*
	※ 크루스칼(Kruskal's) 알고리즘
		ㄴ 무향 연결 그래프가 주어질 때, "최소 신장 트리"라고
		불리는 서브 그래프를 찾는 알고리즘
		ㄴ 크루스칼 알고리즘은 Union_Find 자료구조를 사용한다.

	※ 신장트리
		ㄴ 해당 그래프의 모든 정점을 포함하는 트리 형태의 서브 그래프
		ㄴ 그래프에서 신장트리는 여러개가 존재할 수 있다.
		ㄴ 그런 신장트리들 중에서 간선의 가중치의 합이 가장 작은 신장트리를
		최소 신장 트리라고 한다.

	※ 구현 방법
		- 1. 모든 간선을 끊어 놓는다.
		- 2. 가중치 순으로(오름차순) 간선들을 정렬한다.
		- 3. 정렬된 간선을 순서대로 선택한다.
		- 4. 선택한 간선의 두 정점이 연결되어 있지 않으면
		해당 간선을 최소 신장 트리에 포함시키고 두 정점을 연결한다.
		(사이클이 있으면 안됨)
		(간접적으로 연결이 되어 있어도 연결이 되어있다고 친다.)
		(최소 신장 트리의 총 간선의 수 : 총 노드의 개수 - 1)
*/

#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

class DisjointSetTree
{
public:
	void Init(int node_count)
	{
		parent.clear();
		height.clear();

		parent.shrink_to_fit();
		height.shrink_to_fit();

		for (int i = 0; i < node_count; i++)
		{
			parent.push_back(i);
			height.push_back(1);
		}
	}

	int Find(int v)
	{
		if (parent[v] == v) return v;
		return parent[v] = Find(parent[v]);
	}

	void Union(int v1, int v2)
	{
		v1 = Find(v1);
		v2 = Find(v2);

		if (v1 == v2) return;

		if (height[v1] < height[v2])
			swap(v1, v2);

		parent[v2] = v1;

		if (height[v1] == height[v2])
			height[v1]++;
	}

	bool IsSameSet(int v1, int v2) { return Find(v1) == Find(v2); }

private:
	vector<int> parent;
	vector<int> height;
};

class Kruskal
{
public:
	struct Edge
	{
		Edge() = default;
		Edge(int v1, int v2, int cost) : v1(v1), v2(v2), cost(cost) {}

		int v1, v2; // 연결할 두 정점
		int cost; // 간선의 가중치

		bool operator <(const Edge& e1) const
		{
			return cost < e1.cost;
		}
	};

public:
	void AddEdge(Edge edge)
	{
		edges.push_back(edge);
	}

	int MakeMST(int node_count)
	{
		uf.Init(node_count);
		sort(edges.begin(), edges.end());
		int result = 0;
		int max = 0;

		for (const Edge& e : edges)
		{
			if (uf.IsSameSet(e.v1, e.v2) == false)
			{
				uf.Union(e.v1, e.v2);
				max = e.cost;
				result += e.cost;
			}
		}

		return result - max;
	}

private:
	vector<Edge> edges;
	DisjointSetTree uf;
};

int main()
{
	int N, M;

	cin >> N >> M;

	Kruskal k;

	int A, B, C;

	for (int i = 0; i < M; i++)
	{
		cin >> A >> B >> C;

		k.AddEdge(Kruskal::Edge(A, B, C));
	}

	cout << k.MakeMST(N + 1);
}
