#pragma once
class RectCollider : public Collider
{
private:
	Vector2 size;
	virtual void CreateLine() override;
public:
	RectCollider(Vector2 size);
	~RectCollider();


	// Collider을(를) 통해 상속됨
	virtual bool IsPointCollision(Vector2 point) override;

	virtual bool IsCircleCollision(CircleCollider* collider) override;

	virtual bool IsRectCollision(RectCollider* collider) override;

	Vector2 Size() { return size * GlobalScale(); }

};