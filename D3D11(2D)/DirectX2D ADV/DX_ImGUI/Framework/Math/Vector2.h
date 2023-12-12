#pragma once
class Vector2 : public Float2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(Float2 value);

	Vector2 operator+ (const Vector2& value) const;
	Vector2 operator- (const Vector2& value) const;
	Vector2 operator* (const Vector2& value) const;
	Vector2 operator/ (const Vector2& value) const;


	Vector2 operator* (const float& value) const;
	Vector2 operator/ (const float& value) const;

	void operator+= (const Vector2& value);
	void operator-= (const Vector2& value);
	void operator*= (const float& value);
	void operator/= (const float& value);
};

// Float2를 쉽게 생성하고 쉽게 이용하기 위해 만드는 클래소