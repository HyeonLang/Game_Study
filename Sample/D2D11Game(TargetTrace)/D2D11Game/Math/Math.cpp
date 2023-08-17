#include "stdafx.h"
#include "Math.h"

std::random_device Math::rd;
std::mt19937 Math::mt(rd());

const int Math::Random(const int& min, const int& max)
{
	// uniform_int_distribution : 정수형 범위 난수
	return std::uniform_int_distribution<int>{min, max}(mt);
}

const float Math::Random(const float& min, const float& max)
{
	// uniform_real_distribution : 부동 소수점 범위 난수 
	return std::uniform_real_distribution<float>{min, max}(mt);
}

