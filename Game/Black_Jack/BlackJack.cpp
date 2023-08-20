#include "BlackJack.h"
#include <iostream>
void BlackJack::Init()
{
	is_game_over = true;
	std::cout << "참여할 인원 수를 입력해주세요 : ";
	std::cin >> member_count;

	system("cls");
}

void BlackJack::Update()
{
}

void BlackJack::Render()
{
}

void BlackJack::Destroy()
{
}

void BlackJack::SetMemberCount(int member_count) { this->member_count = member_count; }

int BlackJack::GetMemberCount() { return this->member_count; }

void BlackJack::SetIsGameOver(bool is_game_over) { this->is_game_over = is_game_over; }

int BlackJack::GetIsGameOver() { return this->is_game_over; }
