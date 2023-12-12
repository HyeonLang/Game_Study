#include "framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(LPCWSTR file_loc, DWORD flags)
{
    // ���� ������ InitDevice() ������ ���� �� ����
    
    //hlsl ������ �ε��Ͽ� ���̴��� DirectX ��ü�� ��ġ�ϴ� ����
    ID3DBlob* vertexBlob;
    //1. ������ �ҷ��ö� ���� �Է��� �ƴ� �Ű������� �Է�
    D3DCompileFromFile(file_loc, nullptr, nullptr, "VS",
        "vs_5_0", flags, 0, &vertexBlob, nullptr);

    // ��ġ���� 2
    // 2. Device �̱��� ��ü�� �ҷ����� ������� ����
    Device::Get()->GetDevice()->CreateVertexShader(vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), nullptr, &VS);

    // �׷��� ��ġ�� ���̴��� ���� �׸��� �׸� ��ǥ�� �����Ǹ� �� ���� ������ ������ ������ �����.
    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layoutSize = ARRAYSIZE(layouts);   // ����� �ѷ��� ���⼭ ���

    // ���� ������ ���� ������ �⸮�� ���� �ʿ��� �����͸� �����ص� ������ ����, �̸� DirectX ��ü�� ���
    // ��ϰ������� ��� ����ߴ� blob�� �Ҵ� ����
    Device::Get()->GetDevice()->CreateInputLayout(layouts, layoutSize, vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), &inputLayout);
    vertexBlob->Release();
}

VertexShader::~VertexShader()
{
    Release();
}

void VertexShader::Release()
{
    VS->Release();
    inputLayout->Release();
}
