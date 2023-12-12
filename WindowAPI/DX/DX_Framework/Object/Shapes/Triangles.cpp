#include "framework.h"
#include "Triangles.h"

Triangles::Triangles(vector<Vertex> v, D3D11_PRIMITIVE_TOPOLOGY t) : Shape(0.0f, 0.0f)
{
	type = t;

	// vector를 복사
	verticies.resize(v.size());	// 현재 verticies는 데이터를 저장할 빈 공간조차 할당되지 않은 상태, 복사할 벡터와 같은 길이로 할당.
	copy(v.begin(), v.end(), verticies.begin());
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

Triangles::~Triangles()
{
}
