#pragma once

class Engine final
{
public:
	Engine();
	~Engine();

	void Update();

private:
	class Context* context = nullptr;
};

