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
	//l[1]; //error : ���� ���� �Ұ���

	
	//======================================================================
	// [�ε����� �̿��� ������ �ȵǹǷ� iterator�� ����Ͽ� ���������� �����Ѵ�.]
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
	// [Insert(iter, data) : �ش� iter ��ġ�� ���Ҹ� �߰��Ѵ�. ]
	//======================================================================
	{
		list<int>::iterator iter = l.begin();
		iter = l.begin();
		iter++;
		iter++;
		iter++;

		// -10 0 10 20
		l.insert(iter, 100); // insert(��� �������ΰ�?, ������)
		for (iter = l.begin(); iter != l.end(); ++iter)
			cout << *iter << " ";
		cout << endl;
	}


	//======================================================================
	// [erase(iter) : �ش� iter�� ����Ű�� ���Ҹ� �����Ѵ�. ]
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
	// [remove(data) : �ش� data�� ������ ��� ���Ҹ� �����Ѵ�.
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