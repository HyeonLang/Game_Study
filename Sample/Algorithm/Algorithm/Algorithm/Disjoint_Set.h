#pragma once

// Disjoint_Set.h

/*
	※ Disjoint Set
		ㄴ Union Find 라고도 부른다.
		ㄴ 서로소 집합(Disjoint Set) : 서로 중복되지 않는 원소를 가지는 두 개 이상의 집합
		ㄴ 집합을 관리하는 자료구조, 서로 중복되지 않은 부분 집합들로 나눠진 원소들에 대한
		정보를 저장하고 조작하는 자료구조이다.
		ㄴ 전체 집합이 있을 때 구성 요소들이 겹치지 않도록 분할할 때 사용한다.
			-> 분할된 집합들은 서로소 집합이므로 집합들을 합칠 때 중복된 원소를 고려할 필요가 없다.
		ㄴ 집합은 트리로 표현한다.
		ㄴ 크루스칼 알고리즘에 사용한다.
		ㄴ Union과 Find 연산을 지원한다.

		※ Union Find
		ㅁ Union : 주어진 원소들이 속한 각각의 집합(트리)를 하나의 집합으로 합친다.
			-> 보통 두 트리중 하나의 루트를 다른 트리의 루트에 연결시켜준다.
			이때 작은 트리를 큰 트리에 연결시켜줄 경우 이후 탐색(Find)에서 노드가 루트를
			찾은 연산이 평균적으로 더 적게 나오게 된다. 이렇게 하기 위해서 보통 2가지 방법을 사용한다.

				1. 트리의 높이(깊이)가 작은 쪽을 연결한다. (Union by Rank)
					-> 이때 트리의 높이가 같을 경우 트리의 높이가 증가하므로 +1 시켜준다.
					-> 그렇지 않다면 트리의 높이는 두 개중 큰 트리의 높이로 정해진다.

				예시)

				트리1       트리 2
																	A        트리의 높이가 같은경우
					A			C		두개의 트리를 더하면		  C   B      높이가 증가하므로 +1 해준다.
				B			 D									D


				2. 트리의 크기가 작은 쪽을 큰 쪽에 합친다. (Union by Size)
					-> 트리 A와 트리 B를 합쳤을 때 트리의 크기는 A + B이다.

		ㄴ Find	 : 주어진 노드의 루트를 찾아준다.
			-> 주어진 노드의 부모를 타고 올라가면서 루트를 찾게 된다. 여기서 문제점이
			선형 트리로 될 경우 루트를 찾는 연산이 증가하게 되는데 최악의 경우 O(트리의 크기)가 된다.
			이때 하는 최적화 방법이 경로 압축(Path Compression)인데
			주어진 노드가 루트 노드를찾기 위해 거쳐간 조상 노드들을 루트에 연결시켜주어
			다음에 찾을 시에는 O(1)이 되도록한다.
*/

#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

// 이해를 돕기 위해 만든 간다한 서로소 자료구조
// 최적화 x
class DisjointSet
{
public:
	DisjointSet(int node_count)
	{
		/*
			초기 상태는 각각의 요소가 따로따로 집합에 속한 상태
			-> i번째 요소는 i번째 집합에 속한다고 가정
		*/
		for (int i = 0; i < node_count; i++)
			parent.push_back(i);
	}

	// 요소 v1과 요소 v2를 합쳐준다.
	// -> v1이 속한 집합에 v2가 속한 집합을 합쳐준다.
	void Union(int v1, int v2)
	{
		// 각 요소의 집합(루트)를 찾는다.
		v1 = Find(v1);
		v2 = Find(v2);

		// 집합이 같을경우 리턴
		if (v1 == v2) return;

		// v2의 루트를 v1의 루트로 연결시켜준다.
		// parent[v2] == v2인 상환이므로
		// v2의 집합을 v1의 루트로 연결시켜주는 형태가 된다.
		parent[v2] = v1;
	}

	// 자신이 속한 집합(루트) 반환
	int Find(int v)
	{
		if (parent[v] == v) return v;
		return Find(parent[v]);
	}

private:
	// parent[i] : i번째 원소의 부모 노드의 번호
	// -> 만약 parent[i] ==  i일 경우 해당 원소가 집합 i의 대표 원소
	vector<int> parent;
};

// 최적화한 트리 형태의 서로소 자료구조
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

		// 높이(깊이)가 큰 집합이 v1로 오게한다.
		if (height[v1] < height[v2])
			swap(v1, v2);

		// v2의 집합을 v1로 바꾸어 준다.
		// -> v2 대표 원소(루트)를 v1의 집합(루트)의 자식으로 만든다.
		parent[v2] = v1;

		// 트리의 높이가 같을 경우 높이가 증가하게 된다.
		if (height[v1] == height[v2])
			height[v1]++;
	}

	void Union2(int v1, int v2) // Union by Size
	{
		v1 = Find(v1);
		v2 = Find(v2);

		if (v1 == v2) return;

		// 크기가 큰 집합이 v1로 오게한다.
		if (group_size[v1] < group_size[v2])
			swap(v1, v2);

		// v2의 집합을 v1로 바꾸어 준다.
		// -> v2 대표 원소(루트)를 v1의 집합(루트)의 자식으로 만든다.
		parent[v2] = v1;

		// 집합 크기를 더해준다.
		group_size[v1] += group_size[v2];
	}

private:
	vector<int> parent;	// 각 원소가 가리키는 부모 
	vector<int> height;	// 각 집합의 높이
	vector<int> group_size;	// 각 집합의 크기
};