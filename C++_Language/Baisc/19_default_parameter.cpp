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
	매번 같은 매개변수 값을 넣기 번거로울 때 default_parameter 사용.
	-> 보통 true로 세팅될 때 의 경우 => bool is_active = true
*/
Player CreatePlayer(int hp, bool is_active = true) //기본 매개변수
{
	Player p{ hp, is_active };
	return p;
}

/*
	주의점1 : 기본 매개변수는 무조건 마지막부터 존재해야 한다.
*/
//Player CreatePlayer(bool is_active = true, int hp) 
//{
//	Player p{ hp, is_active };
//	return p;
//}

Player CreatePlayer2(int hp = 150, int atk = 50, bool is_active = true) //기본 매개변수
{
	Player p{ hp, is_active, atk };
	return p;
}

Player CreatePlayer2(int hp = 150, int atk = 50) //기본 매개변수
{
	Player p{ hp, 1, atk };
	return p;
}

Player CreatePlayer2(float hp, float atk, bool is_active = true) //함수 오버로딩
{
	Player p{ hp, is_active, atk };
	return p;
}

int main() {
	Player p1 = CreatePlayer(10);
	Player p2 = CreatePlayer(10);
	Player p3 = CreatePlayer(10);
	Player p4 = CreatePlayer(10, false);

	//주의점2 : 뒤에있는 값만 기본값이 아닌 다른값으로 변경하려면 앞에 있는 기본값들도 넣어주어야 한다.
	CreatePlayer2(150, 50, false);

	//CreatePlayer2(200.0, 300.0); //모호성 에러
	//CreatePlayer2(10); //모호성 에러
	/*
	    주의점3 : 모호성 문제
		함수 하나에 대하여 보통 함수 오버로딩과 default parameter는 양자 택일 하여 사용한다. 
		모호성 문제를 방지하기 위함이다.
	*/

	return 0;
}