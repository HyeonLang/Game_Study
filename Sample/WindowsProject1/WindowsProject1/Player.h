#pragma once
#include "GameNode.h"

class Player final : public GameNode
{
public:
	Player();
	~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	RECT& GetBox() { return box; }

private:
	POINT pos;
	RECT box;
	float speed;
};

