#pragma once
class Card
{
public:
	enum class PATTERN {
		CLOBER = 0,
		HART = 1,
		DIAMOND = 2,
		CLOVER = 3
	};
	enum class NUMBER {
		ACE = 1,
		TWO = 2,
		THREE = 3,
		FOUR = 4,
		FIVE = 5,
		SIX = 6,
		SEVEN = 7,
		EIGHT = 8,
		NINE = 9,
		TEN = 10,
		J = 10,
		Q = 10,
		K = 10
	};
public:

private:
	PATTERN card_pattern;
	NUMBER card_number;
};

