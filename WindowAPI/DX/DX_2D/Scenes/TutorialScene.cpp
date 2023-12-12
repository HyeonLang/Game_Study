#include "pch.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;	// 셰이더를 생성하기 위해 필요한 플래그를 미리 설정
	
	// 정점 셰이더와 픽셀 셰이더를 셰이더 주소가 있는 파일에 생성
	VS = new VertexShader(L"Shader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/VertexShader.hlsl", flags);

	// 도형을 그리는 데 사용할 정점 생성
	vector<Vertex> vx_triangle_list =
	{
		Vertex(-0.1f, +0.1f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.8f, +0.1f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.8f, +0.8f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.8f, +0.8f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.1f, +0.8f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.1f, +0.1f, 0.4f, 0.4f, 1.0f)

	};

	// 정의된 정점을 토대로 도형을 생성
	list_rect = new Triangles(vx_triangle_list, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	/*
		도형을 관장하는 클래스를 만들고 (Shape에 상속시키는 형태)
		이걸 TutorialScene에 객체로 추가하여 출력해보기

		기존에 만들었던걸 객체처럼 만들어서 
		Render() 내부에서 출력하도록 만들어보기

		추가목표 : 정 다면체 제작, 원 제작
	*/
	// 육각형 정점 정의 리스트 : 삼각형 6개 정의 리스트
	vector<Vertex> vx_hexagon_list =
	{
		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.4f, +0.4f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.4f, +0.6f, 0.4f, 0.4f, 1.0f),
		// 정점 생성시 반드시 시계방향으로 생성

		// 도형 정점 팁 : 도형의 중심 좌표를 중심을 기준으로 한다.

		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.4f, +0.6f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.5f, +0.7f, 0.4f, 0.4f, 1.0f),

		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.5f, +0.7f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.6f, +0.6f, 0.4f, 0.4f, 1.0f),

		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.6f, +0.6f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.6f, +0.4f, 0.4f, 0.4f, 1.0f),

		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.6f, +0.4f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.5f, +0.3f, 0.4f, 0.4f, 1.0f),

		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.5f, +0.3f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.4f, +0.4f, 0.4f, 0.4f, 1.0f),
		
	};

	// 중심과 반지름을 토대로 도형을 생성
	hexagon = new Hexagons(calc_ratio_pos_x(960, 0), calc_ratio_pos_x(540, 0), 0.2f, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	/*
		1. 도형의 중심점과 크기만 제공하며 정점까지 구성되는 도형 클래스 출력하기
			: 원, 육각형
		
		1.5. TRIANGEL_STRIP을 이용하여 1번을 할 예정
			: STRIP = 정점들을 이어서 계속 삼각형을 만듦
		
		2. 만든 도형에 색을 입히기 위해 Pixel Shader 변형 실습 예정
	*/

	/*
		과제 : TRIANGEL_STRIP을 통해 도형을 그리기

		STRIP : 이미 사용했던 정점을 재이용해서, 도형을 그리는데 필요한 정점의 개수를 더 적게 쓰고 그리는 방식
		다만 정점을 사용하는 방식이 사각형 기준 다음과 같음

		아래는 사각형이 있다 가정했을 때, 각 정점에 번호를 붙인 것
		1 2
		3 4

		TRIANGLE_LINE 기준으로는
		(1 2 4) (4 3 1)
		(1 2 3) (2 4 3)
		순으로 입력해서 이용했지만

		STRIP 기준으로는
		(1 2 3 4)로만 입력해도 출력이 됨
		(1 2 4 3)으로 입력하면 아마 안 될 것

		어떤 구조로 이뤄지길래 이렇게 입력해도 출력이 되는지 조사하면서,
		이 STRIP을 이용해 원을 그려와볼 것

		추가)원의 경우, 지금 육각형을 만들었던 방식에서 6이 아니라
		원을 그리기 충분한 만큼 나누는 식으로 하면 쉽게 그릴 수 있음
		적게 잡아도 20~30 정도?

		추가2)색은 27일 강의까지의 내용으로는 불가능.
		추석기간 중 추가 제공할 예정인 자료를 참고하면 가능하지만, 과제에서 이를 적용할 것을 요구하지는 않을 것이므로
		과제를 끝내고도 시간이 좀 남는다면 그 때 시도해볼 것을 권장
	*/
	// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP 을 이용한 삼각형 만들기
	// 
	// 각 정점의 번호를 매기면 다음 표와 같음
	// 정점 번호   x    y
	//    1      -0.8 -0.1
	//    2      -0.1 -0.1
	//    3      -0.8 -0.8
	//    4      -0.1 -0.8
	vector<Vertex> vx_strip_rect_list =
	{
		Vertex(-0.8f, -0.1f, 1.0f, 1.0f, 1.0f),
		Vertex(-0.1f, -0.1f, 0.0f, 0.0f, 1.0f),
		Vertex(-0.8f, -0.8f, 1.0f, 0.0f, 0.0f),
		Vertex(-0.1f, -0.8f, 1.0f, 1.0f, 0.0f),
		Vertex(-0.8f, -0.9f, 0.0f, 1.0f, 0.0f),
		Vertex(-0.0f, -0.85f, 0.4f, 0.4f, 1.0f)
		
	};
	strip_rect = new Triangles(vx_strip_rect_list, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	// TRIANGLESTRIP은 다음과 같이 동작한다
	// 첫(홀수)번째 삼각형 : k, k+1, k+2번째 정점을 이용해서 삼각형을 그림 
	// 두번(짝수)번째 삼각형 : k+2, k+1, k+3번째 정점을 이용해서 삼각형을 그림
	// 간단히 말하면 홀수번쨰 삼각형은 그냥 그리고
	// 짝수번째 삼각형은 홀수번째 삼각형의 마지막 두 정점을 순서를 반대로 바꿔서 이용

	// 장점 : 도형을 그리는 데 사용되는 정점의 개수가 LIST에 비해 훨씬 적음
	// LIST는 첫 삼각형 이후 새 삼각형을 그릴 때 매번 정점을 3개씩 추가해야 하지만
	// STRIP은 그냥 하나씩만 추가하면 됨

	// 단점 : 자유롭게 도형을 그리지는 못함
	// 기존에 사용된 정점을 재활용해서 그리다보니, 무조건 해당 정점들을 이용했을 때 시계방향이 되도록 설계해야만 함
	// 거기에 기존 삼각형의 한 변에서 계속 이어서 덧대그리는 구조다보니
	// 서로 독립된 도형을 그린다던가 하는 게 불가능하고 무조건 한 번에 최대 하나의 도형만 그릴 수 있게 되어있다.

	// 색에 대한 내용은 VertexShader.hlsl에서 다룸

}

TutorialScene::~TutorialScene()
{
	delete(list_rect);
	delete(strip_rect);
	delete(hexagon);
	VS->Release();
	PS->Release();
}

void TutorialScene::Update()
// 기존 API에서 루프문이 대신 매 루프마다 호출돼서 사용
{
}

void TutorialScene::Render()
{
	Device::Get()->Clear();			// 화면 초기화
	UINT stride = sizeof(Vertex);   // 버퍼에 저장할 정점의 구조에 따라 변동하는 정점 하나 데이터의 용량 저장 변수
	UINT offset = 0;                // offset 설정

	Device::Get()->GetDeviceContext()->VSSetShader(VS->GetVertexShader(), nullptr, 0);
	Device::Get()->GetDeviceContext()->PSSetShader(PS->GetPixelShader(), nullptr, 0);
	// 디바이스에 정점 셰이더와 픽셀 셰이더를 설정하는 과정

	Device::Get()->GetDeviceContext()->IASetInputLayout(VS->GetInputLayout());	
	// Device 내부에 정의된 DeviceContext를 가져와서 VertexShader에 정의된inputLayout 등록
	 


	// 여기서부턴 본 TutorialScene에서 선언된 도형 객체들을 통해 그리는 구간
	 
    // 1. 우리가 그린 도형은 삼각형 하나
	Device::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, list_rect->GetBuffer(), &stride, &offset);	// 삼각형이 가지고 있는 버퍼를 디바이스에 세팅
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(list_rect->GetType());	// 삼각형의 그림 타입을 디바이스에 세팅
	// 이제 이 장비를 통해 우리가 뭘 출력할 것인지를 지정

	Device::Get()->GetDeviceContext()->Draw(list_rect->GetVertexSize(), 0);	// 삼각형이 가진 정점의 개수를 여기서 체크하고, 그 정점의 개수만큼을 이용해 draw를 실행


	// 2. 우리가 그린 도형은 육각형 하나
	Device::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, hexagon->GetBuffer(), &stride, &offset);	// 삼각형이 가지고 있는 버퍼를 디바이스에 세팅
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(hexagon->GetType());	// 삼각형의 그림 타입을 디바이스에 세팅
	// 이제 이 장비를 통해 우리가 뭘 출력할 것인지를 지정

	Device::Get()->GetDeviceContext()->Draw(hexagon->GetVertexSize(), 0);	// 육각형이 가진 정점의 개수를 여기서 체크하고, 그 정점의 개수만큼을 이용해 draw를 실행

	// STRIP
	Device::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, strip_rect->GetBuffer(), &stride, &offset);	// 삼각형이 가지고 있는 버퍼를 디바이스에 세팅
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(strip_rect->GetType());	// 삼각형의 그림 타입을 디바이스에 세팅
	// 이제 이 장비를 통해 우리가 뭘 출력할 것인지를 지정

	Device::Get()->GetDeviceContext()->Draw(strip_rect->GetVertexSize(), 0);	// 삼각형이 가진 정점의 개수를 여기서 체크하고, 그 정점의 개수만큼을 이용해 draw를 실행


}
