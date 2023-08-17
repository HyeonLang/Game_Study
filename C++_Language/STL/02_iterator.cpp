// 02_iterator.cpp

/*
	iterator - �ݺ���
	- �����̳� ���ҿ� ������ �� �ִ� �����Ϳ� ���� ��ü
	- �����Ϳ� ���� ���ҿ� �����ϹǷ� �ݺ��ڸ� ����Ͽ� 
	�����̳ʿ� ����� ������ Ÿ�Կ� ������� �˰����� ����� �� �ְ� ���ش�.
*/

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
using namespace std;

int main() {
	// �����̳� ���ҿ� �����ϴ� ����� �ݺ��ڷ� �Ϲ�ȭ �Ǿ��־� �ڵ� ������ ������.

	// vector
	{
		vector<int> container;
		for (int i = 0; i < 10; i++)
			container.push_back(i);
		
		std::vector<int>::iterator iter; // �ݺ��� ����
		/*
								end() : �����̳� ������ ���� ��ĭ �ڸ� ����Ű�� �ݺ���
							    ��
			0 1 2 3 4 5 6 7 8 9
			��
			begin() : �����̳��� ù ��° ���Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ
		*/
		iter = container.begin();
		while (iter != container.end()) {
			cout << *iter << " ";
			++iter;
		}
		cout << endl;

		for (auto iter = container.begin(); iter != container.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
	}

	// list
	{
		list<int> container;
		for (int i = 0; i < 10; i++)
			container.push_back(i);

		for (auto iter = container.begin(); iter != container.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
	}

	// set
	{
		set<int> container;
		for (int i = 0; i < 10; i++)
			container.insert(i);

		for (auto iter = container.begin(); iter != container.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
	}

	// map
	{
		map<int, char> container;
		for (int i = 0; i < 10; i++)
			container.insert(make_pair(i, i + 65));

		for (auto iter = container.begin(); iter != container.end(); iter++) {
			cout << iter->first << " " << iter->second  << " / ";
		}
		cout << endl;
	}

	return 0;
}