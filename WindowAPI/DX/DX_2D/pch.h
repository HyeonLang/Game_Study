// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가


// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
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
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

// C 런타임 헤더 파일입니다.
#include <d3d11.h>			// DirectX 3D 11버전 라이브러리 헤더
#include <d3dcompiler.h>	// DirectX 3D 처리에 필요한 기능 헤더 Shader Load
#include <DirectXMath.h>	// DirectX 처리에 사용되는 각종 연산 관련 라이브러리 헤더

#pragma comment(lib, "d3d11.lib")		// d3d11.h에 필요한 라이브러리 가져오기
#pragma comment(lib, "d3dcompiler.lib")	// d3dcompiler.h에 필요한 라이브러리 가져오기

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
// Direct에서 계산에 사용되는 실수 여러개를 묶은 구조체
// 용도 : 실수를 각각의 숫자만큼의 개수를 묶어 사용. Float3, Float4은 각각 위치, 색지정에 자주 사용될 것

// 코드에서 보다시피 원래 이름은 XM이라고 붙어있는 구조체이지만
// 사용하기 편하게 Float2,3,4라는 이름을 붙여둔 것

// Framework Header Files
#include "Framework/System/Device.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

// Object Header Files
#include "Object/Shapes/Vertex.h"
#include "Object/Shapes/Shape.h"
#include "Object/Shapes/Triangles.h"
#include "Object/Shapes/Hexagons.h"

// Program Header Files
#include "Scenes/Scene.h"
#include "Scenes/TutorialScene.h"
#include "Program/Program.h"



//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>

extern HWND hWnd;


#endif //PCH_H
