#pragma once
class Player : public Transform
{
private:
	RectUV* rect;

	ID3D11ShaderResourceView* srv;
	ID3D11SamplerState* sampler_state;
	// UV���� �̿��ؼ� ������ ����ϴµ� �ʿ��� �� ��ü��

public:
	Player(Float2 pos, Float2 size, Float2 s, float a, Matrix* parent = NULL);
	~Player();

	void Update(Float2 pos, Float2 target);
	void Render();
	 
};