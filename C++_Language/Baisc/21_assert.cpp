// 21_assert.cpp

#include <iostream>
#include <cassert>

int main() {
	int x = 0;
	//x 입력, 변화 코드
	std::cout << x << std::endl;

	/*
		assert
			- 조건식이 true 이면 계속 진행, 아니면 에러
			- 특정 조건의 성공 유무 확인 가능
			- debug 모드에서만 수행, release 모드에서는 무시
			- 일반 assert는 런타임시 확인 : 실행 도중 체크
	*/
	//assert(x != 0); 
	
	//문자열 상수는 문자열의 첫 주소 == true : 문자열로 코드 설명을 할 수 있음.
	assert(x != 0 && "x is 0");  

	//정적 assert : 컴파일 타임때 확인하는 assert
	//static_assert(false); 
	
	//컴파일시 확인가능한 상수값만 가능하다.
	bool is_b = true;
	const bool is_cb = is_b; //const는 컴파일시, 런타임시 모두 값 확정이 가능하다.
	constexpr bool is_db = true; //constexpr : 컴파일시 선언이 되어야 하는 변수
	//static_assert(is_b, "is_b" ); //error
	//static_assert(is_cb,"is_cb" ); //error
	
	constexpr int z = 30;
	constexpr int w = 20;
	static_assert(z > w, "w is bigger than z"); //z <= w일 경우 error 

	return 0;
}

//static_assert 사용 예시
template<typename T>
void Test(T val)
{
	static_assert(typeid(T) != typeid(int), "T is int"); //T 가 int시 에러 
}