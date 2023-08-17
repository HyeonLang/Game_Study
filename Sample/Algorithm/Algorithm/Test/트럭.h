#pragma once

#include<iostream>
#include<queue>
using namespace std;

int main()
{
	int n; // 트럭의 수
	int w; // 다리 길이
	int l; // 다리 최대 하중
	int current_time = 0; // 시간
	int current_l = 0; // 다리위 트럭의 총 무게 
	queue<int> land; // 땅에 있는(진입할) 트럭
	queue<pair<int, int>> bridge; // 경과시간, 트럭의 무게

	cin >> n >> w >> l;
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		land.push(temp);
	}

	while (true)
	{
		if (bridge.empty() != true)
		{
			int truck_time = bridge.front().first;
			int truck_weight = bridge.front().second;

			if (current_time - truck_time >= w)
			{
				bridge.pop();
				current_l -= truck_weight;
			}
		}

		if (land.empty() != true && current_l + land.front() <= l)
		{
			bridge.push(make_pair(current_time, land.front()));
			current_l += land.front();
			land.pop();
		}

		current_time++;
		if (land.empty() == true && bridge.empty() == true) break;
	}

	cout << current_time << endl;
}