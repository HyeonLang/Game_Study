#pragma once
class SRTScene : public Scene
{
	MatrixBuffer* world;
	MatrixBuffer* view;
	MatrixBuffer* projection;

	XMFLOAT4X4 world_matrix;
	// 실수 자료형을 이용하는 4x4의 행렬을 의미하는 자료형(구조체)

	MatrixBuffer* worldBuffer;

	Box* srt_box;

	Vortex* star;
	Vortex* star_stub;
	Vortex* satelite;
	

public:
	SRTScene();
	~SRTScene();

	virtual void Update() override;
	virtual void Render() override;
};

