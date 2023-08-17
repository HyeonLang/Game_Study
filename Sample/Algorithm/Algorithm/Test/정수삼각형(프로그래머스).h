#pragma once

#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> triangle) {

    vector<vector<int>> temp;

    temp.assign(triangle.size(), vector<int>());

    int answer = 0;

    temp[0].push_back(triangle[0][0]);
    for (int y = 1; y < triangle.size(); y++)
    {
        temp[y].assign(triangle[y].size(), 0);
        for (int x = 0; x < triangle[y].size(); x++)
        {
            if (x == 0)
            {
                temp[y][x] = triangle[y][x] + temp[y - 1][x];
            }
            else if (x == triangle[y].size() - 1)
            {
                temp[y][x] = triangle[y][x] + temp[y - 1][x - 1];
            }
            else
            {
                int left = temp[y - 1][x - 1];
                int right = temp[y - 1][x];

                temp[y][x] = triangle[y][x] + (left > right ? left : right);
            }
        }
    }

    sort(temp[triangle.size() - 1].begin(), temp[triangle.size() - 1].end(), greater<int>());
    
    return temp[triangle.size() - 1][0];
}

int main()
{
    vector<vector<int>> triangle;

    triangle.assign(5, vector<int>());

    triangle[0].push_back(7);

    triangle[1].push_back(3);
    triangle[1].push_back(8);
    
    triangle[2].push_back(8);
    triangle[2].push_back(1);
    triangle[2].push_back(0);
    
    triangle[3].push_back(2);
    triangle[3].push_back(7);
    triangle[3].push_back(4);
    triangle[3].push_back(4);
    
    triangle[4].push_back(4);
    triangle[4].push_back(5);
    triangle[4].push_back(2);
    triangle[4].push_back(6);
    triangle[4].push_back(5);


    cout << solution(triangle) << endl;;


    return 0;
}