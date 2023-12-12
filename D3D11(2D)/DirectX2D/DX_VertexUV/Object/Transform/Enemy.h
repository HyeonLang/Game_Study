#pragma once
class Enemy : public Transform
{
private:
	RectUV* rect;

	ID3D11ShaderResourceView* srv;
	ID3D11SamplerState* sampler_state;
	// UV값을 이용해서 파일을 출력하는데 필요한 각 개체들

	Float2 init_pos; // 초기 위치
	float velocity;

	DWORD rotate_timer;

public:
	Enemy(Float2 pos, Float2 size, Float2 s, float a, float v, Matrix* parent = NULL);
	~Enemy();

	void Update(DWORD time);
	void Render();
};