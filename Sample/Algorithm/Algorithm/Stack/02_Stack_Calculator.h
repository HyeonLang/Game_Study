#pragma once

// 02_Stack_Calculator.h

/*
	�� ���� ���� ���� ǥ���

		�� ���� ǥ���(in-fix)
			�� �ǿ����� ���̿� �����ڸ� �δ� ���
			�� 1 + 2

		�� ���� ǥ���(pre-fix)
			�� �ǿ����� �տ� �����ڸ� �δ� ���
			�� + 1 2

		�� ���� ǥ���(post-fix.
			�� �ǿ����� �ڿ� �����ڸ� �δ� ���
			�� 1 2 +

	-> ����� ���� ����� �������� ��ǻ�ʹ� ����, ���� ����� ����

	�� �������� ������ ���������� ��ȯ�ϴ� ��

		�� ��ȯ��
			1. ���� ���� �켱������ ���� ��ȣ�� �����ش�.
			2. ����, ������ ���� ��ȣ�ȿ� �ִ� �����ڸ� ���̳� �ڷ� �Ű��ش�.
			3. ��ȣ�� �����Ѵ�.

		�� �������� ���������� ��ȯ
			0. ������ : 3 + 4 * 2 / 2 + 32 - 6 * 7
			1. (((3 + ((4 * 2) / 2)) + 32) - (6 * 7))
			2. (((3 ((4 2 *) 2 /) +) 32) + (6 7 *) -)
			3. 3 4 2 * 2 / + 32 + 6 7 * -

		-> ���⼭ �����ڸ� ������ �ű�� ������ ǥ��

	�� �������� ���������� �ٲٴ� �˰�����
		�� ��ȯ��
			1. ���ڸ� ������ ������ ���ۿ� ����, ���ڸ� �����ϴ� ���ӵ� ���ڸ� ��� �����ؼ�
			�ϳ��� ���ڷ� �����, �̾����� �ǿ����ڿ��� ������ ���� ������ �ϳ� �����Ѵ�.

			ex)
			1111 * �̸�
			1 * 111, 11 * 11 111 * 1  ������ �ȵ�
			-> 11 11 * �̷������� �־��ش�.

			2. �����ڸ� ������ ���ÿ� �ִ´�. �� ��° ���ʹ� '('�� ������ �����ڴ� ������ �˻��Ͽ� �ڽ�(������)����
			�켱������ ���ų� ���� �����ڵ��� ��� ������ ���ۿ� �ִ´�.

			3. ���� ��ȣ'('�� ������ ���ÿ� �ִ´�. ���ÿ��� �켱������ �����ڸ�
			������ �������ΰ� �� �����ϱ� �����̴�.

			4. �ݴ� ��ȣ ')'�� ������ ���þȿ� �ִ� ���� ��ȣ'('�� ������ ���� ���� �ȿ� �ִ�
			�����ڵ��� ��� ���ۿ� �־��ش�.

			5. 1 ~ 4���� �ݺ��� �ϰ�, ��� ������ ������, ���ÿ� �����ִ� �����ڵ��� ������
			���ۿ� �־��ش�.

		�� �켱����
			�� �������� �켱���Ѵ�.

			0 : (
			1 : + -
			2 : * /
			3 : ^

			{

	�� ������ ó�� �˰�����
		1. �����Ŀ� ó������ ���� �о�鼭 ���� ���� �����϶��� �������϶��� ���� ó�����ش�.

		2. �����ϰ�� ���� �����͸� �о ���� ���ÿ� �־��ش�.

		3. �������ϰ�� ���� ���ÿ��� 2���� ���� ���� �����ڿ� �˸��� ������ �Ѵ����� 
		���� ���ÿ� ��� ����� �־��ش�.

		4. �� ������ �������� '\0'�� ���������� �ݺ��Ѵٸ� ���� ���ÿ� ���� ��� ����� ���Եȴ�.


*/

#include <stack>
#include<cctype> // isdigit(int _C) : 10������ ������ �� �ִ� ���ڰ� �ƴϸ� 0 ��ȯ �����ϸ� 0���� �� ��ȯ
#include <assert.h> 
using namespace std;

class Stack_Calculator
{
public:
	// �Է¹��� �������� �켱������ ��ȯ���ִ� �Լ�
	static int GetPriority(char op)
	{
		switch (op)
		{
		case '(':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
		}

		return 100;
	}

	// ���� ������ mid�� ���������� �ٲپ� post�� �־��ش�.
	static void MakePostfix(char* post, const char* mid)
	{
		const char* expression = mid;
		char* new_exp = post;

		int i = 0;
		char temp;

		stack<char> cs;

		while (expression[i] != '\0')
		{
			if (isdigit(expression[i]) != false)
			{
				while(isdigit(expression[i]) != false || expression[i] == '.')
					*new_exp++ = expression[i++];

				*new_exp++ = ' ';
			}
			else
			{
				if (strchr("^*/+-", expression[i]) != nullptr)
				{
					while (cs.empty() != true
						&& GetPriority(cs.top()) >= GetPriority(expression[i]))
					{
						*new_exp++ = cs.top();
						cs.pop();
					}
					cs.push(expression[i++]);
				}
				else if (expression[i] == '(')
				{
					cs.push(expression[i++]);
				}
				else if (expression[i] == ')')
				{
					while (true)
					{
						temp = cs.top();
						cs.pop();
						if (temp == '(')
							break;
						*new_exp++ = temp;
					}
					i++;
				}
				else
					i++;
			}

		} // while (expression[i] != '\0')


		while (cs.empty() != true)
		{
			*new_exp++ = cs.top();
			cs.pop();
		}

		*new_exp = '\0';
	}

	// �������� �Է¹޾� ����� ����� ��ȯ���ش�.
	static double CalcPostfix(const char* post)
	{
		const char* p = post;
		double left, right;
		stack<double> ds;

		while (*p)
		{
			if (isdigit(*p) != false)
			{
				ds.push(atof(p));

				while (isdigit(*p) != false || *p == '.')
					p++;
			}
			else if (strchr("^*/+-", *p) != nullptr)
			{
				right = ds.top();
				ds.pop();

				left = ds.top();
				ds.pop();

				switch (*p)
				{
				case '+': ds.push(left + right); break;
				case '-': ds.push(left - right); break;
				case '*': ds.push(left * right); break;
				case '^': ds.push(pow(left, right)); break;
				case '/':
					assert(right != 0.0);
					ds.push(left / right);
					break;

				}
				p++;
			}
			else
				p++;
		} // while (*p)

		return ds.top();
	}
};

#include<iostream>
using namespace std;

int main()
{
	//1 10 2 *+5 +
	{
		char post[256];
		const char* mid = "1+10*2+5";

		Stack_Calculator::MakePostfix(&post[0], mid);

		cout << post << endl;
		cout << Stack_Calculator::CalcPostfix(post) << endl;
	}

	//1 10 +2 *5 +
	{
		char post[256];
		const char* mid = "(1+10)*2+5";

		Stack_Calculator::MakePostfix(&post[0], mid);

		cout << post << endl;
	}

	// 1.5 1 +
	{
		char post[256];
		const char* mid = "1.5+1";

		Stack_Calculator::MakePostfix(&post[0], mid);

		cout << post << endl;
	}

	return 0;
}