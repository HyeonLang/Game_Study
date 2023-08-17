// 15_nested_type.cpp

#include <iostream>
using namespace std;


class Character {


public:
	//중첩 타입
	enum class Movement {
		Min = 0,
		Idle = Min,
		Walk,
		Run,
		Max = Run,
		Count // 마지막 원소를 count로 하여 인덱스 갯수를 파악 가능 : Count의 idx = 3;
	};

public:
	Character(const string& str) : name(str) {} //멤버 초기화 리스트

	void SetCharacterMovement(Movement new_move) {
		movement_state = new_move;
		speed = movement_speed[static_cast<int>(new_move)];

		//캐릭터 상태 변화시 다른요소를 함수 포인터로 여 타 함수 실행
	}

	void PrintCurrentMovementState()
	{
		switch (movement_state)
		{
		case Character::Movement::Idle:
			cout << name << "의 현재 이동 상태 : idle, 현재 속도 : " << speed << endl;
			break;
		case Character::Movement::Walk:
			cout << name << "의 현재 이동 상태 : Walk, 현재 속도 : " << speed << endl;
			break;
		case Character::Movement::Run:
			cout << name << "의 현재 이동 상태 : Run, 현재 속도 : " << speed << endl;
			break;

		default:
			break;
		}
	}

private:
	static constexpr int movement_speed[static_cast<int>(Movement::Count)] = { 0, 200, 400 }; // Idle, Walk, Run

	std::string name;
	
	Movement movement_state = Movement::Idle;

	int speed = movement_speed[static_cast<int>(Movement::Idle)];
};

int main() {
	Character player(string("Player"));

	player.PrintCurrentMovementState();

	player.SetCharacterMovement(Character::Movement::Walk);

	player.PrintCurrentMovementState();

	cout << endl;

	Character enemy(string("Enemy"));

	enemy.PrintCurrentMovementState();

	enemy.SetCharacterMovement(Character::Movement::Run);

	enemy.PrintCurrentMovementState();

	//Movement::Run; // Movement 단독으로도 데이터를 사용 불가.

	Character::Movement::Idle; // Character를 통해 Movement의 데이터에 접근.
	return 0;
}