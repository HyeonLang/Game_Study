#pragma once
struct Vertex
// 앞으로 우리가 도형을 만들 때 쓸 정점의 정보는 이 구조체를 통해서 관리함
{
	Float3 position;
	Float4 colour;

	Vertex()
		// C++에서 구조체는 사실상 public만 존재하는 클래스와 다를 게 없으므로
		// 이렇게 생성자를 만드는 것도 문제 없음

		// 정점을 아무 입력 없이 디폴트로 선언했을 떄의 초기화값
	{
		position = Float3(0, 0, 0);
		colour = Float4(0, 0, 0, 1);
		// 4번째 값은 알파값 - 지금은 사용할 일이 없어 1로 놔둔다는 것만 기억할 것
	}
	Vertex(float x, float y, float r, float g, float b)
	{
		position = Float3(x, y, 0);
		colour = Float4(r, g, b, 1);
	}
};

struct VertexPos
{
	Float3 position;

	VertexPos() : position(0, 0, 0) {};
	VertexPos(float x, float y) { position = Float3(x, y, 0); }
}; 

float ratio_pos_x(int pos_x);
float ratio_pos_y(int pos_y);
// 이 두 함수는
// 윈도우 창의 절대좌표를 상대좌표로 변환하는 함수
