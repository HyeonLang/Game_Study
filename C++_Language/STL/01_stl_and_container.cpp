// 01_stl_and_container.cpp

/*
	STL
	- �����̳�(container), �ݺ���(iterator), �˰���(algorithm) ������ �̷���� ���̺귯��
	- ���ø��� ����Ͽ� ��� Ÿ���� �����ͷ� ���� ���̺귯���� ����� �� �ֵ��� �Ϲ�ȭ �Ͽ���.
		-> �ڷ����� �Ϲ�ȭ �Ͽ� �ڵ��� �������� ������ �۾��� ������ �� �ִ�.

	�����̳�(container)
	- ���� Ÿ���� �����͸� ������ �� �ִ�.

	�ݺ���(iterator)
	- �����̳ʿ� ������ ���ҿ� ������ �� ����Ѵ�.

	�˰���(algorithm)
	- �ݺ��ڵ��� ������ �Ϸ��� �۾��� �����Ѵ�.

	//���� : std, stl ����
*/

/*
	container - �����̳�
	- ������ �ڷ����� ���� ��ü�� �����Ѵ� ���� Ȥ�� ����Ҹ� �ǹ��Ѵ�.
	- ���ø��� ����� �����ϴ� �������� �ڷ����� �����ϰ� �����̵� ���� �� �ֵ��� ����Ǿ� �ִ�.
	- sequence, associative, adapter �����̳� ������ �ִ�.
*/

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;

void Sequence_Container();
void Associative_Container();
void Container_Adapter();


int main() {
	Sequence_Container();
	Associative_Container();
	Container_Adapter();

	return 0;
}

/*
	sequence container
	- �迭ó�� �����͸� �������� �����ϴ� �����̳�
	- Ư���� �����̳� ��Ģ���� ���Ҹ� �����Ѵ�.

*/
void Sequence_Container() // ���� �����̳�
{
	/*
		vector
		- ���� ���� �迭, ���� �迭�� ���ø�ȭ �� ��
		- ���Ұ� ���� �޸𸮿� ���������� ����Ǿ��־� �������� �����͸� ó���ϱ⿡ �����ϴ�.
		- ���� ������ �����Ѵ�. [], at()
		- �Ҵ�� ������ �� ä���� ���, ���ο� ū ������ �������� ���Ҵ��Ͽ� ���ҵ��� �����Ѵ�.
		- �� �ڿ� ���Ҹ� ����, �����Ҷ��� ������ ������ ��ġ�� �ִ� ���ҵ��� ����, ���� �ϴ� ��쿡��
		�� �� ���Ҹ� ��ĭ�� �аų� ��ܾ��ϱ� ������ ������.

		����ϱ� ���� ���
		- ũ�Ⱑ ������ ���� �� ���
		- �������� ���� ������ ���� ���� ��� 
		- �������� ������ ó���� �ʿ��� ���
	*/
	{
		vector<int> vec; //template�̸� template Ŭ������ ������� ��ü(�迭ó�� �������� �޸𸮸� ������ ����)
		for (int i = 0; i < 10; i++)
			vec.push_back(i);

		//vec.size();		// �������� ��
		//vec.capacity();	// ���� ������ ��

		for (const auto& ele : vec)
			cout << ele << ' ';
		cout << endl;
	}

	/*
		Deque
		- ���Ϳ� ���������, ���Ϳʹ� �ٸ��� ���Ұ� �޸� ������ ���������� �������� ����
		- �޸𸮸� ���Ҵ��� ��, �߰��� �޸� ������ ����� �������� �̾���δ�. => ������ �Ҵ��� ����
		- ���� �������ִ� �޸� ������ ������ �����ϱ� ���� ���ͺ��� �߰����� �޸𸮰� �ʿ��ϴ�.
		- ���Ϳ� �ٸ��� �� �� ������ ����, ������ �� �� ������ ����, ���� �ϴ°Ͱ� �����ϰ� ������.
		- ������ ��ġ�� �ִ� ������ ����, ������ ���ͺ��� ������.
		- ���� ������ �����Ѵ�. [], at()

		����ϱ� ���� ���
		- �� �հ� �� ���� ���Ҹ� ����, �����ϴ� ��찡 ����� ���
		- ����ó�� ����ϰ� ������ ũ�Ⱑ ������ �ȵǴ� ���
	*/
	{
		deque<int> deq;
		for (int i = 0; i < 10; i++)
		{
			deq.push_back(i);
			deq.push_front(i);
		}

		for (const auto& ele : deq)
			cout << ele << ' ';
		cout << endl;
	}

	/*
		List
		- ����� ���� ����Ʈ�� ���ø�ȭ�� ��
		- ����Ʈ�� ���� ������ �ּҿ� ������ ������ ��ġ���� ����Ѵ�.

		- ������ ���Ұ� �ڽ��� �հ� �ڿ� ���� ���Ҹ� ����Ű�� �ִ�.
		ex)���� ����
			->, <- �� �����ͷ� �հ� ���� ������ �ּҸ� �����ϰ� �ִ�.
			������        ������        ������
			������   ->   ������   ->   ������
			���Ҥ�		  ���Ҥ�        ���Ҥ�
			��1 ��   <-   ��2 ��   <-   ��3 ��
			������        ������        ������

		- ���� ������ ������ �־� ������ ��ġ�� �ִ� ���ҿ� �ٷ� ������ �ȵǰ� ���������� �����ؾ� �Ѵ�.
		- ������ ����, ������ �Ͼ ��� ��ũ�� �ٲ��ָ� �Ǳ⿡ ����, ������ ������.
		- ����Ʈ�� ���� �� ��� �޸� ����ȭ ������ �Ͼ �� �ִ�. 
		
		����ϱ� ���� ���
		- ������ ����, ������ ����ϰ� �̷�� �� ���
		- ������ ������ ���������� �����ϴ� ���
	*/
	{
		list<int> list;

		for (int i = 0; i < 10; i++)
			list.push_back(i);

		for (const auto& ele : list)
			cout << ele << ' ';
		cout << endl;
	}
}


