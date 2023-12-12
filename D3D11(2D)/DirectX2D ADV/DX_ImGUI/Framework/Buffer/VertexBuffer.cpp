#include "pch.h"

VertexBuffer::VertexBuffer(void* data, UINT s, UINT count)
	: stride(s), offset(0)
{
	// 기존의 각 도형에서 버퍼를 만들어 등록하는 부분을 복사해서
	// 본 클래스에 맞게 살짝 고쳐 사용 - (1), (2), (3) 세 부분
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = s * count; // (1) stride : 버퍼의 한 칸이 차지하는 용량
	// 이를 입력받아서 사용하므로 특정 클래스의 크기를 구할 필요 없이 입력받은 값을 그대로 이용
	// count 역시 입력받은 데이터의 총 데이터량이 얼마나 되는지 모르니
	// 데이터에 입력되어 있는 자료의 개수 자체를 매개변수로 받아서 이를 이용
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data; // (2) 버퍼에 입력할 데이터가 저장된 주소를 여기에 입력

	DEVICE->CreateBuffer(&bd, &initData, &buffer); 
	// (3) 앞쪽의 미리 매크로를 선언해둔 긴 문구를 매크로로 짧게 줄이고
	// 변수명(버퍼명)이 달라졌으니 이에 맞게 수정해주기
}

VertexBuffer::~VertexBuffer()
{
	buffer->Release();
}

void VertexBuffer::Set(D3D11_PRIMITIVE_TOPOLOGY type)
// 지난 프로젝트에서 Scene에서 각 도형을 출력할 때
// DX 엔진에 출력할 각 도형의 버퍼, 그래픽을 출력하는 방식을 각각 등록한 뒤
// 정해진 개수만큼의 정점을 그리는 식이었는데
// 그 중 버퍼 등록과 출력 방식 입력을 이 함수에서 하는 것으로 대체
{
	DVC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	DVC->IASetPrimitiveTopology(type);
}

// 이렇게 만든 클래스를
// 기존의 Shape 클래스에서 사용하던 ID3D11Buffer를 대체하여 이용할 예정
// -> 기존 클래스에선 출력을 위해 Scene에서 선처리를 해줘야 하는 것이 있었지만,
// 이제는 그런 것 없이 온전히 도형 안에서 출력 관련 세팅을 전부 담당하게 될 것
