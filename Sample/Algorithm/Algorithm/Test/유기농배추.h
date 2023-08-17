#pragma once

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int DFS(vector<vector<bool>>& map, vector<vector<bool>>& visited, int row, int col)
{
	if (row < 0 || row >= map.size()) return 0;
	if (col < 0 || col >= map[0].size()) return 0;
	if (map[row][col] == false) return 0;
	if (visited[row][col] == true) return 0;

	visited[row][col] = true;
	int result = 1;

	result += DFS(map, visited, row - 1, col);
	result += DFS(map, visited, row + 1, col);
	result += DFS(map, visited, row, col - 1);
	result += DFS(map, visited, row, col + 1);

	return result;
}

int main()
{
	int count = 0;

	cin >> count;

	for (size_t i = 0; i < count; i++)
	{
		int size_row, size_col, K;

		cin >> size_col >> size_row >> K;

		vector<vector<bool>> map(size_row);
		vector<vector<bool>> visited(size_row);
		vector<int> result;

		for (auto& vec : map)
			vec.resize(size_col, false);

		for (auto& vec : visited)
			vec.resize(size_col, false);

		for (int i = 0; i < K; i++)
		{
			int row, col;
			cin >> col >> row;
			map[row][col] = true;
		}

		for (int i = 0; i < size_row; i++)
			for (int j = 0; j < size_col; j++)
				if (map[i][j] == true && visited[i][j] == false)
				{
					int count = DFS(map, visited, i, j);

					result.push_back(count);
				}

		cout << result.size() << endl;
	}

	return 0;
}