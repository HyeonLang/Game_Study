#pragma once
#include"utility.h"
#include"Point.h"
class Item
{
public:
	virtual void Init() = 0;
	virtual void Update(int delta) = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

	const Point& GetPosition() const { return position; }
	void SetPosition(const Point& position) { this->position = position; }
	void SetPosition(const int& x, const int& y) { this->position = Point(x, y); }

	const bool GetIsActive() const { return isActive; }
	void SetIsActive(bool b) { isActive = b; }

protected:
	Point position;
	clock_t duration_time_ms;
	clock_t limit_time_ms = 10000;
	bool isActive = false;
};

