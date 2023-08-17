// 13_friend_class.cpp

/*
	friend Ű����
	- �ܺο��� Ŭ������ private, protected ����� ������ �� �ְ� ���ִ� Ű����
	- ������ �����ϰ� ���� �ʿ��� �����Ѵ�. -> �ܹ���
	- friend�� ����� ���� �ʴ´�.
*/

#include<iostream>
using namespace std;


//#define FRIEND_GLOBAL_FUNCTION
//#define FRIEND_MEMBER_CLASS
#define FRIEND_CLASS

#ifdef FRIEND_GLOBAL_FUNCTION
/*
	���� �Լ��� �������ִ� ���
*/
class A
{
public:
	const int& GetValue() const { return value; }

	

private:
	int value = 1;

	// 1.
	// friend Ű���带 �̿��� �����Լ����� Ŭ������ ������ ��� ���� ����
	friend void Test1(const A& a); // �ܺ�(����) �Լ��� friend�� ����

	// 2.
	// friend ����� ���ÿ� �Լ� ���Ǻ� ���� ���� -> 1���� �����ϰ� �ܺ� �Լ��� ���
	friend void Test2(const A& a) {// �ܺ�(����) �Լ��� friend�� ����
		cout << a.value << endl; // private ����� ���� ����
	}
};

void Test1(const A& a)
{
	//cout << a.GetValue() << endl;

	cout << a.value << endl; // private ����� ���� ����
}

int main()
{
	A a;

	//��������� ����
	Test1(a);
	Test2(a);

	return 0;
}


#endif 

#ifdef FRIEND_MEMBER_CLASS
/*
	Ÿ���� �ٸ� Ŭ������ Ư�� �Լ����� �����Ϸ��� ���
*/


/* 
	���� ���� 
	�ڿ� �ۼ��� Ŭ������ ����ü�� �� �ڵ忡�� �������Ѿ� �� �� ���
*/
class B;	// Ŭ������ ������Ÿ���� �̸� ����.

//B b1;		// ���� �ȵ� Ŭ������ �ν��Ͻ��� ���� �� ����

B* b2;		// �����ʹ� �����ϴ�. 
			// ���� �ν��Ͻ��� �����ϴ� ���� �ƴ� �ܼ� �ּ� ���� : ��ü���� ������ �� �ʿ䰡 ����.

class B* b3;// ���漱��� ���ÿ� ������ ���� ����.

class A {
public:
	void attack(B& b); // ���� ���� ���� ������ Ȯ�� ���� : ����� �ȵ�, ����ο� ���Ǻθ� �и�
	/*{
		cout << b.hp;
	}*/

private:

};

class B {
public:
	// class B���� class A�� attack�Լ��� ����Լ��� ����.
	friend void A::attack(B& b); 
private:
	int hp = 100;
};

int main() {
	A a;
	B b;

	a.attack(b); //100
	return 0;
}

void A::attack(B& b) {
	cout << b.hp;
}

#endif

#ifdef FRIEND_CLASS
/*
   friend class
   - Ÿ���� �ٸ� Ŭ������ ��� �������� ������ �����ϰ� ���
*/

class A
{
public:

	// ��� ��� �Լ����� ���� ����
	void Print_B_value1(class B& b);
	void Print_B_value2(class B& b);

};

class B
{
private:

	// class A���� B�� ��� ����� ���� �����ϵ��� ���
	// B���� A�� ������ �ȵȴ�. -> *�ܹ���*
	friend class A;

private:
	int value1 = 10;
	int value2 = 20;
};

int main()
{
	A a;
	B b;

	a.Print_B_value1(b);
	a.Print_B_value2(b);

	return 0;
}

void A::Print_B_value1(class B& b)
{
	cout << "value1 : " << b.value1 << endl;
}

void A::Print_B_value2(class B& b)
{
	cout << "value2 : " << b.value2 << endl;
}

#endif // FRIEND_CLASS

