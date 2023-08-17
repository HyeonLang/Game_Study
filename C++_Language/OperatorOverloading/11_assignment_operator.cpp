// 11_assignment_operator.cpp

// deep copy vs shallow copy
// 깊은 복사 vs 얕은 복사 : 깊은 복사가 필요할 때 대입연산자 재정의 필요
// 얕은 복사 : 주소값만을 공유함.
// 깊은 복사 : 메모리 자체를 생성하여 데이터 자체를 복사함.

#include <iostream>
#include <cassert>
using namespace std;

class MyString
{
public:
    MyString(const char* const src = "")
    {
        assert(src);

        length = strlen(src) + 1;   // 공백문자를 제외하고 개수를 세주어 +1 해준다. (공백문자 포함)
        data = new char[length];    // 소멸자에서 동적 할당한 data 소멸 

        for (int i = 0; i < length; i++)
            data[i] = src[i];

        data[length - 1] = '\0'; //마지막 위치 null문자
    }
       // 복사 생성자 : 얕은 복사, 깊은 복사 
    MyString(const MyString& other) { // const로 인해 이동 생성자에서도 사용가능
        cout << "copy constructor" << endl;

        /*
            shallow copy
            가지고 있는 값을 그대로 전달하는것
            문제 : 포인터가 복사 될 경우 주소값을 공유하게 됨. 
            이는 해당포인터를 클래스 소멸자에서 해제하게 된다면 
            같은 주소를 2번 이상 해제하는 문제 발생
        */
        //length = other.length;  //사본복사
        //data = other.data;      //원본 공유 복사 (포인터)


        /*
            deep copy
            필요한 경우 새로운 메모리 공간을 할당하여 복사
            -> 동적할당 필요 : 얕은 복사보다 느림
            상황에 맞게 사용
        */
        length = other.length;
        if (other.data != nullptr) {
            data = new char[length];
            for (int i = 0; i < length; i++) {
                data[i] = other.data[i];
            }
        }
        else {
            data = nullptr;
        }
    }

    //이동 생성자 : 얕은 복사
    //원본 자체를 가져오는 개념 -> 더이상 외부에 원본 존재 X, const를 붙이지 않음 : 이동 개념
    MyString(MyString&& other) { 
        cout << "move constructor" << endl;

        data = std::move(other.data);
        length = std::move(other.length);

        /*
            받은 매개변수 other는 더이상 외부에 존재하지 않는다고 가정.
            other의 데이터를 초기화하여 접근하지 못하도록 막는것이 안전.
        */
        other.data = nullptr; //외부 원본을 삭제
        other.length = 0;
    }

    ~MyString()
    {
        if (data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }

    //복사 대입 연산자 : 깊은 복사
    MyString& operator = (const MyString& other) {
        cout << "copy assignment operator" << endl;

        // 안전한 코드를 만들기 위해 주의해야 할 점.
        
        // 1. prevent self-assignment, 자신을 할당하는 것 방지
        if (this == &other) return *this;

        // 2. data에 이미 할당되어있는 메모리가 있다면 해제
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }

        //깊은 복사
        length = other.length;
        if (other.data != nullptr) {
            data = new char[length];
            for (int i = 0; i < length; i++) {
                data[i] = other.data[i];
            }
        }
        else {
            data = nullptr;
        }
    }

    //이동 대입 연산자 : 얕은 복사
    MyString& operator = (MyString&& other) {
        cout << "move assignment operator" << endl;

        // 안전한 코드를 만들기 위해 주의해야 할 점.

        // 1. prevent self-assignment, 자신을 할당하는 것 방지
        if (this == &other) return *this;

        // 2. data에 이미 할당되어있는 메모리가 있다면 해제
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }

        //얕은 복사
        data = std::move(other.data);
        length = std::move(other.length);

        /*
           받은 매개변수 other는 더이상 외부에 존재하지 않는다고 가정.
           other의 데이터를 초기화하여 접근하지 못하도록 막는것이 안전.
       */
        other.data = nullptr; //외부 원본을 삭제
        other.length = 0;
    }

public:
    char* data = nullptr;
    int length = 0;
};

int main() {
    MyString str("Hello");

    //copy : 원본을 복사하여 사본을 만듦
    {
        MyString copy(str); // str이 copy되었으므로 str의 data를 공유 : (복사 생성자 호출)
                            //copy 소멸자에서 data를 삭제해 버리면 str의 data도 사라짐
                            // 허상포인터 문제

        copy = str;
    }

    //move 생성자 : 원본에서 이동시켜 새로 만듦
    {
        MyString move(std::move(str));

        move = std::move(str);
    }

	return  0;
}