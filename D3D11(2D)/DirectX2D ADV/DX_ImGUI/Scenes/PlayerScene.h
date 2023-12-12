#pragma once
class PlayerScene : public Scene
{
private:
	MatrixBuffer* world_buffer;
	Player* player;
	Vortex* sun;
	Vortex* cursor;

	Enemy* missiles[4];
public:
	PlayerScene();
	~PlayerScene();

	virtual void Update(DWORD* deltatime) override;
	virtual void Render() override;
	virtual void PostRender() override;
};