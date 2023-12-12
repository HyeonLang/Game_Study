#include "pch.h"
#include "Hexagons.h"

Hexagons::Hexagons(float x, float y, float size, D3D11_PRIMITIVE_TOPOLOGY t)
	: Shape(x, y)
{
	type = t;
	
	// 정수 좌표->상대 좌표로 변환하는 함수, 실제 정수 좌표에서 상대 좌표로 전환

	// 정점을 통해 화면에 그릴 때 사용하는 좌표는 화면 내 비율을 기준으로 계산 : 뷰포트를 통한 상대 좌표를 이용하여 결정

	float screen_ratio = (float)WIN_HEIGHT / (float)WIN_WIDTH;

	// 이번에는 이 생성자 안에서 정점을 직접 생성시킬 예정
	// 따라서 이 안에서 벡터에 직접 정점들을 입력

	float angle = 2 * M_PI;

	for (int i = 0; i < 6; i++) 
	{
		verticies.emplace_back(Vertex(pos_x, pos_y, 0.4f, 0.4f, 1.0f));	// 정점 1
		verticies.emplace_back(Vertex(pos_x - cos(angle) * size * screen_ratio, pos_y - sin(angle) * size, 0.4f, 0.4f, 1.0f));	// 정점 2
		// 중앙의 정점에서 삼각비를 통해 왼쪽으로 얼마나 갔는지, 위/아래로 얼마나 갔는지 계산해서 정점을 추가하는 것
		// 처음에 2pi를 대입해서 이를 계산하면
		// 위 식은 처음엔 (pos_x - 1 * size * screen_ratio, pos_y - 0 * size)

		angle -= 2 * M_PI / 6.0f;
		// 지금 우리가 만드는 건 육각형
		// 따라서 각도를 계산해서 정점을 만들 때 한바퀴를 다 두르는 데 필요한 연산 수는 6번

		verticies.emplace_back(pos_x - cos(angle) * size * screen_ratio, pos_y - sin(angle) * size, 0.4f, 0.4f, 1.0f);	// 정점 3
		// 이번에는 angle이 2pi가 아니므로 삼각비가 정석적으로 계산됐을 것
	
	}

	

	

	//// 육각형 정점 정의 리스트 : 삼각형 6개 정의 리스트
	//vector<Vertex> vx_hexagon_list =
	//{
	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.4f, +0.4f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.4f, +0.6f, 0.4f, 0.4f, 1.0f),
	//	// 정점 생성시 반드시 시계방향으로 생성

	//	// 도형 정점 팁 : 도형의 중심 좌표를 중심을 기준으로 한다.

	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.4f, +0.6f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.5f, +0.7f, 0.4f, 0.4f, 1.0f),

	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.5f, +0.7f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.6f, +0.6f, 0.4f, 0.4f, 1.0f),

	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.6f, +0.6f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.6f, +0.4f, 0.4f, 0.4f, 1.0f),

	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.6f, +0.4f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.5f, +0.3f, 0.4f, 0.4f, 1.0f),

	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.5f, +0.3f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.4f, +0.4f, 0.4f, 0.4f, 1.0f),

	//};


	// vector를 복사
	//verticies.resize(v.size());	// 현재 verticies는 데이터를 저장할 빈 공간조차 할당되지 않은 상태, 복사할 벡터와 같은 길이로 할당.
	//copy(v.begin(), v.end(), verticies.begin());
	// copy라는 함수를 이용해서 벡터를 v에서 verticie로 복사
	// 복사하는 범위는 v의 처음부터 끝까지고, 복사를 시작할 위치는 verticies의 시작점

	// 폴리곤을 기반으로 DX에서 다룰 객체가 사용할 버퍼를 설정 : 기존의 InitDevice() 중 정점을 정의한 뒤 이를 세팅하는 부분 복사
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * verticies.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = verticies.data();
	// DirectX에서 이런 꼭지점들을 사용하려면 이것들을 셰이더에 호환되는 구조의 버퍼에 저장해서
	// 그 버퍼의 내용을 셰이더로 옮기는 과정을 거쳐야 한다.

	Device::Get()->GetDevice()->CreateBuffer(&bd, &initData, &VB);    // 최종적으로 여기서 그림을 그릴 내용을 저장해둘 버퍼가 등록
}

Hexagons::~Hexagons()
{
}
