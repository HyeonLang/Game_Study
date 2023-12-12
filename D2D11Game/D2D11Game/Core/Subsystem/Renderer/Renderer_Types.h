#pragma once
// Renderer_Types.h
#include"stdafx.h"

enum class RenderableType : uint
{
	Opaque,
	Camera
};


enum class RasterizerStateType : uint
{
	Cull_Front_FILL_Solid,
	Cull_Back_FILL_Solid,
	Cull_None_FILL_Solid,
	Cull_Front_FILL_Wireframe,
	Cull_Back_FILL_Wireframe,
	Cull_None_FILL_Wireframe,
};

enum class BlendStateType : uint
{
	Disabled,
	Alpha
};