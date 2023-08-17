// 11_assignment_operator.cpp

// deep copy vs shallow copy
// ���� ���� vs ���� ���� : ���� ���簡 �ʿ��� �� ���Կ����� ������ �ʿ�
// ���� ���� : �ּҰ����� ������.
// ���� ���� : �޸� ��ü�� �����Ͽ� ������ ��ü�� ������.

#include <iostream>
#include <cassert>
using namespace std;

class MyString
{
public:
    MyString(const char* const src = "")
    {
        assert(src);

        length = strlen(src) + 1;   // ���鹮�ڸ� �����ϰ� ������ ���־� +1 ���ش�. (���鹮�� ����)
        data = new char[length];    // �Ҹ��ڿ��� ���� �Ҵ��� data �Ҹ� 

        for (int i = 0; i < length; i++)
            data[i] = src[i];

        data[length - 1] = '\0'; //������ ��ġ null����
    }
       // ���� ������ : ���� ����, ���� ���� 
    MyString(const MyString& other) { // const�� ���� �̵� �����ڿ����� ��밡��
        cout << "copy constructor" << endl;

        /*
            shallow copy
            ������ �ִ� ���� �״�� �����ϴ°�
            ���� : �����Ͱ� ���� �� ��� �ּҰ��� �����ϰ� ��. 
            �̴� �ش������͸� Ŭ���� �Ҹ��ڿ��� �����ϰ� �ȴٸ� 
            ���� �ּҸ� 2�� �̻� �����ϴ� ���� �߻�
        */
        //length = other.length;  //�纻����
        //data = other.data;      //���� ���� ���� (������)


        /*
            deep copy
            �ʿ��� ��� ���ο� �޸� ������ �Ҵ��Ͽ� ����
            -> �����Ҵ� �ʿ� : ���� ���纸�� ����
            ��Ȳ�� �°� ���
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

    //�̵� ������ : ���� ����
    //���� ��ü�� �������� ���� -> ���̻� �ܺο� ���� ���� X, const�� ������ ���� : �̵� ����
    MyString(MyString&& other) { 
        cout << "move constructor" << endl;

        data = std::move(other.data);
        length = std::move(other.length);

        /*
            ���� �Ű����� other�� ���̻� �ܺο� �������� �ʴ´ٰ� ����.
            other�� �����͸� �ʱ�ȭ�Ͽ� �������� ���ϵ��� ���°��� ����.
        */
        other.data = nullptr; //�ܺ� ������ ����
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

    //���� ���� ������ : ���� ����
    MyString& operator = (const MyString& other) {
        cout << "copy assignment operator" << endl;

        // ������ �ڵ带 ����� ���� �����ؾ� �� ��.
        
        // 1. prevent self-assignment, �ڽ��� �Ҵ��ϴ� �� ����
        if (this == &other) return *this;

        // 2. data�� �̹� �Ҵ�Ǿ��ִ� �޸𸮰� �ִٸ� ����
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }

        //���� ����
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

    //�̵� ���� ������ : ���� ����
    MyString& operator = (MyString&& other) {
        cout << "move assignment operator" << endl;

        // ������ �ڵ带 ����� ���� �����ؾ� �� ��.

        // 1. prevent self-assignment, �ڽ��� �Ҵ��ϴ� �� ����
        if (this == &other) return *this;

        // 2. data�� �̹� �Ҵ�Ǿ��ִ� �޸𸮰� �ִٸ� ����
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }

        //���� ����
        data = std::move(other.data);
        length = std::move(other.length);

        /*
           ���� �Ű����� other�� ���̻� �ܺο� �������� �ʴ´ٰ� ����.
           other�� �����͸� �ʱ�ȭ�Ͽ� �������� ���ϵ��� ���°��� ����.
       */
        other.data = nullptr; //�ܺ� ������ ����
        other.length = 0;
    }

public:
    char* data = nullptr;
    int length = 0;
};

int main() {
    MyString str("Hello");

    //copy : ������ �����Ͽ� �纻�� ����
    {
        MyString copy(str); // str�� copy�Ǿ����Ƿ� str�� data�� ���� : (���� ������ ȣ��)
                            //copy �Ҹ��ڿ��� data�� ������ ������ str�� data�� �����
                            // ��������� ����

        copy = str;
    }

    //move ������ : �������� �̵����� ���� ����
    {
        MyString move(std::move(str));

        move = std::move(str);
    }

	return  0;
}