#pragma once

class CollisionScene : public Scene 
{
private:
	Collider* collider;
	Collider* target;
public:
	CollisionScene();
	~CollisionScene();

	// Scene을(를) 통해 상속됨
	virtual void Update(DWORD* deltatime) override;
	virtual void Render() override;
	virtual void PostRender() override;
};
