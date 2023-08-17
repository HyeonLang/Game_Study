#pragma once



#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> map;
int result[3] = {};

void solution(int begin_row, int begin_col, int size)
{
    int num = map[begin_row][begin_col];

    bool is_same = true;

    for (int y = begin_row; y < begin_row + size; y++)
    {
        for (int x = begin_col; x < begin_col + size; x++)
            if (num != map[y][x])
            {
                is_same = false;
                break;
            }

        if (is_same == false)
            break;
    }

    if (is_same)
    {
        result[num + 1]++;
    }
    // 아니라면 문제 분할
    else
    {
        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
            {
                solution(begin_row + y * (size / 3), begin_col + x * (size / 3), size / 3);
            }
    }
}

int main()
{
    int size = 0;
    int data = 0;
    cin >> size;


    map.assign(size, vector<int>());

    for (auto& ele : map)
        ele.assign(size, 0);

    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++)
        {
            cin >> data;
            map[y][x] = data;
        }

    solution(0, 0, size);

    cout << result[0] << endl;
    cout << result[1] << endl;
    cout << result[2] << endl;
}