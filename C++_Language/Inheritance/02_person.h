#pragma once

// 02_person.h

#include<string>

class EX_Student
{
	EX_Student() = default;
	EX_Student(const std::string& name)
		: name(name)
	{}

	auto Getname() const { return name; }
	void SetName(const std::string& name) { this->name = name; }

	void Study() {}

protected:
	std::string name;
};

class EX_Teacher
{
	EX_Teacher() = default;
	EX_Teacher(const std::string& name)
		: name(name)
	{}

	auto Getname() const { return name; }
	void SetName(const std::string& name) { this->name = name; }

	void Teach() {}

protected:
	std::string name;
};


// 겹치는 멤버를 기반 클래스에 작성
class Person
{
public:
	Person() = default;
	Person(const std::string& name)
		: name(name)
	{}

	auto Getname() const { return name; }
	void SetName(const std::string& name) { this->name = name; }

protected:
	std::string name;
};