// 04_inheritance_and_casting.cpp

/*
	Up Casting
	- �ڽ� Ŭ������ �θ� Ŭ���� ���·� �����Ͽ� ����Ű�� ��
	- �ڽ� Ŭ������ �� ũ�� ������ ���������� �� ū �������� ���� �� : �Ͻ��� ����ȯ ����
	- �پ��� �ڽ� Ŭ������ �ϳ��� �θ� Ŭ���� �ڷ�������  ���� �ϰ������� ó�� ����

	Down Casting
	- �θ� Ŭ���� ���·� �����ϴ� �ڽ� Ŭ������ ��ü�� �ٽ� �ڽ� Ŭ������ ���� ���·� ����Ű�� ��
	- �θ� Ŭ�������� �ڽ� Ŭ�������� ��ȯ�� �Ͻ��� ����ȯ�� ���� ����.
*/

#include<iostream>
using namespace std;

class Snack {};

class Chitos : public Snack {};
class ChocoChip : public Snack {};
class Homerunball : public Snack {};

int main() {

	Chitos* chitos1 = new Chitos();

	Snack* chitos = new Chitos(); // �� ĳ���� : �θ��� �����ͷ� ���� �Ҵ� : �ڽ� Ŭ������ ��ӵ� �θ� Ŭ���� �κи� ���� ����
	Snack* chocochip = new ChocoChip();

	//���� �ٸ� �ڽ� Ŭ������ ����� �θ� Ŭ������ ���� ��� ����
	Snack* sneck[2] = { chitos, chocochip };

	//�ٿ� ĳ����
	//Chitos test1 = chitos;  //�Ͻ��� ����ȯ �Ұ�

	//����� ����ȯ���� ó���ؾ� �Ѵ�.
	Chitos* test2 = static_cast<Chitos*>(chitos);

	return 0;
}