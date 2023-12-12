// 10_exception_handling_4.cpp

// std_exception.cpp

#include<iostream>
//1.
// _3에서 예외 처리용 클래스를 만들었지만 이미 std에서 지원함 
#include<exception>
#include<string>
using namespace std;

//2.
// 이미 정의된 클래스를 상속받아 우리가 원하는 형태로 thorw가능
class customException : public std::exception
{
public:
	// c++11 부터 추가
	// 예외시 출력할 문구를 what()을 오버라이딩하여 커스텀할 수 있다.
	const char* what() const noexcept override
	{
		return "Custom exception";
	}

private:

};

int main()
{
	try
	{
		//2.
		throw customException();

		string str;

		// 문자열의 길이는 음수가 없다.
		// -1일경우 언더 플로우 일어나서 최대값이 된다.
		// 문법에 관해 궁금한게 있으면 cppreference.com 참고
		//1.
		str.resize(-1);
	}
	//1.
	//catch (const std::length_error& exception)
	//{
	//	cout << "Length Error" << endl;
	//	cout << exception.what() << endl;
	//}
	//2.
	catch (const std::exception& exception)
	{
		cout << typeid(exception).name() << endl;
		cerr << exception.what() << endl;
	}

	return 0;
}