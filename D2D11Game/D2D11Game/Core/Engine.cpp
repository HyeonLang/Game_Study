#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	context = new Context();

	context->RegisterSubsystem<Timer>();
	context->RegisterSubsystem<ResourceManager>();
	context->RegisterSubsystem<InputManager>();

	context->RegisterSubsystem<Graphics>();
	context->RegisterSubsystem<SceneManager>();

	context->RegisterSubsystem<Renderer>();

	context->InitializeSubsystems();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(Settings::Get().GetWindowHandle());
	auto graphics = context->GetSubsystem<Graphics>();
	ImGui_ImplDX11_Init(graphics->GetDevice(), graphics->GetDeviceContext());
}

Engine::~Engine()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SAFE_DELETE(context);
}

void Engine::Update()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	context->UpdateSubsystems();
}
