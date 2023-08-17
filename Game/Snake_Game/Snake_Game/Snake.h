#pragma once

#include "Point.h"
#include "utility.h"
class Snake
{
public:
	virtual void Init(int x = 0, int y = 0) = 0;
	void Update(int delta);
	virtual void Render() = 0;
	virtual void Destroy() = 0;

	const Point& GetPosition() const { return position; }
	void SetPosition(const Point& position) { this->position = position; }
	void SetPosition(const int& x, const int& y) { this->position = Point(x, y); }
	const Point& GetNextPosition() const { return next_position; }
	void SetNextPosition(const Point& next_position) { this->next_position = next_position; }
	void SetNextPosition(const int& x, const int& y) { this->next_position = Point(x, y); }
	const Point& GetPrePosition() const { return pre_position; }
	void SetPrePosition(const Point& pre_position) { this->pre_position = pre_position; }
	void SetPrePosition(const int& x, const int& y) { this->pre_position = Point(x, y); }
public:
	Point position;
	Point next_position;
	Point pre_position;
};

