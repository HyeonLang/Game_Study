/*
   ���� : Storage<bool>�� Ư��ȭ

   �Ʒ��� Ŭ������ ���� ���ø� ���ڿ� ���� �����͸� 8�� �������ִ� Ŭ�����̴�.

   ���⼭ ������ ����µ� bool���� ���� �� ������ �����ϰ� �ȴ�.
   -> bool���� 1����Ʈ ũ�⸸���ε� 8������ ǥ���� �� ������ �Ʒ���
   ���� ������ ��� 1����Ʈ * 8�� ũ�⸦ ������.

   �Ʒ��� Ŭ������ ���ø� Ư��ȭ�� bool���Ͻ�
   1����Ʈ�� ������ 8���� �Ұ��� ó���� �� �ְ� ������
*/
#include <iostream>
using namespace std;

template<typename T>
class Storage8
{
public:
    void Set(int index, const T& value)
    {
        arr[index] = value;
    }

    const T& Get(int index)
    {
        return arr[index];
    }

private:
    T arr[8];
};

template<>
class Storage8<bool>
{
public:
    void Set(int index, const bool& value)
    {
        if (value == 1) {
            bool_arr = (1 << index) | bool_arr;
        }
        if (value == 0) {
            bool_arr = (~(1 << index)) & bool_arr;
        }
    }

    const bool& Get(int index)
    {
        return (bool_arr << index) & 1;
    }

private:
    char bool_arr;
};

int main() {
    Storage8<int> i;
    Storage8<bool> b;

    i.Set(5, 5);
    cout << i.Get(5) << endl;
    b.Set(0, 1);
    b.Set(0, 0);
    cout << b.Get(0) << endl;


/*
   ���� : ��Ʈ �����ڸ� ����Ͽ� �Ʒ��� ������ �ذ�

   2������, bool��� ����, ��Ʈ����


   1.
   int a = 123;

      a = 0;

      a = a ? a -> ?�� ���� �����ڰ� ���� �� �ڵ庸�� ������ �ɱ�?

   2. swap:
   int a = 123;
   int b = 456;

   a = a ? b
   b = a ? b
   a = a ? b

   temp�� ������� �ʰ� �ٲٴ¹� ã��

   3.
      ¦��/Ȧ�� �Ǻ� -> %������� �ʰ�

   4.
      ����/��� �Ǻ� -> ���迬���� ��� x


   5.
      2�� �¼����� �ƴ��� �Ǻ� -> �ݺ��� ������� �ʰ�
      ���� �ι��� �ϸ� �� �� ����

   6.
      �빮��/�ҹ��� ��ȯ -> +, - �Ⱦ���
      �ƽ�Ű �ڵ��� �빮�ڴ� ������° ��Ʈ�� ��� 0�̰�
      �ҹ��ڴ� ��� 1 �̴�.
*/
    // 1.
    int a = 123;

    a = 0;

    a = a ^ a;

    cout << a << endl;

    // 2. swap:
    int a2 = 123;
    int b2 = 456;

    a2 = a2 ^ b2;
    b2 = a2 ^ b2;
    a2 = a2 ^ b2;

    cout << a2 << " " << b2 << endl;

    // 3. ¦�� / Ȧ�� �Ǻ� -> % ������� �ʰ�
    int odd = 11;
    int even = 12;
    cout << (odd & 1);
    cout << endl;
    cout << (even & 1);
    cout << endl << endl;

    // 4. ���� / ��� �Ǻ�->���迬���� ��� x
    int minus = -121;
    int plus = 2211;
    cout << (minus & 0x80000000);
    cout << endl;
    cout << (plus & 0x80000000);
    cout << endl << endl;
    // 5.2�� �¼����� �ƴ��� �Ǻ�->�ݺ��� ������� �ʰ�, ���� �ι��� �ϸ� �� �� ����
    int bit = 64;
    int no_bit = 20;
    cout << ((bit - 1) & bit) << endl;
    cout << ((no_bit - 1) & no_bit) << endl;


    // 6. �빮�� / �ҹ��� ��ȯ -> + , -�Ⱦ���, �ƽ�Ű �ڵ��� �빮�ڴ� ������° ��Ʈ�� ��� 0�̰�, �ҹ��ڴ� ��� 1 �̴�.
    char capital = 'A';
    char small = 'a';
    cout << char(capital ^ 32) << endl;
    cout << char(small ^ 32) << endl;

    return 0;
}


/*
   ���� : ��Ʈ �����ڸ� ����Ͽ� �Ʒ��� ������ �ذ�

   2������, bool��� ����, ��Ʈ����


   1.
   int a = 123;

      a = 0;

      a = a ? a -> ?�� ���� �����ڰ� ���� �� �ڵ庸�� ������ �ɱ�?

   2. swap:
   int a = 123;
   int b = 456;

   a = a ? b
   b = a ? b
   a = a ? b

   temp�� ������� �ʰ� �ٲٴ¹� ã��

   3.
      ¦��/Ȧ�� �Ǻ� -> %������� �ʰ�

   4.
      ����/��� �Ǻ� -> ���迬���� ��� x


   5.
      2�� �¼����� �ƴ��� �Ǻ� -> �ݺ��� ������� �ʰ�
      ���� �ι��� �ϸ� �� �� ����

   6.
      �빮��/�ҹ��� ��ȯ -> +, - �Ⱦ���
      �ƽ�Ű �ڵ��� �빮�ڴ� ������° ��Ʈ�� ��� 0�̰�
      �ҹ��ڴ� ��� 1 �̴�.
*/
#include <iostream>
using namespace std;

int main() {
    // 1.
    int a = 123;

    a = 0;

    a = a ^ a;

    cout << a << endl;

    // 2. swap:
    int a2 = 123;
    int b2 = 456;

    a2 = a2 ^ b2;
    b2 = a2 ^ b2;
    a2 = a2 ^ b2;

    cout << a2 << " " << b2 << endl;

    // 3. ¦�� / Ȧ�� �Ǻ� -> % ������� �ʰ�
    int odd = 11;
    int even = 12;
    cout << (odd & 1);
    cout << endl;
    cout << (even & 1);
    cout << endl << endl;

    // 4. ���� / ��� �Ǻ�->���迬���� ��� x
    int minus = -121;
    int plus = 2211;
    cout << (minus & 0x80000000);
    cout << endl;
    cout << (plus & 0x80000000);
    cout << endl << endl;
    // 5.2�� �¼����� �ƴ��� �Ǻ�->�ݺ��� ������� �ʰ�, ���� �ι��� �ϸ� �� �� ����
    int bit = 64;
    int no_bit = 20;
    cout << ((bit - 1) & bit) << endl;
    cout << ((no_bit - 1) & no_bit) << endl;


    // 6. �빮�� / �ҹ��� ��ȯ -> + , -�Ⱦ���, �ƽ�Ű �ڵ��� �빮�ڴ� ������° ��Ʈ�� ��� 0�̰�, �ҹ��ڴ� ��� 1 �̴�.
    char capital = 'A';
    char small = 'a';
    cout << char(capital ^ 32) << endl;
    cout << char(small ^ 32) << endl;

    return 0;
}