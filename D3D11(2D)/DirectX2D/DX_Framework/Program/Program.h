#pragma once
class Program
{
private:
	Scene* scene;

public:
	Program();
	~Program();

	void Update();
	void Render();

	void Create();
	void Delete();
};