/*
	associative container
	- �����͸� ������ ��Ģ�� ���� �����ϰ� �����ϴ� �����̳�
	- ������ ����� ��ġ�� ������ �� ���� RB-Tree�� �ؽ� ���̺��� �̿��Ͽ� �����Ǿ� �ִ�.
	- ���Ҹ� ������ ��� �ڵ����� �������ֱ� ������ Ž���� ������.
	- Ű(key) - ��(value) ������ ������. => Ư���� Ű���� ������ �����ϴ� ���� �����ش�.

*/
void Associative_Container()
{
	/*
		 set�� multiset
		 - �����ϴ� �����Ͱ� �� ��ü�� Ű�� ����Ѵ�
		 - �������� ���� ������ üũ�� �� ����
	*/

	//set - Ű�� �ߺ��� ������� �ʴ´�.
	{
		set<string> str_set;

		str_set.insert("Hello");
		str_set.insert("World");
		str_set.insert("Hello"); // �ߺ��̹Ƿ� ���� ����. ������ �ߺ� üũ�� ����

		cout << str_set.size() << endl; // 2

		for (const auto& ele : str_set)
			cout << ele << ' ';
		cout << endl;
	}

	//multiset - Ű�� �ߺ��� ����Ѵ�.
	{
		multiset<string> str_set;

		str_set.insert("Hello");
		str_set.insert("World");
		str_set.insert("Hello"); // �ߺ��� ���

		cout << str_set.size() << endl; // 3

		for (const auto& ele : str_set) // Hello Hello World
			cout << ele << ' ';
		cout << endl;
	}

	/*
		 map�� multimap
		 - Ű�� ������ �����͸� �����Ѵ�.
		 - map�� �ߺ��� ������� ������ multimap�� �ߺ��� ����� �ϳ��� Ű�� ���� ���� ����� �� �ִ�.
	*/

	//map : key/value - pair 
	{
		map<char, int> map;
		map['c'] = 50;
		map['a'] = 10;
		map['d'] = 40;
		map['b'] = 20;

		cout << map['a'] << endl;

		map['a'] = 100;
		cout << map['a'] << endl;

		for (const auto& ele : map)
			cout << ele.first << ' ' << ele.second << ' ';
		cout << endl;


	}

	//multimap : duplicated keys (Ű��(set)�� �ߺ��� �� �ִ�)
	{
		std::multimap<char, int> multimap;
		multimap.insert(pair<char, int>('a', 10));
		multimap.insert(pair<char, int>('b', 100));
		//multimap.insert(pair('c', 1000)); //c++17 -> pair('a', 10); ok. 
		multimap.insert(make_pair('a', 10000));

		cout << multimap.count('a') << endl; // 2 : aŰ�� �ɸ� �������� ��

		for (const auto& ele : multimap)
			cout << ele.first << ' ' << ele.second << ' '; //a 10 a 10000 b 100
		cout << endl;
	}

	/*
	   unordered associative container - ���ĵ��� ���� ���� �����̳�
	   - ���� ���� �����̳ʴ� Ʈ���� ���������
	   ���ĵ��� ���� ���Ҹ� ������ �� �ؽ� ���̺��� ����Ѵ�.
	   - ����, ����, �˻� ��� ������.

	   - unordered_set
	   - unordered_multiset
	   - unordered_map
	   - unordered_multimap

	   ���� : �ؽ����̺� ����
	*/
}



