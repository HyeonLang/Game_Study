// 02_iterator.cpp

/*
	iterator - 반복자
	- 컨테이너 원소에 접근할 수 있는 포인터와 같은 객체
	- 포인터와 같이 원소에 접근하므로 반복자를 사용하여 
	컨테이너와 저장된 데이터 타입에 상관없이 알고리즘을 사용할 수 있게 해준다.
*/

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
using namespace std;

int main() {
	// 컨테이너 원소에 접근하는 방법이 반복자로 일반화 되어있어 코드 수정이 간편함.

	// vector
	{
		vector<int> container;
		for (int i = 0; i < 10; i++)
			container.push_back(i);
		
		std::vector<int>::iterator iter; // 반복자 선언
		/*
								end() : 컨테이너 마지막 원소 한칸 뒤를 가리키는 반복자
							    ↓
			0 1 2 3 4 5 6 7 8 9
			↑
			begin() : 컨테이너의 첫 번째 원소를 가리키는 반복자를 반환
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