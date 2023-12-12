#include "pch.h"



Program::Program()
{
	Create();
	//scene = new TutorialScene();
	//scene = new SRTScene();
	//scene = new SolarScene();
	scene = new PlayerScene();
	// 바로 이 부분을 통해 프로그램이 어떤 Scene을 사용할 것인지를 설정
	// DX를 다루는 초반 구간에서는 Scene을 많아봐야 하나만 사용할 것이므로
	// 그 Scene을 여기서 설정하고, 나중에 필요하면 기존 Scene은 놔둔 채
	// 새로운 Scene을 여기에 등록해서 사용하는 식으로 프로그램을 구성할 예정
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
	// 원래는 프로그램에서 Render 함수가 호출되었을 때 이뤄져야 하지만
	// 지금 당장은 Scene을 한 번에 하나만 다루기 때문에
	// 그리고 Scene 내부에서 또 화면 초기화를 하기 때문에 여기서는 생략
	scene->Render();
	Device::Get()->Present();

}

void Program::Create()
{
	Device::Get(); // 싱글톤을 여기서 생성
	CreateProjection();
}

void Program::Delete()
{
	Device::Delete();
}

void Program::CreateProjection()
	// WBP변환에 사용될 행렬 중 투영(Projection) 행렬을 설정하는 함수
	// View는 줌인 줌아웃이 2D에서는 필요 없음. 따라서 같이 처리
{
	view = new MatrixBuffer();
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH
	(
		0.0f, (float)WIN_WIDTH,
		// 좌표계의 X좌표 기준을 0 ~ (WIN_WIDTH)까지의 범위로 설정
		(float)WIN_HEIGHT, 0.0f,
		// 좌표계의 Y좌표 기준을 (WIN_HEIGHT) ~ 0까지의 범위로 설정
		-1.0f, 1.0f
	);

	projection->Set(orthographic);

	view->SetVS(1);
	projection->SetVS(2);
}