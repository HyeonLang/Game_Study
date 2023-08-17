#pragma once

// Disjoint_Set.h

/*
	�� Disjoint Set
		�� Union Find ����� �θ���.
		�� ���μ� ����(Disjoint Set) : ���� �ߺ����� �ʴ� ���Ҹ� ������ �� �� �̻��� ����
		�� ������ �����ϴ� �ڷᱸ��, ���� �ߺ����� ���� �κ� ���յ�� ������ ���ҵ鿡 ����
		������ �����ϰ� �����ϴ� �ڷᱸ���̴�.
		�� ��ü ������ ���� �� ���� ��ҵ��� ��ġ�� �ʵ��� ������ �� ����Ѵ�.
			-> ���ҵ� ���յ��� ���μ� �����̹Ƿ� ���յ��� ��ĥ �� �ߺ��� ���Ҹ� ������ �ʿ䰡 ����.
		�� ������ Ʈ���� ǥ���Ѵ�.
		�� ũ�罺Į �˰����� ����Ѵ�.
		�� Union�� Find ������ �����Ѵ�.

		�� Union Find
		�� Union : �־��� ���ҵ��� ���� ������ ����(Ʈ��)�� �ϳ��� �������� ��ģ��.
			-> ���� �� Ʈ���� �ϳ��� ��Ʈ�� �ٸ� Ʈ���� ��Ʈ�� ��������ش�.
			�̶� ���� Ʈ���� ū Ʈ���� ��������� ��� ���� Ž��(Find)���� ��尡 ��Ʈ��
			ã�� ������ ��������� �� ���� ������ �ȴ�. �̷��� �ϱ� ���ؼ� ���� 2���� ����� ����Ѵ�.

				1. Ʈ���� ����(����)�� ���� ���� �����Ѵ�. (Union by Rank)
					-> �̶� Ʈ���� ���̰� ���� ��� Ʈ���� ���̰� �����ϹǷ� +1 �����ش�.
					-> �׷��� �ʴٸ� Ʈ���� ���̴� �� ���� ū Ʈ���� ���̷� ��������.

				����)

				Ʈ��1       Ʈ�� 2
																	A        Ʈ���� ���̰� �������
					A			C		�ΰ��� Ʈ���� ���ϸ�		  C   B      ���̰� �����ϹǷ� +1 ���ش�.
				B			 D									D


				2. Ʈ���� ũ�Ⱑ ���� ���� ū �ʿ� ��ģ��. (Union by Size)
					-> Ʈ�� A�� Ʈ�� B�� ������ �� Ʈ���� ũ��� A + B�̴�.

		�� Find	 : �־��� ����� ��Ʈ�� ã���ش�.
			-> �־��� ����� �θ� Ÿ�� �ö󰡸鼭 ��Ʈ�� ã�� �ȴ�. ���⼭ ��������
			���� Ʈ���� �� ��� ��Ʈ�� ã�� ������ �����ϰ� �Ǵµ� �־��� ��� O(Ʈ���� ũ��)�� �ȴ�.
			�̶� �ϴ� ����ȭ ����� ��� ����(Path Compression)�ε�
			�־��� ��尡 ��Ʈ ��带ã�� ���� ���İ� ���� ������ ��Ʈ�� ��������־�
			������ ã�� �ÿ��� O(1)�� �ǵ����Ѵ�.
*/

#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

// ���ظ� ���� ���� ���� ������ ���μ� �ڷᱸ��
// ����ȭ x
class DisjointSet
{
public:
	DisjointSet(int node_count)
	{
		/*
			�ʱ� ���´� ������ ��Ұ� ���ε��� ���տ� ���� ����
			-> i��° ��Ҵ� i��° ���տ� ���Ѵٰ� ����
		*/
		for (int i = 0; i < node_count; i++)
			parent.push_back(i);
	}

	// ��� v1�� ��� v2�� �����ش�.
	// -> v1�� ���� ���տ� v2�� ���� ������ �����ش�.
	void Union(int v1, int v2)
	{
		// �� ����� ����(��Ʈ)�� ã�´�.
		v1 = Find(v1);
		v2 = Find(v2);

		// ������ ������� ����
		if (v1 == v2) return;

		// v2�� ��Ʈ�� v1�� ��Ʈ�� ��������ش�.
		// parent[v2] == v2�� ��ȯ�̹Ƿ�
		// v2�� ������ v1�� ��Ʈ�� ��������ִ� ���°� �ȴ�.
		parent[v2] = v1;
	}

	// �ڽ��� ���� ����(��Ʈ) ��ȯ
	int Find(int v)
	{
		if (parent[v] == v) return v;
		return Find(parent[v]);
	}

private:
	// parent[i] : i��° ������ �θ� ����� ��ȣ
	// -> ���� parent[i] ==  i�� ��� �ش� ���Ұ� ���� i�� ��ǥ ����
	vector<int> parent;
};

// ����ȭ�� Ʈ�� ������ ���μ� �ڷᱸ��
class DisjointSetTree
{
public:
	DisjointSetTree(int node_count)
	{
		for (int i = 0; i < node_count; i++)
		{
			parent.push_back(i);
			height.push_back(1);
			group_size.push_back(1);
		}
	}

	int Find(int v)
	{
		if (parent[v] == v) return v;
		return parent[v] = Find(parent[v]);
	}

	void Union1(int v1, int v2) // Union by Rank
	{
		v1 = Find(v1);
		v2 = Find(v2);

		if (v1 == v2) return;

		// ����(����)�� ū ������ v1�� �����Ѵ�.
		if (height[v1] < height[v2])
			swap(v1, v2);

		// v2�� ������ v1�� �ٲپ� �ش�.
		// -> v2 ��ǥ ����(��Ʈ)�� v1�� ����(��Ʈ)�� �ڽ����� �����.
		parent[v2] = v1;

		// Ʈ���� ���̰� ���� ��� ���̰� �����ϰ� �ȴ�.
		if (height[v1] == height[v2])
			height[v1]++;
	}

	void Union2(int v1, int v2) // Union by Size
	{
		v1 = Find(v1);
		v2 = Find(v2);

		if (v1 == v2) return;

		// ũ�Ⱑ ū ������ v1�� �����Ѵ�.
		if (group_size[v1] < group_size[v2])
			swap(v1, v2);

		// v2�� ������ v1�� �ٲپ� �ش�.
		// -> v2 ��ǥ ����(��Ʈ)�� v1�� ����(��Ʈ)�� �ڽ����� �����.
		parent[v2] = v1;

		// ���� ũ�⸦ �����ش�.
		group_size[v1] += group_size[v2];
	}

private:
	vector<int> parent;	// �� ���Ұ� ����Ű�� �θ� 
	vector<int> height;	// �� ������ ����
	vector<int> group_size;	// �� ������ ũ��
};