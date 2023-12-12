#include "pch.h"

ConstBuffer::ConstBuffer(void* data, UINT data_szie)
	: data(data), data_size(data_size)
{
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = data_szie;	// 데이터의 총 용량 크기 자체를 입력
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;	

	DEVICE->CreateBuffer(&bd, &initData, &buffer); 
}

ConstBuffer::~ConstBuffer()
{
}

void ConstBuffer::SetVS(UINT slot)
{
	DVC->UpdateSubresource(buffer, 0, NULL, data, 0, 0);
	DVC->VSSetConstantBuffers(slot, 1, &buffer);
}
void ConstBuffer::SetPS(UINT slot)
{
	DVC->UpdateSubresource(buffer, 0, NULL, data, 0, 0);
	DVC->PSSetConstantBuffers(slot, 1, &buffer);
}
// 각각 정점 / 픽셀 셰이더에 정의된 각 슬롯에 
// 버퍼 데이터를 입력하는 함수

// 슬롯의 의미는 VertexShader.hlsl 에서 다룬다.