#pragma once
enum class ENEMY_STATE
{
	NONE = 0,
	RANDOM,	// ������ �⵿
	CHASE,	// �÷��̾� ����
	MAX = 3
};
class Enemy : public Transform
{
private:
	RectUV* rect;

	ID3D11ShaderResourceView* srv;
	ID3D11SamplerState* sampler_state;
	// UV���� �̿��ؼ� ������ ����ϴµ� �ʿ��� �� ��ü��

	Float2 init_pos; // �ʱ� ��ġ
	float velocity;
	ENEMY_STATE state;

	DWORD rotate_timer;

public:
	Enemy(Float2 pos, Float2 size, Float2 s, float a, float v, ENEMY_STATE state, Matrix* parent = NULL);
	~Enemy();

	void Update(DWORD time, Float2* target);
	void Render();
};