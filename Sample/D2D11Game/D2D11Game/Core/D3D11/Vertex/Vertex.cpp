/*
	������ : �ֻ��� ������������ ��ǥ���������� ����Ű�� �������ΰ��
	����� : ������ġ�� ��� �� ������ ���� ��ǥ������ ����Ű�� ���
		-> �߰� ���� ���͸��� ��� ����� ������ġ�� �߰������� ������ �� �ִ�.
*/

#include"stdafx.h" // ��Ʈ ���͸��� �߰� ���� ���͸��� �߰��Ͽ� ��θ� �����
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