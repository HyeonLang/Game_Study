#pragma once
#include "GameNode.h"

struct Box
{
	RECT box;
	float speed;
};

class Monsters : public GameNode
{

public:
	Monsters();
	~Monsters();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetLevel(int level) { this->level = level; }

	vector<Box>& GetBoxes() { return boxes; }
private:
	vector<Box> boxes;
	int spawn_delay;
	int level;
};

