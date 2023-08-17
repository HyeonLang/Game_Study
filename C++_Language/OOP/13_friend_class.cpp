// 13_friend_class.cpp

/*
	friend 키워드
	- 외부에서 클래스의 private, protected 멤버에 접근할 수 있게 해주는 키워드
	- 정보에 접근하게 해줄 쪽에서 선언한다. -> 단방향
	- friend는 상속이 되지 않는다.
*/

#include<iostream>
using namespace std;


//#define FRIEND_GLOBAL_FUNCTION
//#define FRIEND_MEMBER_CLASS
#define FRIEND_CLASS

#ifdef FRIEND_GLOBAL_FUNCTION
/*
	전역 함수에 공유해주는 경우
*/
class A
{
public:
	const int& GetValue() const { return value; }

	

private:
	int value = 1;

	// 1.
	// friend 키워드를 이용해 전역함수에서 클래스에 숨겨진 멤버 접근 가능
	friend void Test1(const A& a); // 외부(전역) 함수를 friend로 선언

	// 2.
	// friend 선언과 동시에 함수 정의부 구현 가능 -> 1번과 동일하게 외부 함수로 취급
	friend void Test2(const A& a) {// 외부(전역) 함수를 friend로 선언
		cout << a.value << endl; // private 멤버를 공유 받음
	}
};

void Test1(const A& a)
{
	//cout << a.GetValue() << endl;

	cout << a.value << endl; // private 멤버를 공유 받음
}

int main()
{
	A a;

	//결과적으로 같음
	Test1(a);
	Test2(a);

	return 0;
}


#endif 

#ifdef FRIEND_MEMBER_CLASS
/*
	타입이 다른 클래스의 특정 함수에게 공유하려는 경우
*/


/* 
	전방 선언 
	뒤에 작성한 클래스나 구조체를 앞 코드에서 인지시켜야 할 때 사용
*/
class B;	// 클래스의 프로토타입을 미리 적음.

//B b1;		// 정의 안된 클래스의 인스턴스를 만들 수 없음

B* b2;		// 포인터는 가능하다. 
			// 실제 인스턴스를 생성하는 것이 아닌 단순 주소 저장 : 구체적인 정보를 알 필요가 없다.

class B* b3;// 전방선언과 동시에 포인터 생성 가능.

class A {
public:
	void attack(B& b); // 전방 선언 존애 유무만 확인 가능 : 사용은 안됨, 선언부와 정의부를 분리
	/*{
		cout << b.hp;
	}*/

private:

};

class B {
public:
	// class B에서 class A의 attack함수에 멤버함수를 공개.
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
   - 타입이 다른 클래스의 모든 영역에서 접근이 가능하게 경우
*/

class A
{
public:

	// 모든 멤버 함수에서 접근 가능
	void Print_B_value1(class B& b);
	void Print_B_value2(class B& b);

};

class B
{
private:

	// class A에서 B의 모든 멤버에 접근 가능하도록 허용
	// B에서 A로 접근은 안된다. -> *단방향*
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

