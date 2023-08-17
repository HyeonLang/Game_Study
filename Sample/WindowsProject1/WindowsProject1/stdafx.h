// header.h : include file for standard system include files,
// or project specific include files
//

/*
	미리 컴파일된 헤더
	- 자주 변경하지 않을 코들르 미리 컴파일하여 컴파일 결과를 별도의 파일에 저장해
	똑같은 헤더 파일을 컴파일하는 경우 미리 컴파일된 헤더 파일을 사용해 컴파일 속도를 향상시킨다.
	- 교체할일이 별로 없거나 크기가 커서 컴파일 시간이 긴 헤더나 코드를 포함시킨다.
*/

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<stack>
#include<time.h>
#include<vector>

#define WINSIZE_X 640
#define WINSIZE_Y 720

#define PROGRAM_TITLE L"윈도우API게임"

#define RECT_MAKE(x, y, s) {x - s / 2, y - s / 2, x + s / 2, y + s / 2 }
#define RECT_DRAW(rt) Rectangle(g_hDC, rt.left, rt.top, rt.right, rt.bottom)

// " "   : 일반 문자열
// L" "  : 한글과 같은 멀티 바이트 문자를 표시할 때 사용하는 문자열

#include<string>

using namespace std;

extern HWND g_hWnd;
extern POINT g_mouse_pos;
extern HDC g_hDC;

#include"MainGame.h"