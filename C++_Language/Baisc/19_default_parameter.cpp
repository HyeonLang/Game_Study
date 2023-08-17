// 19_default_parameter.cpp

#include <iostream>

struct Player
{
	int hp;
	bool is_active;
	int atk;
};


//Player CreatePlayer(int hp, bool is_active) 
//{
//	Player p{ hp, is_active };
//	return p;
//}

/*
	�Ź� ���� �Ű����� ���� �ֱ� ���ŷο� �� default_parameter ���.
	-> ���� true�� ���õ� �� �� ��� => bool is_active = true
*/
Player CreatePlayer(int hp, bool is_active = true) //�⺻ �Ű�����
{
	Player p{ hp, is_active };
	return p;
}

/*
	������1 : �⺻ �Ű������� ������ ���������� �����ؾ� �Ѵ�.
*/
//Player CreatePlayer(bool is_active = true, int hp) 
//{
//	Player p{ hp, is_active };
//	return p;
//}

Player CreatePlayer2(int hp = 150, int atk = 50, bool is_active = true) //�⺻ �Ű�����
{
	Player p{ hp, is_active, atk };
	return p;
}

Player CreatePlayer2(int hp = 150, int atk = 50) //�⺻ �Ű�����
{
	Player p{ hp, 1, atk };
	return p;
}

Player CreatePlayer2(float hp, float atk, bool is_active = true) //�Լ� �����ε�
{
	Player p{ hp, is_active, atk };
	return p;
}

int main() {
	Player p1 = CreatePlayer(10);
	Player p2 = CreatePlayer(10);
	Player p3 = CreatePlayer(10);
	Player p4 = CreatePlayer(10, false);

	//������2 : �ڿ��ִ� ���� �⺻���� �ƴ� �ٸ������� �����Ϸ��� �տ� �ִ� �⺻���鵵 �־��־�� �Ѵ�.
	CreatePlayer2(150, 50, false);

	//CreatePlayer2(200.0, 300.0); //��ȣ�� ����
	//CreatePlayer2(10); //��ȣ�� ����
	/*
	    ������3 : ��ȣ�� ����
		�Լ� �ϳ��� ���Ͽ� ���� �Լ� �����ε��� default parameter�� ���� ���� �Ͽ� ����Ѵ�. 
		��ȣ�� ������ �����ϱ� �����̴�.
	*/

	return 0;
}