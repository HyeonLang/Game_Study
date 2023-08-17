// 과제 : 람다식 조사, for each문

// 1. 람다 기본 모양, 사용법
#define 람다_기본폼
#include<iostream>
#include<string>
using namespace std;

#ifdef 람다_기본폼
/*
* 람다식(Anonymous functions / lambda)

	- 람다 표현식, 람다 함수, 익명 함수 등의 이름으로 불린다.
	- 우리가 아는 일반 함수에서 함수 이름이 없어지고 동작만 있는 함수를 람다 함수, 이름 없는 함수, 람다 표현식이라고 한다.

* 사용법(간략)

	[] ( ) {  } ( )

	[캡처] (매개변수) { 함수 동작 } (호출인자)

	첫 번째 [] : 캡처
	두 번째 () : 매개변수 선언 부분 (생략 가능 - 매개변수 필요 없을 때)
	세 번째 {} : 함수 동작 부분
	네 번째 () : 함수 호출 시 인자 (생략 가능 - 호출 시에만 사용)
*/

//	* 예시


// 일반 함수 정의
void sum1(int a, int b)
{
	cout << "sum1 func : " << a + b << endl;
}

int main(void) {

	//일반 함수 호출
	sum1(10, 20);

	//람다 함수
	[](int a, int b)
	{
		cout << "sum2 lambda : " << a + b << endl;
	}(30, 40);

	return 0;
}

// 출력값
// sum1 func : 30
// sum2 lamda : 70


/*
	* 기본 모양과 사용법

		일반적인 함수는

				반환형 함수이름 (매개변수)
				{
				  // 함수동작
				}

		이런 식으로 되어있지만,



		람다는

				[] (int a, int b) {  cout << " " << endl; } (30, 40);

				---> [] (매개변수) { // 함수 동작 } (호출 시 인자) ;



		이런 식으로 함수의 이름과 반환형이 보이지 않는 희한한 모양인 것을 볼 수 있다.

		정확히 말하면,

		람다식 : [] (매개변수) { // 함수 동작 } --> 여기까지가 람다식

		호출인자 : 맨뒤 ( ) 는 호출인자!



				람다 표현식 생성. 즉, 함수를 만들기만 한 것
				[](int a, intb) {return a + b};

				람다 표현식 사용. 즉 함수를 만들고 호출한 것
				[](int a, intb) {return a + b} (10, 20);


	* 람다 표현 4가지 방법

		일반 함수와 마찬가지로 매개변수가 있는 경우, 매개변수가 없는 경우, 반환이 있는 경우, 반환이 없는 경우 모두 구현이 가능하다.

			1) 매개변수 없는 람다 표현식 : [] { cout << " 인자 없음 " << endl; };

			2) 매개변수 있는 람다 표현식 : [] (int a, int b, int c) { cout << a << b << c << endl; };

			3) 매개변수 없고 반환 있는 람다 : [] { return 200; };

			4) 매개변수 있고 반환 있는 람다 : [] (int a, int b) { return a * b; } ;

				" 이런 식으로 4종류의 람다 함수가 존재한다. "

				주의) 그리고 람다 표현식도 식이기 때문에 끝에는 세미콜론을 붙여주어야 한다.

		위 네가지에서는 함수를 호출하지 않았으므로 중괄호 뒤에 () 이런 식이 없는 것을 확인할 수 있고,

		앞서 보았듯 매개변수가 있는 람다를 호출하기 위해서는 [] (int a, int b) { return a * b; } (10, 20) ;

		이런 식으로 맨 뒤에 매개변수에 맞게 호출부를 작성해주어야 한다.

*/
#endif // 람다_기본폼



// 2. 람다 예제

#define 람다_캡쳐_예제
#include<iostream>
#include<string>
using namespace std;

