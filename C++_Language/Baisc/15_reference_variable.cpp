// 15_reference_variable.cpp

/*
	섯다, textrpg, 빙고

	주말과제 : 슈팅 게임
*/


/*
	L-value : 나중에 다시 접근 가능한 값, 메모리를 특정할 수 있는 값
	R-value : 식이 끝나면 접근 불가능한 값, 메모리를 특정할 수 없는 값
*/

#include <iostream>

int Test1(int& a) { return a; }; //L-v 매개변수 : 원본이 넘어온다. 수정시 외부에 영향을 준다.
int Test1(int&& a) { return a; }; //R-v 매개변수 : 원본(상수 값)이 넘어온다. 수정시 외부에 영향을 주지 않는다.

int main() {
	//L-v = R-v
	int a = 10;

	//a : l, 15 : r
	a = 15;
	
	//& : L-value reference (참조) 
	//a ==l, a의 새 별명 l
	int& l = a;
	//l과 a는 같은 메모리 참조
	//int& l = 12; // 불가 
	
	
	//cout << a; : 15
	l = 20; //a가 가리키는 메모리 값을 10으로 변경
	//cout << a; : 20

	//예외적으로 R-value 입력가능 : const
	const int& l1 = 10;
	//const int& l2; const는 선언시 반드시 초기화 해야함. 

	//&& : R-value reference (참조)
	int&& r = 10;

	return 0;
}