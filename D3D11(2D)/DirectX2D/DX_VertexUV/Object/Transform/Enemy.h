#pragma once
class Enemy : public Transform
{
private:
	RectUV* rect;

	ID3D11ShaderResourceView* srv;
	ID3D11SamplerState* sampler_state;
	// UV���� �̿��ؼ� ������ ����ϴµ� �ʿ��� �� ��ü��

	Float2 init_pos; // �ʱ� ��ġ
	float velocity;

	DWORD rotate_timer;

public:
	Enemy(Float2 pos, Float2 size, Float2 s, float a, float v, Matrix* parent = NULL);
	~Enemy();

	void Update(DWORD time);
	void Render();
};