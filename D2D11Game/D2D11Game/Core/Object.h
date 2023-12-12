#pragma once

//TODO:
#include"stdafx.h"

class Object
{
public:
	Object() { id = GUIDGenerator::Generate(); }
	virtual ~Object() = default;

	uint GetID() const { return id; }
	void SetID(const uint& id) { this->id = id; }

private:
	uint id = 0;
};