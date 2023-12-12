#pragma once
class SRTScene : public Scene
{
	MatrixBuffer* world;
	MatrixBuffer* view;
	MatrixBuffer* projection;

	XMFLOAT4X4 world_matrix;
	// �Ǽ� �ڷ����� �̿��ϴ� 4x4�� ����� �ǹ��ϴ� �ڷ���(����ü)

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

