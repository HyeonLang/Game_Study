#pragma once

// 02_Stack_Calculator.h

/*
	※ 전위 중위 후위 표기법

		ㅁ 중위 표기법(in-fix)
			ㄴ 피연산자 사이에 연산자를 두는 방식
			ㄴ 1 + 2

		ㅁ 전위 표기법(pre-fix)
			ㄴ 피연산자 앞에 연산자를 두는 방식
			ㄴ + 1 2

		ㅁ 후위 표기법(post-fix.
			ㄴ 피연산자 뒤에 연산자를 두는 방식
			ㄴ 1 2 +

	-> 사람은 중위 방식이 편하지만 컴퓨터는 전위, 후위 방식이 편함

	※ 중위식을 전위나 후위식으로 변환하는 법

		ㅁ 변환법
			1. 먼저 연산 우선순위에 따라 괄호로 묶어준다.
			2. 전위, 후위에 따라 괄호안에 있는 연산자를 앞이나 뒤로 옮겨준다.
			3. 괄호를 제거한다.

		ㅁ 중위식을 후위식으로 변환
			0. 중위식 : 3 + 4 * 2 / 2 + 32 - 6 * 7
			1. (((3 + ((4 * 2) / 2)) + 32) - (6 * 7))
			2. (((3 ((4 2 *) 2 /) +) 32) + (6 7 *) -)
			3. 3 4 2 * 2 / + 32 + 6 7 * -

		-> 여기서 연산자를 앞으로 옮기면 전위식 표기

	※ 중위식을 후위식으로 바꾸는 알고리즘
		ㅁ 변환법
			1. 숫자를 만나면 후위식 버퍼에 삽입, 숫자를 구성하는 연속된 문자를 모두 추출해서
			하나의 숫자로 만들고, 이어지는 피연산자와의 구분을 위해 공백을 하나 삽입한다.

			ex)
			1111 * 이면
			1 * 111, 11 * 11 111 * 1  구분이 안됨
			-> 11 11 * 이런식으로 넣어준다.

			2. 연산자를 만나면 스택에 넣는다. 두 번째 부터는 '('를 제외한 연산자는 스택을 검사하여 자신(연산자)보다
			우선순위가 같거나 높은 연산자들을 모두 꺼내서 버퍼에 넣는다.

			3. 여는 괄호'('를 만나면 스택에 넣는다. 스택에서 우선순위의 연산자를
			어디까지 꺼낼것인가 를 결정하기 위함이다.

			4. 닫는 괄호 ')'를 만나면 스택안에 있는 여는 괄호'('를 만날때 까지 스택 안에 있는
			연산자들을 모두 버퍼에 넣어준다.

			5. 1 ~ 4까지 반복을 하고, 모든 과정이 끝나면, 스택에 남아있는 연산자들을 꺼내서
			버퍼에 넣어준다.

		ㅁ 우선순위
			ㄴ 높을수록 우선시한다.

			0 : (
			1 : + -
			2 : * /
			3 : ^

			{

	※ 후위식 처리 알고리즘
		1. 후위식에 처음부터 값을 읽어가면서 읽은 값이 숫자일때와 연산자일때를 따로 처리해준다.

		2. 숫자일경우 숫자 데이터를 읽어서 숫자 스택에 넣어준다.

		3. 연산자일경우 숫자 스택에서 2개의 값을 꺼내 연산자에 알맞은 연산을 한다음에 
		숫자 스택에 계산 결과를 넣어준다.

		4. 위 과정을 후위식을 '\0'을 만날때까지 반복한다면 숫자 스택에 최종 계산 결과가 남게된다.


*/

#include <stack>
#include<cctype> // isdigit(int _C) : 10진수로 변경할 수 있는 문자가 아니면 0 반환 가능하면 0외의 값 반환
#include <assert.h> 
using namespace std;

class Stack_Calculator
{
public:
	// 입력받은 연산자의 우선순위를 반환해주는 함수
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

	// 받은 중위식 mid를 후위식으로 바꾸어 post에 넣어준다.
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

	// 후위식을 입력받아 계산한 결과를 반환해준다.
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