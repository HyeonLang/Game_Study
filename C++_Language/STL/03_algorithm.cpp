// 03_algorithm.cpp

/*
   algorithm Library
   - 컨테이너의 반복자를 사용하여 여러 작업을 쉽게 수행하게 도와주는 라이브러리
*/
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<random>

using namespace std;

//난수
random_device rd;
mt19937_64 mt(rd());

int main()
{
    // 여러가지 알고리즘 있음

    vector<int> container;
    //list<int> container;

    for (int i = 0; i < 10; ++i)
        container.push_back(i);

    //list를 사용할 경우 에러남
    shuffle(container.begin(), container.end(), mt);

    for (auto iter = container.begin(); iter != container.end(); iter++)
        cout << *iter << " ";
    cout << endl;

    // 범위의 최소값 찾아줌
    auto iter = min_element(container.begin(), container.end());
    cout << *iter << endl;

    // 최대값
    iter = max_element(container.begin(), container.end());
    cout << *iter << endl;

    // 원하는 원소 찾기 
    iter = find(container.begin(), container.end(), 7); // 못찾으면 end 리턴
    cout << *iter << endl;

    // 퀵정렬시켜줌 
    sort(container.begin(), container.end()); // 리스트는 내부에 sort가 있어서 지원안함
    //container.sort(); // list는 정렬 방법이 다름

    return 0;
}