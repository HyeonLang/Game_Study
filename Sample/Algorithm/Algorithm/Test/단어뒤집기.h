#pragma once

#include<iostream>
#include<string>
#include<stack>
using namespace std;

int main()
{
	/*
		※ cin
			ㄴ 입력 버퍼에서 '\t', '\n', ' '를 읽기 전까지의 데이터를 입력받는다.
			ㄴ 입력받을 데이터를 구분하기 위해 이용한 '\t', '\n', ' '전까지의 내용을 버퍼에서 제거한다.
			ㄴ 버퍼에서 데이터를 입력받기전에 만난 '\t', '\n', ' '는 무시한다.

		※ getline()
			ㄴ 버퍼에서 delim(따로 설정하지 않을경우 '\n')을 만나기 전까지의 데이터를 입력받는다.
			ㄴ 입력받은 데이터와 만난 delim을 버퍼에서 제거한다.

		※ cin과 getline()을 같이 사용할 때 발생할 수 있는 문제점
			ㄴ cin을 통해 입력을 받는다면 버퍼에는 '\n'문자가 남게 된다.
			그 후에 getline()을 통해 입력을 받으려고 시도할 경우 버퍼 맨앞에 '\n'이 남아있는
			경우가 생겨 '\n'만 버퍼에서 제거하고 아무런 입력을 받지못하는 문제가 생긴다.
			-> 버퍼에서 '\n'을 지워 문제를 해결한다.

		※ ignore(count, delim)
			ㄴ 입력 버퍼에서 처음 만나는 delim까지의 데이터들을 버퍼에서 제거한다.
			ㄴ 만약 입력 버퍼에 delim이 없다면 count개수만큼의 데이터가 제거된다.
			ㄴ 기본값은 각각 count = 1, delim = -1(EOF : 파일의 끝)이다.
	*/

	int t;
	cin >> t;
	cin.ignore(); // ignore()로 입력 버퍼에 남아있는 '\n'을 제거해준다.

	for (int i = 0; i < t; ++i)
	{
		string str("");
		getline(cin, str);
		str += ' ';

		stack<char> stack;
		for (int j = 0; j < str.size(); ++j)
		{
			if (str[j] == ' ')
			{
				while (stack.empty() != true)
				{
					cout << stack.top();
					stack.pop();
				}
				cout << ' ';
			}
			else
				stack.push(str[j]);
		}
		cout << endl;
	}
}
