// 05_delegeting_constructor.cpp

/*
	delegeting constructor - 위임 생성자
	- 같은 클래스에서 생성자가 다른 생성자를 호출하는 것
*/

#include<iostream>
#include<string>
using namespace std;

class Student1
{
public:
	Student1(const int& id, const std::string& name)
		: id(id), name(name)
	{
		//...
		//...
		//...
		//...
		//...
	}

	//Student1(const std::string& name)
	//	: Student1(0, name) // Student1(id, name) 형태의 생성자에게 생성을 위임
	//{
	//	// Student1(0, name)의 작업이 끝난후 처리되는 코드
	//}

	// 이와같이 다양한 방식으로 초기화 할 수 있지만 초기화 방식은 하나만 존재하는게 유지보수하기에 용이

private:
	int id;
	std::string name;
};


class Student2
{
public:
	Student2(const int& id, const std::string& name)
	{
		Initialize(id, name);
	}

	Student2(const std::string& name)
	{
		Initialize(0, name);
	}

	void Initialize(const int& id, const string& name)
	{
		//TODO:
	}

private:
	int id;
	std::string name;
};

int main()
{

	return 0;
}