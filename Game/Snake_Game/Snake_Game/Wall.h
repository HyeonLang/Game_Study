#pragma once
#include "utility.h"
#include "Point.h"
class Wall
{
public:
	Wall(int x, int y);
	Wall(Point p);
	~Wall();
	void Init(int x, int y);
	void Update(int delta);
	void Render();
	void Destroy();

	const Point& GetPosition() const { return position; }

private:
	Point position;
};

