// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <time.h>
#include <vector>
#include <random>
#include <thread>

extern int WINSIZE_X;
extern int WINSIZE_Y;

#define PROGRAM_TITLE L"API_지뢰찾기"
#define RECT_DRAW(rt) Rectangle(g_hdc, rt.left, rt.top, rt.right, rt.bottom)

extern HWND g_hwnd;
extern HDC g_hdc;
extern POINT mouse;

using namespace std;
#include "MainGame.h"
