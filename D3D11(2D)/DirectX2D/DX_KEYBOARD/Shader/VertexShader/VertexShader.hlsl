cbuffer world : register(b0)
{
    matrix world;
}
cbuffer view : register(b1)
{
    matrix view;
}
cbuffer projection : register(b2)
{
    matrix projection;
}
// �� 3���� constbuffer�� WVP ��ȯ�� ���� �Է¹޾ƾ� �ϴ� ����
// world ��� -> b0, view ��� -> b1, projection ��� -> b2 ������ ���� �Է� ����
// ���� ������Ʈ���� �����͸� ���� ������ ����ϸ� ���̴����� �˾Ƽ� ó��

struct VertexInput
{
    float4 pos : POSITION;
    float4 color : COLOR;
};

struct PixelInput
{
    float4 position : SV_Position;
    float4 color : COLOR;
};


PixelInput VS(VertexInput input)
{
    PixelInput output;

    // �Էµ� �����͸� �̿��� WVP ��ȯ ����
    output.position = mul(input.pos, world);    // mul : hlsl���� �����ϴ� ��� ���� �Լ� : ���� x ��� ���� �Լ�
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    // output.position = projection x view x world x input.pos
    output.color = input.color;
	
    return output;
}
