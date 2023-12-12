#include "pch.h"

Program::Program()
{
	Create();
	//scene = new TutorialScene();
	//scene = new SRTScene();
	//scene = new SolarScene();
	//scene = new PlayerScene();
	scene = new CollisionScene();
	// �ٷ� �� �κ��� ���� ���α׷��� � Scene�� ����� �������� ����
	// DX�� �ٷ�� �ʹ� ���������� Scene�� ���ƺ��� �ϳ��� ����� ���̹Ƿ�
	// �� Scene�� ���⼭ �����ϰ�, ���߿� �ʿ��ϸ� ���� Scene�� ���� ä
	// ���ο� Scene�� ���⿡ ����ؼ� ����ϴ� ������ ���α׷��� ������ ����
}

Program::~Program()
{
	delete scene;
}

void Program::Update()
{
	scene->Update(&deltatime);
}

void Program::Render()
{
	// Device::Get()->Clear();
	// ������ ���α׷����� Render �Լ��� ȣ��Ǿ��� �� �̷����� ������
	// ���� ������ Scene�� �� ���� �ϳ��� �ٷ�� ������
	// �׸��� Scene ���ο��� �� ȭ�� �ʱ�ȭ�� �ϱ� ������ ���⼭�� ����

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	// ImGUI : �з����� ���� ���� �� �� �ְ� ��� ������ Graphic User Interface
	// DX11 / Win32 ȯ�濡�� â�� ������̶�� �˸�
	// NewFrame()���� â�� �����.

	string hello = "Hello, ImGui!";
	ImGui::Text(hello.c_str());

	scene->Render();
	scene->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	Device::Get()->Present();
}

void Program::Create()
{
	Device::Get(); // �̱����� ���⼭ ����

	ImGui::CreateContext();		// ImGUI ��ü ����
	ImGui::StyleColorsDark();	// â�� ������ ���������� ����

	ImGui_ImplWin32_Init(hWnd);	// ������ �ü������ ������ ����
	ImGui_ImplDX11_Init(DEVICE, DVC);	// DX11 ȯ�濡�� ������ ����

	CreateProjection();
}

void Program::Delete()
{
	Device::Delete();
}

void Program::CreateProjection()
	// WBP��ȯ�� ���� ��� �� ����(Projection) ����� �����ϴ� �Լ�
	// View�� ���� �ܾƿ��� 2D������ �ʿ� ����. ���� ���� ó��
{
	view = new MatrixBuffer();
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH
	(
		0.0f, (float)WIN_WIDTH,
		// ��ǥ���� X��ǥ ������ 0 ~ (WIN_WIDTH)������ ������ ����
		(float)WIN_HEIGHT, 0.0f,
		// ��ǥ���� Y��ǥ ������ (WIN_HEIGHT) ~ 0������ ������ ����
		-1.0f, 1.0f
	);

	projection->Set(orthographic);

	view->SetVS(1);
	projection->SetVS(2);
}