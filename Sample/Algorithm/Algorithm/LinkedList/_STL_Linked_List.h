#pragma once

#include<iostream>
#include<list>
using namespace std;

int main()
{
	list<int> l;

	l.push_back(10);
	l.push_back(20);
	l.push_front(0);
	l.push_front(-10);
	//l[1]; //error : 임의 접근 불가능

	
	//======================================================================
	// [인덱스를 이용한 접근이 안되므로 iterator를 사용하여 순차적으로 접근한다.]
	//======================================================================
	{
		//for (int i = 0; i < l.size(); i++)
		//	l[i]; // error

		list<int>::iterator iter = l.begin();
		for (iter; iter != l.end(); ++iter)
			cout << *iter << " ";
		cout << endl;
	}

	//======================================================================
	// [Insert(iter, data) : 해당 iter 위치에 원소를 추가한다. ]
	//======================================================================
	{
		list<int>::iterator iter = l.begin();
		iter = l.begin();
		iter++;
		iter++;
		iter++;

		// -10 0 10 20
		l.insert(iter, 100); // insert(어디에 넣을것인가?, 넣을값)
		for (iter = l.begin(); iter != l.end(); ++iter)
			cout << *iter << " ";
		cout << endl;
	}


	//======================================================================
	// [erase(iter) : 해당 iter가 가리키는 원소를 삭제한다. ]
	//======================================================================
	{
		list<int>::iterator iter = l.begin();

		iter = l.end();
		iter--; iter--;
		l.erase(iter);

		for (iter = l.begin(); iter != l.end(); ++iter)
			cout << *iter << " ";
		cout << endl;
	}


	//======================================================================
	// [remove(data) : 해당 data를 가지는 모든 원소를 삭제한다.
	//======================================================================
	{
		list<int>::iterator iter = l.begin();

		l.remove(0);
		for (iter = l.begin(); iter != l.end(); ++iter)
			cout << *iter << " ";
		cout << endl;
	}

	//////////////////////
	l.clear();

	return 0;
}