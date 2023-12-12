#pragma once
class CircleCollider : public Collider
{
private:

public:
	CircleCollider();
	~CircleCollider();

	// Collider��(��) ���� ��ӵ�
	virtual bool IsPointCollision(Vector2 point) override;
	virtual bool IsCircleCollision(CircleCollider* collider) override;
	virtual bool IsRectCollision(RectCollider* collider) override;
	virtual void CreateLine() override;
};