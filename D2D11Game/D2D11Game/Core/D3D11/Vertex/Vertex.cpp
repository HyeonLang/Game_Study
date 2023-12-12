/*
	절대경로 : 최상위 시작지점부터 목표지점까지를 가리키는 절대적인경로
	상대경로 : 기준위치를 잡아 그 기준을 상대로 목표지점을 가리키는 경로
		-> 추가 포함 디렉터리에 상대 경로의 기준위치를 추가적으로 포함할 수 있다.
*/

#include"stdafx.h" // 루트 디렉터리를 추가 포함 디렉터리에 추가하여 경로를 잡아줌
#include"Vertex.h"

D3D11_INPUT_ELEMENT_DESC D3D11_VertexColor::descs[] =
{
	{"POSITIONT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

D3D11_INPUT_ELEMENT_DESC D3D11_VertexTexture::descs[] =
{
	{"POSITIONT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
};