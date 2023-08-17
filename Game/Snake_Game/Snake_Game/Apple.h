#pragma once
#include "Item.h"
class Apple : public Item
{
public:
	Apple();
	~Apple();
	void Init();
	void Update(int delta);
	void Render();
	void Destroy();
};