#ifdef 람다_캡쳐_예제
/*

* 람다 캡쳐[] 사용법

	[]

	- 이름 : 캡쳐

	- 기능 : 람다 외부에 정의되어있는 변수나 상수를 람다 내부에서 사용하기 위해서 사용한다.

			└> 매개변수로 넘겨서 사용하면 되지 않을까?
				: 모든 변수, 상수를 매개변수로 전달할 수도 없고, STL에서 사용할 때는 매개변수 제약이 있을 수 있기 때문에
				이런 상황에서 캡처를 사용하라고 캡쳐를 만들어 둔 것으로 판단됨.

	- 캡쳐 방법 (call by value /  call by reference)

	1) 복사 call by value(=)

		- 복사를 할때는 그냥 변수 이름을 사용하면 된다.
		- 모든 외부 변수에 대해서 복사를 하려면 [=]으로 사용하면 된다.

	2) 참조 call by reference(&)

		- 참조를 할 때는 & 기호를 붙인다.
		- 모든 외부 변수에 대해서 참조를 하려면 [&]라고 사용하면 된다.
*/


int main(void) {
	int result1 = 1;
	int result2 = 2;
	int result3 = 3;
	int result4 = 4;

	// 일부 복사
	cout << "1. 특정변수 복사" << endl;
	[result1, result2](int a, int b) {

		cout << "result1, result2 : " << result1 << ", " << result2 << endl;
		cout << "result1 + a + b : " << result1 + a + b << endl << endl;

		// 복사한 변수에는 대입 불가능
		// result1 = a + b; 
		// result2 = 99999;

	}(10, 20);



	// 일부 참조
	cout << "2. 특정변수 참조" << endl;

	[&result3, &result4](int a, int b) {

		// 참조해서 원본 값 바꾸기 가능
		result3 = 22222;

		cout << "(내부) result3 : " << result3 << endl;
		result4 = a + b;

	}(10, 20);

	cout << "(외부) result3, result4 : " << result3 << ", " << result4 << endl << endl << endl;


	/*
		출력값)

		1. 특정변수 복사
		result1, result2 : 1, 2
		result1 + a + b : 31

		2. 특정변수 참조
		(내부) result3 : 22222
		(외부) result3, result4 : 22222, 30
	*/




	int result5 = 1;
	int result6 = 2;
	int result7 = 3;
	int result8 = 4;


	// 전체 복사
	cout << "3. 전체 복사" << endl;

	[=](int x)
	{
		cout << "result5, 6 : " << result5 << ", " << result6 << endl;
		cout << "result7, 8 : " << result7 << ", " << result8 << endl;
		cout << "매개변수 : " << x << endl;
	}(30);


	cout << endl;


	// 전체 참조
	[&](int y)
	{
		cout << "result5, 6 : " << result5 << ", " << result6 << endl;
		cout << "result7, 8 : " << result7 << ", " << result8 << endl;
		cout << "매개변수 : " << y << endl;

		result5 += y;
		result6 += y;
		result7 += y;
		result8 += y;
	}(99);

	cout << "result5, 6 : " << result5 << ", " << result6 << endl;
	cout << "result7, 8 : " << result7 << ", " << result8 << endl;


	/*
		출력값)

		3. 전체 복사
		result5, 6 : 1, 2
		result7, 8 : 3, 4
		매개변수 : 30

		result5, 6 : 1, 2
		result7, 8 : 3, 4
		매개변수 : 99
		result5, 6 : 100, 101
		result7, 8 : 102, 103

	*/

	return 0;

	/*
		[=, & 변수, & 변수] 이런 식으로 전체 외부 변수를 복사 하되, "일부" 변수만 참조로 가지고 올 수 있고,

		[&, 변수, 변수] 모든 변수를 참조로 가지고 오고, "일부" 변수만 복사로 가지고 올 수 있다.

		단,

		[&, &변수] 이런식으로 모든 변수 참조하고 "일부"도 참조하려 하거나,

		[=, 변수, 변수] 이런 식으로 모든 변수 복사하고 "일부"도 복사하려는 것은 당연하게도 오류가 발생한다.
	*/
}
#endif // 람다_캡쳐_예제




