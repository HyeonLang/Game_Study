#include "pch.h"

Hexagon::Hexagon(int x, int y, float size, D3D11_PRIMITIVE_TOPOLOGY t)
	: Shape(x, y)
{
	type = t;

	// Hexagon에선 매개 변수로 정점이 저장된 vector를 받지 않음
	
	// 여기서 직접 선언할 예정이기 때문

	// vector<Vertex> verticies = {};
	// 이제부터는 각 오브젝트가 직접 그래픽 출력에 필요한 정점들을 관리하게 설계함
	// 따라서, 생성자에서 그 정점을 입력하는 방식을 취한다
	// 주의할 점은, 이미 Shape에서 verticies가 선언되고 초기화되어 있으므로
	// 굳이 생성자에서 이를 초기화할 이유는 없음

	// 정점은 현 시점에선 절대좌표가 아니라 화면 중앙을 기준으로 하는 상대좌표로 이용되는 중
	// 따라서 절대좌표를 사용하기 위해선 이를 적절히 변환할 필요가 있음
	
	float screen_ratio = float(WIN_HEIGHT) / float(WIN_WIDTH);
	// 추가로, 창의 가로와 세로는 같은 절대값에 대한 비율이 다르므로
	// 이를 보정해줄 값을 미리 계산할 필요가 있음

	float pos_x = ratio_pos_x(x);
	float pos_y = ratio_pos_y(y);
	// 생성자에서 사용된 매개변수는 int이므로 정상적으로 계산하는 데 이용할 수 없음
	// 따라서 float으로 변환하는 과정이 필요하고, 이를 생성자 내부에서 실행

	float angle = 2 * M_PI - 1.327f * M_PI / 6.0f;
	// M_PI = math.h에 포함되어 있는 상수로, 원주율 pi의 값을 저장해둔 값
	// 앞으로 삼각함수를 좀 사용할 예정인데, 삼각함수를 다루는 함수에서 사용하는 값이
	// Radian 값을 이용하기 때문에 이에 맞는 변수를 만들어둘 필요가 있다
	
	// angle = 2pi = 360도

	switch (type)
		// 삼각형 외에도 다른 출력방식도 다뤄볼 예정
	{
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		for (int i = 0; i < 6; i++)
		{
			verticies.emplace_back(pos_x, pos_y, 0.4f, 0.4f, 1.0f);
			verticies.emplace_back(
				pos_x - cos(angle) * size * screen_ratio,
				// 중앙점에서 삼각함수를 이용해 구한 (원 안에서의) 상대좌표를 더하거나 빼서
				// 육각형의 이번 꼭지점의 X좌표를 계산한다
				pos_y - sin(angle) * size,
				// 여기엔 화면비율을 곱하지 않는데,
				// 위에서 구한 화면의 비율은 가로가 더 넓으므로
				// 상대좌표계에선 같은 절대좌표 입력에 비해 실제 값의 변동이 더 작아야 함
				0.4f, 0.4f, 1.0f);

			angle -= 2 * M_PI / 6.0f;

			verticies.emplace_back(pos_x - cos(angle) * size * screen_ratio,
				pos_y - sin(angle) * size, 0.4f, 0.4f, 1.0f);
			// 각을 새로이 보정한 뒤에 다음 꼭지점의 위치 계산

		}
		break;

	case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
		for (int i = 0; i <= 6; i++)
		{
			verticies.emplace_back(pos_x - cos(angle) * size * screen_ratio,
				pos_y - sin(angle) * size, 0.4f, 0.4f, 1.0f);
			angle -= 2 * M_PI / 6.0f;
		}
		break;

	default:
		break;
	}

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * verticies.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = verticies.data();

	Device::Get()->GetDevice()->CreateBuffer(&bd, &initData, &VB);
	// 기본적으로 정점들이 입력되는 방식을 제외하면 다른(Triangle) 클래스와 내용이 다를 게 없으니
	// 그 다른 클래스에서 그대로 내용을 복사해 재활용

}

Hexagon::~Hexagon()
{
}
