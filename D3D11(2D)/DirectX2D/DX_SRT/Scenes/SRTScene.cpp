#include "pch.h"
#include "SRTScene.h"

SRTScene::SRTScene()
{
	world = new MatrixBuffer();
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
	// 왼손 좌표계용으로 사용자가 직접 지정한 값들을 이용한 직교 투영 행렬을 만들라는 명령
	// "왼쪽 아래"를 기점으로 해서 거기서부터 우리가 표시할 공간의 범위를 지정하고
	// 그 값들을 행렬로서 구성해 만들라는 명령

	// Y좌표 설정을 보면 시작점이 WIN_HEIGHT고 종료점이 0인 걸 확인할 수 있음
	// 이는 좌표를 입력했을 때 값이 높을 수록 오른쪽 값(=아래쪽), 낮을 수록 왼쪽 값(위쪽)에 더 가까워진다는 의미

	// 즉, 이렇게 WIN_HEIGHT를 앞쪽에 넣는다면 우리가 API에서 좌표를 입력할 때 왼쪽 위를 기준으로 했던 것과
	// 동일하게 이용할 수 있음
	// 반대로 수학을 배울 때 사용했던 것처럼 왼쪽 아래를 0,0으로 놓겠다면 위 함수에서 WIN_HEIGHT와 0.0f의 위치를 바꾸면 됨

	// 중앙을 0,0으로 하고 싶다면 화면 전체의 절반의 길이를 음수와 양수로 넣는 식으로 처리하는 것도 가능
	// 여기선 API와 통일하기 위해 위와 같이 작성

	// -1.0~1.0까지의 값을 이용해가지고 정점의 위치를 표기하던 것을
	// 우리가 API에서 각 좌표를 직접 지정하던 식으로 바꾸는 것

	projection->Set(orthographic);

	world_matrix._11 = 1; // 행렬의 1번 행의 1번 열에 있는 데이터를 1로 설정한다
	world_matrix._22 = 1; // 행렬의 2번 행의 2번 열에 있는 데이터를 1로 설정한다
	world_matrix._33 = 1; // 행렬의 3번 행의 3번 열에 있는 데이터를 1로 설정한다
	world_matrix._44 = 1; // 행렬의 4번 행의 4번 열에 있는 데이터를 1로 설정한다

	srt_box = new Box(Float2(640.0f, 480.0f), Float2(1.0f, 2.2f), 0);

	worldBuffer = new MatrixBuffer();


	star = new Vortex(
		Float2((float)WIN_CENTER_X / 2, (float)WIN_CENTER_Y),	// 위치
		Float2(2.0f, 0.5f),		// x,y 사이즈
		0.0f,					// 초기 방향
		100.0f,					// 크기
		240,					// 표현 정점 갯수 
		-0.3f					// 회전 방향 및 속도
	);
	star->SetColor(Float4(0.8f, 0.8f, 0.1f, 1.0f));

	star_stub = new Vortex(Float2((float)WIN_CENTER_X / 2, (float)WIN_CENTER_Y), Float2(1.0f, 1.0f), 0.0f, 0.0f, 0, 0.3f);

	satelite = new Vortex(Float2(100.0f, 0.0f), Float2(1.0f, 1.0f), M_PI_4,
		25.0f, 5, 3.0f);
	satelite->SetColor(Float4(0.4f, 0.4f, 0.4f, 1.0f));
}

SRTScene::~SRTScene()
{
	delete world;
	delete view;
	delete projection;
	delete srt_box;
	delete worldBuffer;
	delete star;
	delete satelite;
}

void SRTScene::Update()
{
	srt_box->Update();
	star->Update();

	star_stub->Update();
	satelite->Update(star_stub->GetWorld());
	// satelite는 star위치에 기반한다.
	// star에 적용된 scale, rotate 등이 적용됨.

}

void SRTScene::Render()
{
	Device::Get()->Clear();
	// 화면을 초기화

	world->SetVS(0);
	view->SetVS(1);
	projection->SetVS(2);
	// 출력하기 전 WVP 변환에 사용될 행렬들을 정점 셰이더에 등록
	// 왜 이런 번호로 넣어야 하는지는 VertexShader.hlsl에 설명

	// W, V, P라는 이 3가지 버퍼들은 상수 버퍼
	// 상수 버퍼 = 정점 셰이더나 픽셀 셰이더에서 사용되는 각종 상수들을 모아놓는 버퍼
	// 이 버퍼에다가 그래픽 표현에 사용될 각종 상수들을 저장했다가
	// 이를 셰이더에 넘기는 역할

	// 셰이더 쪽에 "어느 상수 버퍼가 어느 역할을 할 것"인지 이미 정의가 되어있으므로
	// 그렇게 정해둔 슬롯에 맞게 각 버퍼들을 입력한다

	srt_box->Render();

	worldBuffer->Set(*star->GetWorld());
	worldBuffer->SetVS(0);
	star->Render();

	worldBuffer->Set(*satelite->GetWorld());
	worldBuffer->SetVS(0);
	satelite->Render();
	
}
