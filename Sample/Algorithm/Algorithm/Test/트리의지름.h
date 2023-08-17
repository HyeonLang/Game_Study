#pragma once
// 1967�� 

#include<iostream>
#include<vector>
using namespace std;

struct Edge
{
	int child = 0;
	int cost = 0;
};

struct Node
{
	vector<Edge> childs;
};

pair<int, int> tree(vector<Node>& vec, int node,int cost)
{
	vector<pair<int, int>> child_result;

	// �ڽ� ���� ���
	for (auto& edge : vec[node].childs)
		child_result.push_back(tree(vec, edge.child, edge.cost));

	int this_result = 0;
	int child_max_second = 0;
	int child_max_first = 0;

	// �ڽ��� ��Ʈ������ �������� ������ �������� ����ġ�� ���
	for (auto& ele : child_result)
	{
		this_result += ele.second;

		if (child_max_second < ele.second)
			child_max_second = ele.second;

		if (child_max_first < ele.first)
			child_max_first = ele.first;
	}

	return pair<int, int>( 
		(this_result > child_max_first) ? this_result : child_max_first
		, child_max_second + cost);
}

int main()
{
	int node_count = 0;
	cin >> node_count;

	vector<Node> vec(node_count, Node());

	int p, c1, c2;

	for (int i = 0; i < node_count - 1; i++)
	{
		cin >> p >> c1 >> c2;

		p--;
		c1--;

		vec[p].childs.push_back(Edge{ c1, c2 });
	}

	cout << tree(vec, 0, 0).first;

	return 0;
}