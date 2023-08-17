// 15_nested_type.cpp

#include <iostream>
using namespace std;


class Character {


public:
	//��ø Ÿ��
	enum class Movement {
		Min = 0,
		Idle = Min,
		Walk,
		Run,
		Max = Run,
		Count // ������ ���Ҹ� count�� �Ͽ� �ε��� ������ �ľ� ���� : Count�� idx = 3;
	};

public:
	Character(const string& str) : name(str) {} //��� �ʱ�ȭ ����Ʈ

	void SetCharacterMovement(Movement new_move) {
		movement_state = new_move;
		speed = movement_speed[static_cast<int>(new_move)];

		//ĳ���� ���� ��ȭ�� �ٸ���Ҹ� �Լ� �����ͷ� �� Ÿ �Լ� ����
	}

	void PrintCurrentMovementState()
	{
		switch (movement_state)
		{
		case Character::Movement::Idle:
			cout << name << "�� ���� �̵� ���� : idle, ���� �ӵ� : " << speed << endl;
			break;
		case Character::Movement::Walk:
			cout << name << "�� ���� �̵� ���� : Walk, ���� �ӵ� : " << speed << endl;
			break;
		case Character::Movement::Run:
			cout << name << "�� ���� �̵� ���� : Run, ���� �ӵ� : " << speed << endl;
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

	//Movement::Run; // Movement �ܵ����ε� �����͸� ��� �Ұ�.

	Character::Movement::Idle; // Character�� ���� Movement�� �����Ϳ� ����.
	return 0;
}