/*
	adapter container
	- ������ �����̳��� �������̽��� �����Ͽ� ����� ����� ���ѵǰų� ������ �����̳�
	- ������ ���ʰ� �Ǵ� Ŭ������ �������̽��� �����Ͽ� Ư�� ������ ���۸��� �����ϵ��� �Ѵ�.
	- �ݺ��ڸ� �������� �ʾ� stl �˰��� ����� �Ұ��ϴ�.
	EX) stack, queue...
*/
void Container_Adapter()
{
	/*
		Stack
		- ���� �����͸� �����ϰ� ���Լ���(LIFO) ������ ������.
		
		Last - in, First - out
		- ���� �������� ����� �����Ͱ� ���� ���� ���´�.

	*/
	//stack 
	{
		cout << "Stack" << endl;

		std::stack<int> stack;

		//����  : enplace, push ���� ����
		stack.push(1);
		stack.emplace(2); // emplace : <int>�� ������ �Ű������� �޴´�.
		stack.emplace(3);

		cout << stack.top() << endl; // ���� �д´�. // 3
		stack.pop(); // ���� �������� �� ���Ҹ� �����Ѵ�.
		cout << stack.top() << endl; // 2
	}

	/*
		Queue
		- �������� �����͸� �����ϰ� ���Լ���(FIFO)�� ������.

		First - in, First - out
		- ���� ���� ����� �����Ͱ� ���� ���� ���´�.
	*/
	{
		cout << "Queue" << endl;

		std::queue<int> queue;

		queue.push(1);
		queue.push(2);
		queue.push(3);

		cout << queue.front() << ' ' << queue.back() << endl; //�հ� �ڿ� ���� 1/3
		queue.pop(); // ���� �� ���Ҹ� ���� : �� �� ���� ����
		cout << queue.front() << ' ' << queue.back() << endl; //pop �Ŀ��� 2/3
	}

	/*
		Priority Queue
		- �켱���� ť, �켱���� ���� �����͸� ���� ������ ����
		- �켱���� ť�� �� Ʈ���� �����Ǿ� �ִ�.
		- Queue�ʹ� �ٸ��� �켱������ ���� ū �����Ͱ� �տ� ��ġ�ϰ� �ȴ�.
	*/
	{
		cout << "Priority queue" << endl;

		priority_queue<int> priority_queue; // default : ��������

		for (const int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
			priority_queue.push(n);

		for (int i = 0; i < 10; i++)
		{
			cout << priority_queue.top() << endl; // ��� : 9 8 7 6 5 4 3 2 1 0
			priority_queue.pop();
		}
	}
}


