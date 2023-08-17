// 01_stl_and_container.cpp

/*
	STL
	- 컨테이너(container), 반복자(iterator), 알고리즘(algorithm) 등으로 이루어진 라이브러리
	- 템플릿을 사용하여 어떠한 타입의 데이터로 위의 라이브러리를 사용할 수 있도록 일반화 하였다.
		-> 자료형을 일반화 하여 코드의 수정없이 동일한 작업을 수행할 수 있다.

	컨테이너(container)
	- 임의 타입의 데이터를 보관할 수 있다.

	반복자(iterator)
	- 컨테이너에 보관된 원소에 접근할 때 사용한다.

	알고리즘(algorithm)
	- 반복자들을 가지고 일련의 작업을 수행한다.

	//과제 : std, stl 조사
*/

/*
	container - 컨테이너
	- 동일한 자료형의 여러 객체를 저장한느 집합 혹은 저장소를 의미한다.
	- 템플릿을 사용해 저장하는 데이터의 자료형에 무관하게 무엇이든 담을 수 있도록 설계되어 있다.
	- sequence, associative, adapter 컨테이너 종류가 있다.
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
	- 배열처럼 데이터를 선형으로 저장하는 컨테이너
	- 특별한 제약이나 규칙없이 원소를 보관한다.

*/
void Sequence_Container() // 순차 컨테이너
{
	/*
		vector
		- 가변 길이 배열, 동적 배열을 템플릿화 한 것
		- 원소가 실제 메모리에 순차적으로 저장되어있어 연속적인 데이터를 처리하기에 유리하다.
		- 임의 접근을 제공한다. [], at()
		- 할당된 공간을 다 채웠을 경우, 새로운 큰 공간을 동적으로 재할당하여 원소들을 복사한다.
		- 맨 뒤에 원소를 삽입, 삭제할때는 빠르나 임의의 위치에 있는 원소들을 삽입, 삭제 하는 경우에는
		그 뒤 원소를 한칸씩 밀거나 당겨야하기 때문에 느리다.

		사용하기 좋은 경우
		- 크기가 예측이 가능 한 경우
		- 데이터의 삽입 삭제가 별로 없는 경우 
		- 연속적인 데이터 처리가 필요한 경우
	*/
	{
		vector<int> vec; //template이며 template 클래스로 만들어진 객체(배열처럼 연속적인 메모리를 가지고 있음)
		for (int i = 0; i < 10; i++)
			vec.push_back(i);

		//vec.size();		// 데이터의 수
		//vec.capacity();	// 가용 공간의 수

		for (const auto& ele : vec)
			cout << ele << ' ';
		cout << endl;
	}

	/*
		Deque
		- 벡터와 비슷하지만, 벡터와는 다르게 원소가 메모리 공간에 연속적으로 존재하지 않음
		- 메모리를 재할당할 때, 추가로 메모리 공간을 만들어 논리적으로 이어붙인다. => 데이터 할당이 빠름
		- 서로 떨어져있는 메모리 공간의 정보를 보관하기 위해 벡터보다 추가적인 메모리가 필요하다.
		- 벡터와 다르게 맨 앞 원소의 삽입, 삭제가 맨 뒤 원소의 삽입, 삭제 하는것과 동일하게 빠르다.
		- 임의의 위치에 있는 원소의 삽입, 삭제가 벡터보다 빠르다.
		- 임의 접근을 제공한다. [], at()

		사용하기 좋은 경우
		- 맨 앞과 맨 뒤의 원소를 삽입, 삭제하는 경우가 빈번한 경우
		- 벡터처럼 사용하고 싶지만 크기가 예측이 안되는 경우
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
		- 양방향 연결 리스트를 템플릿화한 것
		- 리스트는 시작 원소의 주소와 마지막 원소의 위치만을 기억한다.

		- 각각의 원소가 자신의 앞과 뒤에 오는 원소를 가리키고 있다.
		ex)구조 예시
			->, <- 는 포인터로 앞과 뒤의 원소의 주소를 저장하고 있다.
			ㅁㅁㅁ        ㅁㅁㅁ        ㅁㅁㅁ
			ㅁ원ㅁ   ->   ㅁ원ㅁ   ->   ㅁ원ㅁ
			ㅁ소ㅁ		  ㅁ소ㅁ        ㅁ소ㅁ
			ㅁ1 ㅁ   <-   ㅁ2 ㅁ   <-   ㅁ3 ㅁ
			ㅁㅁㅁ        ㅁㅁㅁ        ㅁㅁㅁ

		- 위의 구조를 가지고 있어 임의의 위치에 있는 원소에 바로 접근이 안되고 순차적으로 접근해야 한다.
		- 원소의 삽입, 삭제가 일어날 경우 링크만 바꿔주면 되기에 삽입, 삭제가 빠르다.
		- 리스트를 남발 할 경우 메모리 단편화 현상이 일어날 수 있다. 
		
		사용하기 좋은 경우
		- 원소의 삽입, 삭제가 빈번하게 이루어 질 경우
		- 원소의 접근이 순차적으로 접근하는 경우
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
	- 데이터를 일정한 규칙에 따라 저장하고 관리하는 컨테이너
	- 저장한 요소의 위치를 지정할 수 없고 RB-Tree나 해시 테이블을 이용하여 구현되어 있다.
	- 원소를 삽입할 경우 자동으로 정렬해주기 때문에 탐색이 빠르다.
	- 키(key) - 값(value) 구조를 가진다. => 특정한 키값을 넣으면 대응하는 값을 돌려준다.

*/
void Associative_Container()
{
	/*
		 set과 multiset
		 - 저장하는 데이터값 그 자체를 키로 사용한다
		 - 데이터의 존재 유무를 체크할 때 유리
	*/

	//set - 키의 중복을 허용하지 않는다.
	{
		set<string> str_set;

		str_set.insert("Hello");
		str_set.insert("World");
		str_set.insert("Hello"); // 중복이므로 들어가지 않음. 데이터 중복 체크시 유리

		cout << str_set.size() << endl; // 2

		for (const auto& ele : str_set)
			cout << ele << ' ';
		cout << endl;
	}

	//multiset - 키의 중복을 허용한다.
	{
		multiset<string> str_set;

		str_set.insert("Hello");
		str_set.insert("World");
		str_set.insert("Hello"); // 중복을 허용

		cout << str_set.size() << endl; // 3

		for (const auto& ele : str_set) // Hello Hello World
			cout << ele << ' ';
		cout << endl;
	}

	/*
		 map과 multimap
		 - 키와 값으로 데이터를 관리한다.
		 - map은 중복은 허용하지 않지만 multimap은 중복을 허용해 하나의 키가 여러 값과 연결될 수 있다.
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

	//multimap : duplicated keys (키값(set)이 중복될 수 있다)
	{
		std::multimap<char, int> multimap;
		multimap.insert(pair<char, int>('a', 10));
		multimap.insert(pair<char, int>('b', 100));
		//multimap.insert(pair('c', 1000)); //c++17 -> pair('a', 10); ok. 
		multimap.insert(make_pair('a', 10000));

		cout << multimap.count('a') << endl; // 2 : a키에 걸린 데이터의 수

		for (const auto& ele : multimap)
			cout << ele.first << ' ' << ele.second << ' '; //a 10 a 10000 b 100
		cout << endl;
	}

	/*
	   unordered associative container - 정렬되지 않은 연관 컨테이너
	   - 위의 연관 컨테이너는 트리를 사용하지만
	   정렬되지 않은 원소를 저장할 때 해시 테이블을 사용한다.
	   - 삽입, 삭제, 검색 모두 빠르다.

	   - unordered_set
	   - unordered_multiset
	   - unordered_map
	   - unordered_multimap

	   과제 : 해시테이블 조사
	*/
}



/*
	adapter container
	- 기존의 컨테이너의 인터페이스를 제한하여 만들어 기능이 제한되거나 변형된 컨테이너
	- 각각의 기초가 되는 클래스의 인터페이스를 제한하여 특정 형태의 동작만을 수행하도록 한다.
	- 반복자를 지원하지 않아 stl 알고리즘 사용이 불가하다.
	EX) stack, queue...
*/
void Container_Adapter()
{
	/*
		Stack
		- 선형 데이터를 저장하고 후입선출(LIFO) 구조를 가진다.
		
		Last - in, First - out
		- 가장 마지막에 저장된 데이터가 가장 먼저 나온다.

	*/
	//stack 
	{
		cout << "Stack" << endl;

		std::stack<int> stack;

		//과제  : enplace, push 차이 조사
		stack.push(1);
		stack.emplace(2); // emplace : <int>의 생성자 매개변수를 받는다.
		stack.emplace(3);

		cout << stack.top() << endl; // 값을 읽는다. // 3
		stack.pop(); // 가장 마지막에 들어간 원소를 제거한다.
		cout << stack.top() << endl; // 2
	}

	/*
		Queue
		- 선형으로 데이터를 저장하고 선입선출(FIFO)를 따른다.

		First - in, First - out
		- 가장 먼저 저장된 데이터가 가장 먼저 나온다.
	*/
	{
		cout << "Queue" << endl;

		std::queue<int> queue;

		queue.push(1);
		queue.push(2);
		queue.push(3);

		cout << queue.front() << ' ' << queue.back() << endl; //앞과 뒤에 접근 1/3
		queue.pop(); // 먼저 들어간 원소를 제거 : 맨 앞 원소 제거
		cout << queue.front() << ' ' << queue.back() << endl; //pop 후에는 2/3
	}

	/*
		Priority Queue
		- 우선순위 큐, 우선순위 높은 데이터를 먼저 꺼내는 구조
		- 우선순위 큐는 힙 트리로 구현되어 있다.
		- Queue와는 다르게 우선순위가 가장 큰 데이터가 앞에 위치하게 된다.
	*/
	{
		cout << "Priority queue" << endl;

		priority_queue<int> priority_queue; // default : 내림차순

		for (const int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
			priority_queue.push(n);

		for (int i = 0; i < 10; i++)
		{
			cout << priority_queue.top() << endl; // 출력 : 9 8 7 6 5 4 3 2 1 0
			priority_queue.pop();
		}
	}
}


