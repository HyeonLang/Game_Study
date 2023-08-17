#pragma once

#include<iostream>
#include<string>
#include<stack>
using namespace std;

int main()
{
	/*
		�� cin
			�� �Է� ���ۿ��� '\t', '\n', ' '�� �б� �������� �����͸� �Է¹޴´�.
			�� �Է¹��� �����͸� �����ϱ� ���� �̿��� '\t', '\n', ' '�������� ������ ���ۿ��� �����Ѵ�.
			�� ���ۿ��� �����͸� �Է¹ޱ����� ���� '\t', '\n', ' '�� �����Ѵ�.

		�� getline()
			�� ���ۿ��� delim(���� �������� ������� '\n')�� ������ �������� �����͸� �Է¹޴´�.
			�� �Է¹��� �����Ϳ� ���� delim�� ���ۿ��� �����Ѵ�.

		�� cin�� getline()�� ���� ����� �� �߻��� �� �ִ� ������
			�� cin�� ���� �Է��� �޴´ٸ� ���ۿ��� '\n'���ڰ� ���� �ȴ�.
			�� �Ŀ� getline()�� ���� �Է��� �������� �õ��� ��� ���� �Ǿտ� '\n'�� �����ִ�
			��찡 ���� '\n'�� ���ۿ��� �����ϰ� �ƹ��� �Է��� �������ϴ� ������ �����.
			-> ���ۿ��� '\n'�� ���� ������ �ذ��Ѵ�.

		�� ignore(count, delim)
			�� �Է� ���ۿ��� ó�� ������ delim������ �����͵��� ���ۿ��� �����Ѵ�.
			�� ���� �Է� ���ۿ� delim�� ���ٸ� count������ŭ�� �����Ͱ� ���ŵȴ�.
			�� �⺻���� ���� count = 1, delim = -1(EOF : ������ ��)�̴�.
	*/

	int t;
	cin >> t;
	cin.ignore(); // ignore()�� �Է� ���ۿ� �����ִ� '\n'�� �������ش�.

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
