#pragma once
#include "Rect.h"
class Monster final : public Rect
{
public:
	Monster(class Graphics* graphics, const D3DXCOLOR& color);
	~Monster();

	virtual void Event() override;

private:
	virtual void Move() override;
	virtual void Restore() override;

private:
	Stopwatch stopwatch;
	Stopwatch restore_stopwatch;
	Direction direction = Direction::Right;
};

