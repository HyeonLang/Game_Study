#pragma once

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int DFS(vector<vector<bool>>& map, vector<vector<bool>>& visited, int row, int col)
{
	if (row < 0 || row >= map.size()) return 0;
	if (col < 0 || col >= map.size()) return 0;
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
	int size;

	cin >> size;
	vector<vector<bool>> map(size);
	vector<vector<bool>> visited(size);
	vector<int> result;

	for (auto& vec : map)
		vec.resize(size, false);

	for (auto& vec : visited)
		vec.resize(size, false);

	for (int i = 0; i < size; i++)
	{
		string str;
		cin >> str;

		for (int j = 0; j < str.length(); j++)
		{
			if (str[j] == '1') map[i][j] = true;
			else map[i][j] = false;
		}
	}

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (map[i][j] == true && visited[i][j] == false)
			{
				int count = DFS(map, visited, i, j);

				result.push_back(count);
			}

	sort(result.begin(), result.end());

	cout << result.size() << endl;
	for (auto ele : result)
		cout << ele << endl;

	return 0;
}