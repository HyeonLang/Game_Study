#pragma once
class CircleCollider : public Collider
{
private:

public:
	CircleCollider();
	~CircleCollider();

	// Collider을(를) 통해 상속됨
	virtual bool IsPointCollision(Vector2 point) override;
	virtual bool IsCircleCollision(CircleCollider* collider) override;
	virtual bool IsRectCollision(RectCollider* collider) override;
	virtual void CreateLine() override;
};