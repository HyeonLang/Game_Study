#pragma once
class Player : public Transform
{
private:
	RectUV* rect;
	Float2 prev_pos;
	RectCollider* collider;

	ID3D11ShaderResourceView* srv;
	ID3D11SamplerState* sampler_state;
	// UV값을 이용해서 파일을 출력하는데 필요한 각 개체들

public:
	Player(Float2 pos, Float2 size, Float2 s, float a, Matrix* parent = NULL);
	~Player();

	void Update(DWORD* deltatime, Float2 target);
	void Render();
	 
};