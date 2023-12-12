#include "pch.h"

TutorialScene::TutorialScene()
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	// 셰이더 생성에 필요한 플래그를 미리 설정

	VS = new VertexShader(L"Shader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/VertexShader.hlsl", flags);
	// 정점 셰이더와 픽셀 셰이더를 셰이더 주소가 있는 파일에 생성

	// 이제 도형을 그리는 데 사용할 정점 생성
	vector<Vertex> vx_triangle_list =
	{
		Vertex(-0.1f, +0.1f, 0.8f, 0.8f, 0.17f),
		Vertex(-0.8f, +0.1f, 0.8f, 0.8f, 0.17f),
		Vertex(-0.8f, +0.8f, 0.8f, 0.8f, 0.17f),
	};

	list_triangle = new Triangle(vx_triangle_list,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vector<Vertex> vx_rect_list =
	{
		Vertex(-0.8f, -0.1f, 0.8f, 0.1f, 0.6f),
		Vertex(-0.1f, -0.1f, 0.8f, 0.1f, 0.6f),
		Vertex(-0.8f, -0.8f, 0.8f, 0.1f, 0.6f),
		Vertex(-0.8f, -0.8f, 0.8f, 0.1f, 0.6f),
		Vertex(-0.1f, -0.1f, 0.8f, 0.1f, 0.6f),
		Vertex(-0.1f, -0.8f, 0.8f, 0.1f, 0.6f),
	};

	list_rect = new Triangle(vx_rect_list,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	list_hexagon[0] = new Hexagon(960, 540,
		0.3f, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	list_hexagon[1] = new Hexagon(560, 540,
		0.3f, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	line_hexagon = new Hexagon(960, 180,
		0.4f, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	// 이렇게 한 가지 도형을 그리는 클래스를 만들어서
	// 그 도형에 여러 모드를 설정해두고 필요할 때마다 골라서 쓰는 것으로도
	// 우리가 원하는 도형을 정점을 직접 입력해줄 필요 없이
	// 좌표와 크기만 입력하는 것으로
	// 알아서 그 도형의 정점들을 구성해 완성된 도형으로 출력하도록 만들 수 있다

	// 이런 식으로 오브젝트를 만드는 것이
	// 앞으로 우리가 만들 프로그램들의 기본적인 조형 방법

	// 
}

TutorialScene::~TutorialScene()
{
	delete(list_triangle);
	delete list_rect;
	for (int i = 0; i < 10; i++)
	{
		if(list_hexagon[i] != NULL)
			delete list_hexagon[i];
	}
	delete line_hexagon;
	VS->Release();
	PS->Release();
}

void TutorialScene::Update()
// 메인 프로그램의 매 루프마다 씬의 현재 상황을 업데이트하는 함수
// 시간 경과 등에 따라 씬의 내용이 변해야 한다면 이 함수를 통해 변동사항을 관리

// ...하지만 오늘은 이 함수를 사용할 일이 없으니 빈 함수로 놔둠
{


}

void TutorialScene::Render()
// 실제 출력을 담당하는 부분
// 이 씬이 사용중일 떄, 메인 루프가 돌아갈 때마다 이 함수를 통해 화면에 출력
{
	Device::Get()->Clear();
	// 화면을 초기화시키는 함수를 Device에서 불러 사용

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	

	Device::Get()->GetDeviceContext()->VSSetShader(VS->GetVertexShader(), nullptr, 0);
	Device::Get()->GetDeviceContext()->PSSetShader(PS->GetPixelShader(), nullptr, 0);
	// 디바이스에 정점 셰이더와 픽셀 셰이더를 설정

	Device::Get()->GetDeviceContext()->IASetInputLayout(VS->GetInputLayout());
	// VS 내부의 input_layout을 가져와 device_context에 세팅

	// 여기까지는 그리기 전에 Scene을 그릴 환경을 세팅하는 부분
	// 여기부터는 본격적으로 도형을 그리는 부분

	Device::Get()->GetDeviceContext()->IASetVertexBuffers
	(0, 1, list_triangle->GetBuffer(), &stride, &offset);
	// 삼각형이 보유하고 있는 정점이 저장된 버퍼를 디바이스에 세팅
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(list_triangle->GetType());
	// 삼각형이 보유하고 있는 도형을 그릴 방식을 디바이스에 세팅

	Device::Get()->GetDeviceContext()->Draw(list_triangle->GetVertexSize(), 0);
	// 세팅을 다 끝냈으면 삼각형이 보유하고 있는 정점의 개수만큼 도형을 그리라고 요청
	
	// 다른 도형을 그리고 싶다면 위 3줄의 코드를 변수 이름만 바꿔서 재탕 
	Device::Get()->GetDeviceContext()->IASetVertexBuffers
	(0, 1, list_rect->GetBuffer(), &stride, &offset);
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(list_rect->GetType());

	Device::Get()->GetDeviceContext()->Draw(list_rect->GetVertexSize(), 0);



	for (int i = 0; i < 10; i++)
	{
		if (list_hexagon[i] == NULL)
			break;
		Device::Get()->GetDeviceContext()->IASetVertexBuffers
		(0, 1, list_hexagon[i]->GetBuffer(), &stride, &offset);
		Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(list_hexagon[i]->GetType());

		Device::Get()->GetDeviceContext()->Draw(list_hexagon[i]->GetVertexSize(), 0);
	}
	Device::Get()->GetDeviceContext()->IASetVertexBuffers
	(0, 1, line_hexagon->GetBuffer(), &stride, &offset);
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(line_hexagon->GetType());

	Device::Get()->GetDeviceContext()->Draw(line_hexagon->GetVertexSize(), 0);

	// 여기까지가 Scene에서 도형을 그릴 부분

/*
과제 :

도형을 담당하는 클래스를 하나 더 만들어서
같은 Scene에다가 그려볼 것
Hexagon 클래스를 만들었던 것과 같은 요령으로 클래스를 만들어볼 것

기존에 그렸던 도형들은 전부 제거해도 무방

조건 1 : 그릴 도형이 무엇인지는 지난주와 마찬가지로 불문
조건 2 : 독립된 클래스로서 만들어볼 것
조건 3 : 도형을 "처음 만들 때부터 어느 정도 회전된 상태로 만들 것"
그리고 그 회전은 같은 클래스의 객체끼리도 달라야 함
<- 검증을 위해 해당 클래스로 객체를 최소 3개 이상 만들고
각각이 전부 회전된 정도가 달라야 한다



*/
}