// 3. 람다 유용한 상황
#define 람다_필요이유_예제
#include<iostream>
#include<string>
#include<algorithm>
#include<array>
using namespace std;

#ifdef 람다_필요이유_예제

#define 예제1

#ifndef 예제1

/*
	1) 람다와 auto

	람다 함수를 auto를 이용해서 특정 변수에 넣어둘 수 있다.

			auto func1 = [] (int a, int b) { return a * b };

	이런 식으로 함수를 정의한 부분을 func1 이라는 변수에 집어 넣어서 실제로 사용할때는

	fun1(10, 20); 이런식으로 사용이 가능하다.
*/

int main(void) {

	// 람다 함수1
	auto func1 = [](int a, int b) {return a * b; };

	cout << "func1(2, 10) : " << func1(2, 10) << endl << endl;


	// 람다 함수2
	int num = 20;
	auto func2 = [&num](int a) { num += a; };

	func2(100); // num = num + 100 

	cout << "num : " << num << endl;
	return 0;
}

/*
	출력값)

	func1(2, 10) : 20

	num : 120
*/
#endif // 예제1


//	2) 함수가 필요한데 많이 쓰일 것 같진 않고, 애매 할 때
// ex) sort 함수 - 함수는 필요한데 이번 한번 사용하고 땡처리되는 1회성 함수가 필요할 때 


bool compare(int a, int b) { return a > b; }

int main(void) {
	std::array<int, 10> arr1 = { 5, 4, 2, 1, 100, 32, 2, 4, 6, 9 };
	std::array<int, 10> arr2 = { 5, 4, 2, 1, 100, 32, 2, 4, 6, 9 };
	std::array<int, 10> arr3 = { 5, 4, 2, 1, 100, 32, 2, 4, 6, 9 };

	// 1) sort 함수
	sort(arr1.begin(), arr1.end());
	cout << "std::sort(arr1, arr1 + 10)" << endl;
	for (int val : arr1)
	{
		cout << val << " ";
	}
	cout << endl << endl;


	// 2) sort 함수와 일반 함수 이용
	cout << "std::sort(arr, arr + 10, compare) : " << endl;
	sort(arr2.begin(), arr2.end(), compare);
	for (int val : arr2)
	{
		cout << val << " ";
	}
	cout << endl << endl;


	// 3) sort 함수와 람다 함수 이용
	cout << "std::sort(arr, arr + 10, [](int a, int b) {return a > b; })" << endl;
	sort(arr3.begin(), arr3.end(), [](int a, int b) {return a > b; });
	for (int val : arr3)
	{
		cout << val << " ";
	}

	return 0;
}

/*
	출력값)

	std::sort(arr1, arr1 + 10)
	1 2 2 4 4 5 6 9 32 100

	std::sort(arr, arr + 10, compare) :
	100 32 9 6 5 4 4 2 2 1

	std::sort(arr, arr + 10, [](int a, int b) {return a > b; })
	100 32 9 6 5 4 4 2 2 1
*/

/*
	1) sort함수

		디폴트로 오름차순으로 정렬이 된다.

	2) 기본 함수 이용

		sort() 함수에서 세 번째 인자에 정렬 기준을 정하는 함수를 넣음. 내림차순으로 정렬.

		sort(arr2.begin(), arr2.end(), compare); 여길 보면 세 번째 인자로 함수를 넣은 것을 볼 수 있다.

		기존에는 이런 식으로 sort 함수를 이용해왔는데 람다 함수를 이용하면 좀 더 간편하게 처리할 수 있다.

	3) 람다
		sort(arr3.begin(), arr3.end(), [](int a, int b){return a > b;});

		이런 식으로 sort 함수의 세 번째 인자에 일반 함수 대신, 람다 함수를 집어넣은 것을 볼 수 있다.

		이런 식으로 함수가 필요한 곳에 함수 대신 람다 함수를 사용할 수 있다.
*/
#endif // 람다_필요이유_예제