// 22_variable_argument.cpp

/*
	variable_argument : 가변 인자
		- 함수에 들어가는 인가의 개수가 가변적인것.
		- ex) printf에 있는 ... 을 말한다.
*/

#include <iostream>
#include <cstdarg>
#include <string>

//#define 가변_인자_함수_사용하기
//#define 다양한_자료형으로_가변_인자_함수_사용하기
#define 더쉽게_다양한_자료형으로_가변_인자_함수_사용하기



/*
	================================================
	[가변인자 함수 사용하기]
	================================================
*/
#ifdef 가변_인자_함수_사용하기

//arg_count : 가변인자의 개수를 받는다.
//...		: 가변인자를 받을 것이라는 의미
void print_number(int arg_count, ...) { //... : 가변 인자

	va_list arg_list;	//가변인자를 가리키는 포인터

	 /*
		va_start(가변인자 포인터, 마지막 고정인수)
			- 가변 인자의 포인터 설정 매크로
			- 마지막 고정 인수를 기준으로 위치를 찾아준다.

		---------------------------------------------------
		|  arg_count  | arg_list1 | arg_list2 | arg_list3 |
		---------------------------------------------------
					  ↑
				  arg_list
	   마지막 고정 인수를 기준으로 가변 인자의 시작 위치를 찾아준다.
	*/
	va_start(arg_list, arg_count); //arg_count 다음 시작위치를 arg_list에 넣어준다.

	for (int i = 0; i < arg_count; i++) {

		// va_arg(arg_list, int) : arg_list에서 4바이트(int크기)만큼 역참조하여 데이터를 가져온 뒤 
	    //                         arg_list를 4바이트(int크기)만큼 이동시킨다. -> 다음 가변 인자의 시작 위치로 이동시킴

		int num = va_arg(arg_list, int);	// int형으로 arg_list의 가변인자들을 return. 
											//다음 데이터 위치로 이동도 한다.
		printf("%d", num);
	}

	va_end(arg_list); //해당 가변인자 포인터를 nullptr로 초기화

	printf("\n");
}

int main() {
	print_number(1, 1);
	print_number(2, 1, 2);
	print_number(3, 1, 2, 3);
	print_number(4, 1, 2, 3, 4);

	return 0;
}

#endif



/*
	================================================
	[다양한 자료형으로 가변인자 함수 사용하기]
	================================================
*/
#ifdef 다양한_자료형으로_가변_인자_함수_사용하기

void print_value(const char* arg_format, ...) {
	va_list arg_list;
	int i = 0;

	va_start(arg_list, arg_format);

	while (arg_format[i] != '\0') {

		switch (arg_format[i++]) {
		case 'i': printf("%d ", va_arg(arg_list, int)); break;
		case 'd': printf("%lf ", va_arg(arg_list, double)); break;
		case 'c': printf("%c ", va_arg(arg_list, char)); break;
		case 's': printf("%s ", va_arg(arg_list, char*)); break;
		}
		
	}

	va_end(arg_list);

	printf("\n");
}

int main() {
	print_value("i"   , 10);
	print_value("di"  , 3.14, 10);
	print_value("cdi" , 'A', 3.14, 10);
	print_value("scdi", "arg_list", 'A', 3.14, 10);

	return 0;
}

#endif



/*
	================================================
	[더 쉽게 다양한 자료형으로 가변인자 함수 사용하기]
	================================================
*/
#ifdef 

void print_string(const std::string arg_format, ...)
{
	va_list arg_list;
	int i = 0;

	va_start(arg_list, arg_format);
	{
		// _vscprintf -> 형식과 인자가 합쳐서 만들어질 총 문자열의 길이를 알려준다.
		// -> '\0'의 길이는 따로 넣어주어야 한다.
		int size = _vscprintf(arg_format.c_str(), arg_list) + sizeof('\0');

		// 만들어질 크기만큼 동적할당을 받는다.
		char* string = new char[size];

		// vsprintf_s() : string에 size 만큼 arg_format(형식)과 arg_list(인자)를 합쳐 문자열을 만들어 준다.
		vsprintf_s(string, size, arg_format.c_str(), arg_list);

		// 완성된 문자열을 출력한다.
		printf("%s", string);

		// 사용 후 해제해준다.
		delete[] string;

	}
	va_end(arg_list);

	printf("\n");
}

int main()
{
	print_string("문자열 출력 가능 : %s, 숫자도 가능 : %d, Escape sequence도 가능 : \nTest", "Hello World!", 123);


	//로그 찍을 때 사용할 만한 매크로
	__FUNCTION__;
	__LINE__;
	__FILE__;

	return 0;
}

#endif