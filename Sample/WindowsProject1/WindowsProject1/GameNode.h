#pragma once

class GameNode
{
public:
	GameNode() = default;
	virtual ~GameNode() = default;
	
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

