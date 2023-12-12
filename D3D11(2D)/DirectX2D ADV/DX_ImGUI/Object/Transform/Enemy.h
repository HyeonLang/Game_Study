#pragma once
enum class ENEMY_STATE
{
	NONE = 0,
	RANDOM,	// 무작위 기동
	CHASE,	// 플레이어 추적
	MAX = 3
};
class Enemy : public Transform
{
private:
	RectUV* rect;

	ID3D11ShaderResourceView* srv;
	ID3D11SamplerState* sampler_state;
	// UV값을 이용해서 파일을 출력하는데 필요한 각 개체들

	Float2 init_pos; // 초기 위치
	float velocity;
	ENEMY_STATE state;

	DWORD rotate_timer;

public:
	Enemy(Float2 pos, Float2 size, Float2 s, float a, float v, ENEMY_STATE state, Matrix* parent = NULL);
	~Enemy();

	void Update(DWORD time, Float2* target);
	void Render();
};