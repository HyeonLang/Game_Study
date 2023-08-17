// 03_algorithm.cpp

/*
   algorithm Library
   - �����̳��� �ݺ��ڸ� ����Ͽ� ���� �۾��� ���� �����ϰ� �����ִ� ���̺귯��
*/
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<random>

using namespace std;

//����
random_device rd;
mt19937_64 mt(rd());

int main()
{
    // �������� �˰��� ����

    vector<int> container;
    //list<int> container;

    for (int i = 0; i < 10; ++i)
        container.push_back(i);

    //list�� ����� ��� ������
    shuffle(container.begin(), container.end(), mt);

    for (auto iter = container.begin(); iter != container.end(); iter++)
        cout << *iter << " ";
    cout << endl;

    // ������ �ּҰ� ã����
    auto iter = min_element(container.begin(), container.end());
    cout << *iter << endl;

    // �ִ밪
    iter = max_element(container.begin(), container.end());
    cout << *iter << endl;

    // ���ϴ� ���� ã�� 
    iter = find(container.begin(), container.end(), 7); // ��ã���� end ����
    cout << *iter << endl;

    // �����Ľ����� 
    sort(container.begin(), container.end()); // ����Ʈ�� ���ο� sort�� �־ ��������
    //container.sort(); // list�� ���� ����� �ٸ�

    return 0;
}