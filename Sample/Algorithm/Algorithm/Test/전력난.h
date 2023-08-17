#pragma once

#include<vector>
#include<algorithm>
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

		for (const Edge& e : edges)
		{
			if (uf.IsSameSet(e.v1, e.v2) == false)
			{
				uf.Union(e.v1, e.v2);
			}
			else
				result += e.cost;
		}

		return result;
	}

private:
	vector<Edge> edges;
	DisjointSetTree uf;
};


#include <iostream>
using namespace std;

int main()
{
	int m; // 노드의 개수
	int n; // 간선의 개수

	int x; // 정점
	int y; // 정점
	int z; // 가중치

	while (true)
	{
		Kruskal k;

		cin >> m >> n;

		if (m == 0 && n == 0)
			break;

		for (int i = 0; i < n; i++)
		{
			cin >> x >> y >> z;

			k.AddEdge(Kruskal::Edge(x, y, z));
		}

		cout << k.MakeMST(m) << endl;
	}

}
