#pragma once
class VertexBuffer
{
private:
	ID3D11Buffer* buffer;

	UINT stride;	// 이 클래스에서 저장하고 있는 버퍼가 한칸마다 사용하는 용량을 저장
	// DX시스템에서는 버퍼 데이터 단위 하나당 자료량을 모른다. 용량 자체를 관리, 입력 필요

	UINT offset;	// 오프셋 = 사용중인 데이터의 인덱스를 명시
	
public:
	VertexBuffer(void* data, UINT s, UINT count);
	~VertexBuffer();

	void Set(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// 도형을 출력하는 방식을 이제 이 쪽에서 관리
};


