#pragma once
#include"Point.h"
#include"Bullet.h"

constexpr int bullet_size = 10;

class Player
{
public:
	friend class ShootGame;

public:
	Player();
	~Player();

	void Init();
	void Update(int delta);
	void Render();
	void Destroy();

	const Point& GetPosition() { return position; }

	void SetPosition(const Point& position) { this->position = position; }
	void SetPosition(const int& x, const int& y) { this->position = Point(x, y); }

	void Shoot();

	Bullet* GetBullets() { return bullets; }

private:
	Point position;

	Bullet bullets[bullet_size];
	int bullet_count = 0;
};

