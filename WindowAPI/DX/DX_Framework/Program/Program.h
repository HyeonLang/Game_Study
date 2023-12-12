#pragma once
#include "framework.h"

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