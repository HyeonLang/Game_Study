// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.
#pragma once

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가

#include "targetver.h"
#include "framework.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <windowsx.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

#define WIN_START_X 100
#define WIN_START_Y 100
// 윈도우 창이 처음에 열릴 때 어느 위치에서 열릴지를 결정할 매크로

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define WIN_CENTER_X (WIN_WIDTH * 0.5f)
#define WIN_CENTER_Y (WIN_HEIGHT * 0.5f)
// 화면 중앙의 좌표를 매크로로서 손쉽게 이용할 수 있도록 선언

#define DEVICE Device::Get()->GetDevice()
// 프레임워크의 Device 싱글톤 클래스의 객체를 가져와 ID3D11Device 객체에 접근

#define DVC Device::Get()->GetDeviceContext()
// D3D11DeviceContext 객체에 접근

// 매크로는 코드 자체를 대신하는 방식이기 때문에 세미콜론을 넣으면 안된다.

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "Library/DirectXTex.h"

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
// XMFLOAT 시리즈 : DX에서 사용되는, 실수 여러개를 묶어놓은 구조체
// 용도 : "딱 이 개수만큼의 실수를 묶어서 하나의 구조체로 사용하겠다"
// 각 실수들을 따로따로 정의하는 것은 번거롭기도 하고 DX에서 주로 사용하는 형태와 포맷을 맞추기 편함
// 따라서 구조체로서 편히 묶어 사용하기 위해 위와 같이 typedef를 이용해 별명 생성

// Float4와 Float3는 각각 색상 / 좌표 입력에 주로 사용될 예정

typedef XMMATRIX Matrix;
// XMMATRIX는 DX에서 각종 변환에 사용할 기본적인 형태의 행렬
// 입력받은 자료 형태에 따라 4개 값을 가진 벡터가 되거나 4x4 행렬이 되는 union 자료형


// 이 헤더에 포함하는 여러 헤더들은
// 반드시 헤더를 포함하는 순서가 정확해야 함
// 지금은 헤더가 많지 않아 괜찮지만, 점차 헤더의 개수가 폭증할 예정이고
// 한 헤더가 다른 헤더를 참고해야만 하는 경우가 꽤 많아서
// 반드시 여기서 헤더를 포함하는 순서를 지켜야 함

//Framework Header
#include"Framework/Math/Vector2.h"
#include"Framework/Buffer/VertexBuffer.h"
#include"Framework/Buffer/ConstBuffer.h"
#include"Framework/Buffer/GlobalBuffer.h"
#include"Framework/Math/Transform.h"
#include"Framework/System/Device.h"
#include"Framework/Shader/VertexShader.h"
#include"Framework/Shader/PixelShader.h"


//Object Header
#include"Object/Shapes/Vertex.h"
#include"Object/Shapes/VertexUV.h"
#include"Object/Shapes/Shape.h"
#include"Object/Shapes/ShapeList.h"

#include"Object/Transform/TransformList.h"

//Program Header
#include"Scenes/Scene.h"
#include"Scenes/SceneList.h"
#include"Program/Program.h"


extern HWND hWnd;
extern DWORD time_stamp;
extern UINT key_map;
extern Float2 object_pos;
extern POINT mouse_pos;
extern RECT windows_size;

#endif //PCH_H