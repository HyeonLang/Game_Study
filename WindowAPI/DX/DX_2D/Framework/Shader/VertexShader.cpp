#include "pch.h"
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
    // ��Ȯ���� ������ ������ ������ ������ ����� ���ÿ�,
    // ���̴��� �� ���� �ѱ� �� ������ ������ ������ ����ϴ� ���̵������ ���� ����ϴ� �κ�
    // ���̴��� C++ó�� �ڷ����� �˾Ƽ� �Ǵ����� ���ϱ� ������ ���� �ڷ��� �� ��ü�� �˷��� �ʿ䰡 ����

    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION",                    // �ø�ƽ �Է� ����
        0, 
        DXGI_FORMAT_R32G32B32_FLOAT,    // �ø�ƽ�� �� �ڷ��� ��� : R32G32B32 = 4byte �� 3���� FLOAT �Ҵ�
        // DXGI_FORMAT : ��� ��� ������ �����Ͱ� ������ �� �ƴϰ� ������ �̹� ������ ���ĵ鸸 ��� ����
        // �׷��� �� ��� ������ �͵��� �ϳ��� �������� ��Ƶ״ٴ� �ǹ�(�� �������� �̸��� DXGI_FORMAT)
        0, 
        0,                              // ��ü ������(����Ʈ) �� �������� ������ ���
        D3D11_INPUT_PER_VERTEX_DATA, 0},
        // �ø�ƽ "POSITION"�� �ش��ϴ� �����ʹ� ���� ���� �������� �ý��ۿ� �˸��� ����

        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
        // �ø�ƽ "COLOR"�� �ش��ϴ� �����ʹ� ���� ���� �������� �ý��ۿ� �˸��� ����

        // �� �κ��� ���̴��� �����͸� �ѱ� �� "�̷��� �����Ǿ� �ִ� �����͸� �ѱ� �����Դϴ�"��� �˸��ٴ� �ǹ�
        // Shader���� ������ �ø�ƽ�� �ش��ϴ� �����Ͱ� ������ ������������ �� �ڵ带 ���� ���

        // ������ �Էµ� �������� �� ������ ���� ������ �Էµ�.
        // �� ������ ���̴����� �Է��� �䱸�ϴ� ������ ��Ȯ�� ������ ���� ��� ���� CreateInputLayout�� �ƿ� �۵����� ����
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
