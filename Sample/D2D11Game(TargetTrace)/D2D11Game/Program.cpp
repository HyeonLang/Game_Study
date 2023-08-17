// Program.cpp
#include"stdafx.h"
#include"Core/Window.h"
#include"Core/Execute.h"

int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{

	// ������ ����
	Window::Create(hInstance, 1000, 1000);
	Window::Show();

	Settings::Get().SetWindowHandle(Window::global_handle);
	Settings::Get().SetWidth(static_cast<float>(Window::GetWidth()));
	Settings::Get().SetHeight(static_cast<float>(Window::GetHeight()));

	Execute* execute = new Execute();

	// ���� �κ� 
	while (Window::Update())
	{
		execute->Update();
		execute->Render();
	}

	SAFE_DELETE(execute);

	// ������ �ı�
	Window::Destroy();
}