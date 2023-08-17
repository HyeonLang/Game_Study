// 15_pure_virtual_function_and_abstract_class.cpp
// ���� ���� �Լ��� �߻� Ŭ����

/*
	pure vitual function - ���� ���� �Լ�
		- �Ļ� Ŭ�������� �ݵ�� ������ �ؾ��ϴ� �Լ�
		- ������ �����ϴ� ���Ǻΰ� ����.
		- ���� ���� ���� �Լ��̹Ƿ� ���� ���� �Լ��� ������ Ŭ������
		�ν��Ͻ�ȭ�� �ȵǰ� ������θ� ��� ����. -> ���� ������ �ڷ��� ������ ����

	abstract class - �߻� Ŭ����
		- �ϳ� �̻��� ���� ���� �Լ��� ������ Ŭ����

	interface - �������̽�
		- ���� ���� �Լ��θ� �̷���� Ŭ����
		- ���� �ٸ� ��ü���� ���� �ڷ������� ���� �� ���. : ���� �ٸ� Ŭ������ ���� ��� �� ��.
		- ���� ��� ����.

	// ���� : �������̽��� ����ϴ� ���� ����
	// ���� : SOLID ����
*/

#define ����_����_�Լ�_�߻�_Ŭ����
#define �������̽�

#include <iostream>
#include <string>
using namespace std;

#ifdef ����_����_�Լ�_�߻�_Ŭ����


class Animal { // �߻� Ŭ���� : ���� ���� �Լ��� �Ѱ� �̻� ������.
public:
	Animal(const string& name) : name(name) {}

	const string& GetName() const { return name; }

	// ���� ���� �Լ� : ������ �Ļ� Ŭ�������� ����
	virtual void Speak() const = 0; 

private:
	string name;
};

class Cat : public Animal
{
public:
	Cat(string name) : Animal(name) {}
	void Speak() const { cout << "Meow" << endl; }
};

class Dog : public Animal
{
public:
	Dog(string name) : Animal(name) {}
	void Speak() const { cout << "Woof" << endl;  }
};

class Fox : public Animal
{
public:
	Fox(string name) : Animal(name) {}
};

int main()
{
	Cat cat("DiDi");
	Dog dog("Corgi");

	cat.Speak();
	dog.Speak();

	// ���� ���� �Լ��� ������ Ŭ���� �̹Ƿ� ��üȭ �Ұ���
    //Animal ani("lala"); // �Ұ�!!
    //ani.Speak();

	// ��ӹ��� ���� ���� �Լ��� ������ ���� �ʾ� ����
    //Fox fox("RURU"); // ������ ���� ����!!
    //fox.Speak();

	return 0;
}
#endif // ����_����_�Լ�_�߻�_Ŭ����


#ifdef �������̽�

class IErrorLog
{
public:
	virtual ~IErrorLog() = default; // ���� default �Ҹ��� 
	virtual bool ReportError(const char* const error) = 0;
};

class FileErrorLog : public IErrorLog
{
public:
	virtual bool ReportError(const char* error) override
	{
		cout << "Writting error to a file" << endl;
		return true;
	}
};

class ConsoleErrorLog : public IErrorLog
{
public:
	virtual bool ReportError(const char* error) override
	{
		cout << "Printing error to a console" << endl;
		return true;
	}
};

void DoSomething(IErrorLog& log) // �ڷ��� �ΰ��� �������̽� �ϳ��� ���� �Ű������� ����.
{
	log.ReportError("Error");
}

int main()
{
	FileErrorLog file_log;
	ConsoleErrorLog console_log;

	DoSomething(file_log);
	DoSomething(console_log);
}

#endif // �������̽�

