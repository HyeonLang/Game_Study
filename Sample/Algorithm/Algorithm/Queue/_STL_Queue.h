#pragma once

#include<iostream>
#include<queue>
using namespace std;

int main()
{
	//Enqueue : Push
	//Dequeue : Pop
	//Empty

	// 큐는 반복자 지원 x, 임의접근안됨 -> 필요하면 큐를 쓰면 안된다.
	cout << "queue" << endl;
	queue<int> q;
	q.push(10);
	q.push(20);
	q.push(30);
	q.push(40);
	q.push(50);

	while (q.empty() == false)
	{
		cout << q.front() << endl;
		cout << q.back() << endl << endl;

		q.pop();
	}
	cout << endl;

	return 0;
}