// 09_enum_class.cpp

#include<iostream>

int main()
{
	// c style enum의 문제점
	{
		// 중복문제를 해결하기위해 멤버이름 앞에 자료형의 이름을 붙여줘야 한다.

		// 같은 색상 열거형이지만 종류가 달라 구분하기 위해 이름을 붙여야함
		enum Color
		{
			Color_Red,
			Color_Blue
		};

		enum Tint_Color
		{
			Tint_Color_Red,
			Tint_Color_Blue
		};
		
		enum Fruit
		{
			APPLE,
			BANANA
		};

		// 내부적으로 정수형 데이터이기 때문에 상관없는 자료형으로 암시적 캐스팅이 됨
		int test_color = Color_Red;

		Color color = Color_Red;
		Fruit fruit = APPLE;

		// 다른 의미를 가지는 값이지만 내부적으로 정수형 데이터이기 때문에 비교가 가능
		if (color == fruit)
		{

		}

		// 다른 의미를 가지는 값이지만 내부적으로 정수형 데이터이기 때문에 비교가 가능
		if (color == 0)
		{

		}

	}

	/*
		Scoped Enumerations(c++ 11)
		- 영역 제한 열거형
	*/

	{
		enum class BaseColor : unsigned long long int // 자료형을 지정해 줄 수 있다. 실수형, 문자형은 안됨
		{
			Red,
			Blue,
		};

		enum class BaseTintColor
		{
			Red,
			Blue
		};

		// 이름공간을 무조건 붙여야 하므로 중복 문제를 해결할 수 있다
		BaseColor::Red;
		BaseTintColor::Red;

		BaseColor c = BaseColor::Red;
		BaseTintColor tc = BaseTintColor::Red;

		// 같은 타입끼리만 비교 가능
		//if (c == tc)
		{

		}

		if (static_cast<int>(c) == 0)
		{

		}

		// 한번에 자동완성 가능
		// switch 자동완성 -> 변수나 열거형 자료형 입력 -> 아무 위치에 마우스 왼클릭 
		switch (c)
		{
		case BaseColor::Red:
			break;
		case BaseColor::Blue:
			break;
		default:
			break;
		}

	}

	return 0;
}