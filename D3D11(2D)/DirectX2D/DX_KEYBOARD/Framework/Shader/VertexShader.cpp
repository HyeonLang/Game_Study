#include "pch.h"
// �̸� �����ϵ� ����� �ش� ����� �̸� ����ص״ٸ�
// ���� �ڵ� ������ �ڵ� �������� �� �˾Ƽ� �̸� �����ϵ� ����� ���Ե�

VertexShader::VertexShader(LPCWSTR file_loc, DWORD flags)
{
    ID3DBlob* vertexBlob;

    D3DCompileFromFile(file_loc, nullptr, nullptr, "VS",
        "vs_5_0", flags, 0, &vertexBlob, nullptr);
    // ������ ���� �ּҸ� �Է��ߴ� �Ͱ��� �޸�,
    // ������ �Ű������� ���� ���̴� ������ ��ġ�� ���� �Է¹޴´�

    Device::Get()->GetDevice()->CreateVertexShader(vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), nullptr, &VS);
    // �������� ������ ���� ������ ����ƴ� ���� ����ߴ� �ڵ带
    // �̹� �����ӿ�ũ�� �ɸ´� ���·� ��ȯ
    // ������ device�� ���� singleton ��ü�� ���ؼ� �����ؾ� �ϴ� �׿� �°� �����ְ�,
    // VertexShader ��ü�� ������ �� Ŭ������ ��� ������ VS�� �̿��ϰ� �����Ƿ� �׿� �°� ����

    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION", // ���̴��� �����Ͱ� �Էµ� ��, ���� �ٷ�� �κ��� �����ʹ�
        // �� �̸��� ���� �ø�ƽ�� �� ���̴�
        0, // �ø�ƽ �ε��� - ������ �� ���� ������ ���� ����� ���� ������ �� ����
        // �� �������� 0���� ����
        DXGI_FORMAT_R32G32B32_FLOAT, 
        // "�� �ø�ƽ�� �� ������ �ڷᰡ �� ����"�̶�� �˷��ִ� �κ�,
        // �̰� ���� �����Ϳ� ��ġ���� ������ ���������� �۵����� ����
        // �̰� ������ ������ ���� ��찡 ������ �����Ƿ� �Ű�Ἥ ��ġ������� ��

        // �� ������ ����
        // R, G, B �� 3������ �ڷḦ ����Ѵٴ� �ǹ�
        // + �� 3���� �ڷ�� ���� 32��Ʈ / 32��Ʈ / 32��Ʈ��ŭ�� �����͸� �����
        // �׸��� �� �����͵��� �Ǽ�(float)��

        // �����ϴ� �������� ���Ŀ� �ѵ��� ������,
        // �� ������ ���Ǹ� ã�ư��� �������� ������ ���� Ȯ���غ� ��
        0, // ��� "����"�� �������� �����ϴ� �κ�
        // �� ���Կ� ���� ������ ���� ���� �ٷ�� ���� �� ����, ���� ������ ������� �ʴ� ����
        0, // ��ü ������(����Ʈ) �� ��𿡼����� �� �����Ͱ� ���۵Ǵ��� �� �ε����� ���
        // �ε����� ����ϴ� ���̴� 0���� ����
        D3D11_INPUT_PER_VERTEX_DATA, 0} // 2D�� �����ϴ� ���ȿ� �ٷ� �� ���� �������̹Ƿ� �н�

        // ���� ���̴��� �ø�ƽ "POSITION"���� �̷� ������ �����Ͱ� ���ٰ�
        // �ý��ۿ� �˸��� �κ�

        ,{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
        // �ø�ƽ "COLOR"�� �� �������� ����
        // 12�� ���, ���ʿ��� ����Ǿ��� ù���� �������� ������
        // R32G32B32 = �� 12����Ʈ�̹Ƿ�
        // �� 12����Ʈ�� ������ �� �� 13��° ����Ʈ(=�ε��� 12)���� �� ������ �����͸� ����Ų��
        // ��� �˷��ִ� ����

        // �̷��� ���ǵ� �����͵���
        // ���� ���̴��� �Էµȴٴ� ���� �ý��ۿ� �˸��� ���� layouts�� ����
    };

    UINT layoutSize = ARRAYSIZE(layouts);
    // �׷��� �԰��� ������ layouts�� �� �뷮�� ���
    // �ٷ� ���� CreateInputLayout �Լ����� layouts�� �� �뷮�� ���� ������� ���ϱ� ������,
    // �츮�� �̸� ����ؼ� �˷��� �ʿ䰡 �ֱ� ����

    Device::Get()->GetDevice()->CreateInputLayout(layouts, layoutSize, vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), &input_layout);
    vertexBlob->Release();
}

VertexShader::~VertexShader()
{
    Release();
}

void VertexShader::Set()
{
    DVC->IASetInputLayout(input_layout);
    DVC->VSSetShader(VS, nullptr, 0);
}

void VertexShader::Release()
{
    VS->Release();
    input_layout->Release();
}
