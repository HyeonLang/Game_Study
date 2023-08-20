#include "utility.h"


void gotoxy(int x, int y, const char* string)
{
	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}