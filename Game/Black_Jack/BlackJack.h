#pragma once
class BlackJack
{
public:
	void Init();
	void Update();
	void Render();
	void Destroy();

	void SetMemberCount(int member_count);
	int GetMemberCount();
	void SetIsGameOver(bool is_game_over);
	int GetIsGameOver();
private:
	int member_count;
	bool is_game_over;
};

