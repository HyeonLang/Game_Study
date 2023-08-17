#pragma once
/*
	※ 그래프(Graph)
		ㄴ 연결되어 있는 객체간의 관계를 표현하는 자료구조
		ㄴ 데이터 간의 관계를 표현할 때 사용, 예시) 길찾기 알고리즘, SNS의 친구관계

	※ 그래프 용어 정리
		ㄴ 정점(Vetrex)					: 트리의 노드를 생각하면된다. 노드라고도 부름
		ㄴ 간선(Edge)					: 정점끼리의 관계를 선으로 표현한 것
		ㄴ 가중치(Weight)				: A노드에서 B노드로 이동할때 필요한 비용, 가중치가 있으면 가중치 그래프라고 부르고 길찾기 알고리즘에 사용한다.
		ㄴ 인접 정점(Adjacent Vertex)	: 하나의 정점에서 간선에 의해 직접 연결된 정점.
		ㄴ 차수(Degree)					: 하나의 정점에 연결된 다른 정점의 수
			- 무방향 그래프의 차수
				ㄴ 인접 정점의 개수
			- 방향 그래프의 차수
				ㄴ 진입 차수(In Degree)	: 외부에서 오는 간선의 수
				ㄴ 진출 차수(Out Degree)	: 외부로 향하는 간선의 수
		ㄴ 경로 길이(Path Length)		: 경로를 구성하는데 사용된 간선의 수
		ㄴ 단순 경로(simple path)		: 경로 중에서 반복되는 간선이 없는 경로
		ㄴ 사이클(cycle)					: 단순 경로의 시작 정점과 종료 정점이 동일한 경로. -> 왔다가 돌아오긴하지만 길이 달라야 한다.

	※ 그래프의 종류

		ㅁ 유향 그래프(Directed Graph)
			ㄴ 간선의 방향이 있음 -> 선 하나는 단방향을 의미함

		ㅁ 무향 그래프(Indirected Graph)
			ㄴ 간선의 방향이 없음 -> 연결되어 있으면 양방향 이동이 가능

		ㅁ 가중치 그래프(Weighted Graph)
			ㄴ 간선에 가중치가 있는 형태의 그래프

		ㅁ 연결 그래프(connected graph)
			ㄴ G에 있는 모든 정점 쌍에 대하여 항상 경로가 존재하는 그래프

		ㅁ 비연결 그래프(Disconnected graph)
			ㄴ 정점들 중 간선에 의해 연결되어 있지 않는 노드가 존재하는 그래프

		ㅁ 완전 그래프(complete graph)
			ㄴ 모든 정점들이 서로 연결되어 있는 형태

	※ 그래프관련 트리
		ㅁ 신장 트리(Spanning Tree)
			ㄴ 그래프의 모든 정점을 포함하는 트리
			ㄴ 최소 연결부분 그래프(간선의 수가 제일 적은 그래프)

		ㅁ 최소 신장 트리(Minimum Spanning Tree)
			ㄴ 각 간선에 가중치가 부여되어 있을때, 가중치를 고려하여 최소 비용의 신장트리를 구하는것.
			ㄴ 크루스칼(kruskal), 프림(prim) 알고리즘을 이용해 구할 수 있다.


	※ 인접 행렬 방법(Adjacent Matrix)방법
		ㄴ 정점간의 관계를 2차원 배열로 표현한 방법
			-> 만약 간선(i, j)가 그래프에 존재한다면,
			-> M[i][j] = 1;
			-> 그렇지 않다면 M[i][j] = 0

		ㄴ 그래프 G1의 정점은 A~~이다.
			- V(G1) = {A,B,C,D,E,F}

		ㄴ 무향 G1의 간선
			- E(G1) = {(A,B), (A,F), (A,D)}

		ㄴ 유향 G1의 간선
			- E(G1) = {<A,B>, <A,F>, <A,D>}
			- <A, B> -> A에서 B로 향하는 간선
*/


#include<iostream>
#include<Windows.h>

using namespace std;

int main()
{
	// 무방향 그래프의 인접 행렬 
	int m;
	cout << "정점의 개수 입력 :";
	cin >> m;

	int** graph = new int* [m];

	for (int i = 0; i < m; i++)
		graph[i] = new int[m];


	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			graph[i][j] = 0;

	int u, v;
	for (int i = 0; i < m; i++)
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < m; j++)
				cout << graph[i][j] << "\t";
			cout << endl;
		}

		cout << "연결한 정점(u) : ";
		cin >> u;
		cout << "연결한 정점(v) : ";
		cin >> v;

		cout << endl;

		graph[u][v] = graph[v][u] = 1;


		Sleep(1000);
	}

	return 0;
}