#pragma once

// _STL_Stack.h

#include<iostream>
#include<stack>
#include<vector>
#include<list>
using namespace std;

int main()
{
	stack<int> s;				// 기본값으로 deque 컨테이너를 사용
	stack<int, vector<int>> sv; // deque 대신에 vector컨테이너 사용
	stack<int, list<int>> sl;	// deque 대신에 list컨테이너 사용

	s.push(10);
	s.push(20);
	s.push(30);
	s.push(40);

	while (s.empty() != true)
	{
		cout << s.top() << endl;
		s.pop();
	}

	return 0;
}