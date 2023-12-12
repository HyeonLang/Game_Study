#pragma once

class Collider : public Transform
{
protected:
	enum class TYPE
	{
		RECT,
		CIRCLE
	} type;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	ColourBuffer* colourBuffer;

	MatrixBuffer* worldBuffer;

	vector<VertexPos> verticies;

public:
	Collider();
	virtual ~Collider();

	void Render();
	 
	virtual bool IsCollision(Collider* collider);

	virtual bool IsPointCollision(Vector2 point) = 0;
	virtual bool IsCircleCollision(class CircleCollider* collider) = 0;
	virtual bool IsRectCollision(class RectCollider* collider) = 0;
	// 순수 가상함수에서 후 시점에서 만들어지는 클래스는 class를 명시
	void SetColor(float r, float g, float b)
	{
		colourBuffer->data.colour = Float4(r, g, b, 1);
	}

protected:
	virtual void CreateLine() = 0;
};