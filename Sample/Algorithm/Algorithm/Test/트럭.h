#pragma once

#include<iostream>
#include<queue>
using namespace std;

int main()
{
	int n; // Ʈ���� ��
	int w; // �ٸ� ����
	int l; // �ٸ� �ִ� ����
	int current_time = 0; // �ð�
	int current_l = 0; // �ٸ��� Ʈ���� �� ���� 
	queue<int> land; // ���� �ִ�(������) Ʈ��
	queue<pair<int, int>> bridge; // ����ð�, Ʈ���� ����

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