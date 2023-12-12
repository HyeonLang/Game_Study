#pragma once
class Program
{
private:
	Scene* scene;
	DWORD deltatime = 0;
public:
	Program();
	~Program();

	void Update();
	void Render();

	void Create();
	void Delete();
};