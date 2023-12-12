#pragma once
struct VertexUV 
{
	Float3 position;
	Float2 uv;

	VertexUV(float x, float y, float u, float v)
	{
		position = Float3(x, y, 0);
		uv = Float2(u, v);
	}

	// UV는 VertexUV.hlsl에서 설명
};