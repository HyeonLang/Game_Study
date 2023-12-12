// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

// 윈도우 창의 시작 지점 좌표 상수
#define WIN_START_X 100
#define WIN_START_Y 100

// 윈도우 창의 크기 상수
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

// 윈도우 창의 중점 좌표 상수
#define WIN_CENTER_X (WIN_WIDTH * 0.5f)
#define WIN_CENTER_Y (WIN_HEIGHT * 0.5f)

// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <d3d11.h>			// DirectX 3D 11버전 라이브러리 헤더
#include <d3dcompiler.h>	// DirectX 3D 처리에 필요한 기능 헤더
#include <DirectXMath.h>	// DirectX 처리에 사용되는 각종 연산 관련 라이브러리 헤더

#pragma comment(lib, "d3d11.lib")		// d3d11.h에 필요한 라이브러리 가져오기
#pragma comment(lib, "d3dcompiler.lib")	// d3dcompiler.h에 필요한 라이브러리 가져오기

using namespace DirectX;

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
