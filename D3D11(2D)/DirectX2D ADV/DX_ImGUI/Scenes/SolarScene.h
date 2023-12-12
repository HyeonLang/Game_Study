#pragma once
class SolarScene : public Scene
{
private:
	MatrixBuffer* world;
	MatrixBuffer* view;
	MatrixBuffer* projection;

	XMFLOAT4X4 world_matrix;

	Box* srt_box;

	Vortex* sun;
	Vortex* sun_stub;
	Vortex* mercury;
	Vortex* venus;
	Vortex* earth;

	Vortex* earth_stub;
	Vortex* moon;

	Box* player;
	Box* target;

public:
	SolarScene();
	~SolarScene();

	virtual void Update(DWORD* deltatime) override;
	virtual void Render() override;
};