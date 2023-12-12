#pragma once
class Program
{
private:
	Scene* scene;

	MatrixBuffer* view;
	MatrixBuffer* projection;

	void CreateProjection();

	DWORD deltatime = 0;

public:
	Program();
	~Program();

	void Update();
	void Render();

	void Create();
	void Delete();
};