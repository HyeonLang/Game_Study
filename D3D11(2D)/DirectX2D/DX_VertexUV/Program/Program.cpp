#include "pch.h"



Program::Program()
{
	Create();
	//scene = new TutorialScene();
	//scene = new SRTScene();
	//scene = new SolarScene();
	scene = new PlayerScene();
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
	scene->Render();
	Device::Get()->Present();

}

void Program::Create()
{
	Device::Get(); // �̱����� ���⼭ ����
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