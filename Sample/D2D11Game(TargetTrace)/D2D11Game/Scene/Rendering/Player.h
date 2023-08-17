#pragma once
#include "Rect.h"

class Player final : public Rect
{
public:
	Player(class Graphics* graphics, const D3DXCOLOR& color);
	~Player();

	virtual void Event() override;

private:
	virtual void Move() override;
	virtual void Restore() override;
	
private:
	Stopwatch restore_stopwatch;
	float speed = 3.0f;

};

