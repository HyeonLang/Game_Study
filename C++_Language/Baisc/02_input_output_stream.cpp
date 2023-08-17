// 02_input_output_stream.cpp

#include<iostream>
//#include<iomanip>

/*
	stream ( >> , <<)
		- 데이터의 입력과 출력의 흐름을 표시한 것
*/

int main()
{
	/*
		cout, endl

		<< : output operator(stream)
	*/

	int x = 1028;
	double pi = 3.141592;

	std::cout << "x is " << x << " pi is " << pi << std::endl << std::endl;

	/*
		cin

		>> : input operator(stream)
	*/
	//int z;
	//std::cin >> z;
	//std::cout << "Your input is " << z << std::endl << std::endl;

	/*
		조정자(mainpulator)
		- 입출력 형식을 지정해줄 수 있다
		- 변경하기 전까지 설정한 옵션이 계속 유지된다.
	*/

	int num = 100;

	// 진수 출력 형식 조정자
	std::cout << std::oct << num << std::endl;
	std::cout << std::dec << num << std::endl;
	std::cout << std::hex << num << std::endl << std::endl;

	// showbase : 어떤 진수 형태로 출력되는지 표시
	// showpos	: 십진수 정수의 부호 표시
	// noshowbase, noshowpos로 해제 가능

	std::cout << std::showbase << std::showpos;
	std::cout << std::oct << num << std::endl;
	std::cout << std::dec << num << std::endl;
	std::cout << std::hex << num << std::endl << std::endl;
	std::cout << std::noshowbase << std::noshowpos;

	bool is_true = true;
	bool is_false = false;

	//bool형의 출력 형식을 바꿀 수 있다.
	std::cout << std::boolalpha; // true, false형식으로 출력
	std::cout << is_true << std::endl;
	std::cout << is_false << std::endl << std::endl;

	std::cout << std::noboolalpha; // boolalpha 취소
	std::cout << is_true << std::endl;
	std::cout << is_false << std::endl << std::endl;

	return 0;
}