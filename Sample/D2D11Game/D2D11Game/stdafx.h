#pragma once

#ifdef _DEBUG

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#endif

#define DIRECTINPUT_VERSION 0x0800
#define NOMINMAX

#pragma warning(disable : 4506)

using uint = unsigned int;

#include<Windows.h>
#include<assert.h>

//STD
#include<vector>
#include<iostream>
#include<sstream> 
#include<unordered_map>
#include<random>
#include<chrono>
#include<functional>
#include<memory>
#include<map>
#include<typeinfo>
#include<mutex>
#include<filesystem>

#include<d3dcompiler.h>
#include<d3d11.h>
#include<D3DX10math.h>
#include<D3DX11async.h>
#include<dinput.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


#define SAFE_RELEASE(p) {if(p) { (p)->Release(); (p) = nullptr; }}
#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }}

// Utility
#include"Utility/GeometryGenerator.h"
#include"Utility/GUIDGenerator.h"
#include"Utility/Xml.h"

//Math
#include"Math/Math.h"

//Framework
#include"Core/Settings.h"
#include"Core/Object.h"

//Subsystem
#include"Core/Context.h"
#include"Core/Subsystem/Graphics.h"
#include"Core/Subsystem/SceneManager.h"
#include"Core/Subsystem/Timer.h"
#include"Core/Subsystem/Renderer/Renderer.h"
#include"Core/Subsystem/ResourceManager.h"
#include"Core/Subsystem/InputManager.h"

// D3D11
#include"Core/D3D11/Vertex/Vertex.h"
#include"Core/D3D11/Vertex/Geometry.h"

#include"Core/D3D11/InputAssembler/D3D11_VertexBuffer.h"
#include"Core/D3D11/InputAssembler/D3D11_IndexBuffer.h"
#include"Core/D3D11/InputAssembler/D3D11_InputLayout.h"

#include"Core/D3D11/Shader/D3D11_Shader.h"
#include"Core/D3D11/Shader/D3D11_ConstantBuffer.h"
#include"Core/D3D11/Shader/D3D11_Texture.h"
#include"Core/D3D11/Shader/D3D11_SamplerState.h"

#include"Core/D3D11/Rasterizer/D3D11_RasterizerState.h"
#include"Core/D3D11/Rasterizer/D3D11_Viewport.h"

#include"Core/D3D11/OutputMerger/D3D11_BlendState.h"

#include"Core/D3D11/D3D11_Pipeline.h"

// Resources
#include"Resource/Animation.h"

// ImGui
#include "Utility/ImGui/imgui.h"
#include "Utility/ImGui/imgui_impl_win32.h"
#include "Utility/ImGui/imgui_impl_dx11.h"

// LogSystem
#include "Core/LogSystem/LogSystem.h"