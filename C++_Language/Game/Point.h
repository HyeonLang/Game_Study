#pragma once

struct Point
{
public:
	Point(int x = 0, int y = 0) : x(x), y(y) {}

	bool operator==(const Point& rhs) const //좌표 비교 연산자
	{
		return x == rhs.x && y == rhs.y;
	}

public:
	int x;
	int y;
};

