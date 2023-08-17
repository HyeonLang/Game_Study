#pragma once
#include "GameNode.h"

class MainGame final : public GameNode
{
public:
	MainGame();
	~MainGame();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	int level;
	int score;

	class Player* player;
	class Monsters* monsters;
};

