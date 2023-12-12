// header.h : include file for standard system include files,
// or project specific include files
//

/*
	�̸� �����ϵ� ���
	- ���� �������� ���� �ڵ鸣 �̸� �������Ͽ� ������ ����� ������ ���Ͽ� ������
	�Ȱ��� ��� ������ �������ϴ� ��� �̸� �����ϵ� ��� ������ ����� ������ �ӵ��� ����Ų��.
	- ��ü������ ���� ���ų� ũ�Ⱑ Ŀ�� ������ �ð��� �� ����� �ڵ带 ���Խ�Ų��.
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

#define PROGRAM_TITLE L"������API����"

#define RECT_MAKE(x, y, s) {x - s / 2, y - s / 2, x + s / 2, y + s / 2 }
#define RECT_DRAW(rt) Rectangle(g_hDC, rt.left, rt.top, rt.right, rt.bottom)

// " "   : �Ϲ� ���ڿ�
// L" "  : �ѱ۰� ���� ��Ƽ ����Ʈ ���ڸ� ǥ���� �� ����ϴ� ���ڿ�

#include<string>

using namespace std;

extern HWND g_hWnd;
extern POINT g_mouse_pos;
extern HDC g_hDC;

#include"MainGame.h"