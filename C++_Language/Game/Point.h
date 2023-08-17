#pragma once

struct Point
{
public:
	Point(int x = 0, int y = 0) : x(x), y(y) {}

	bool operator==(const Point& rhs) const //��ǥ �� ������
	{
		return x == rhs.x && y == rhs.y;
	}

public:
	int x;
	int y;
};

