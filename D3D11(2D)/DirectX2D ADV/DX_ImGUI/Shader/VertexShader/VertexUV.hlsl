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


struct VertexInput
{
    float4 pos : POSITION;
    float4 uv : UV; // �� ��°�� ����ϴ� ��ǥ
    // ������ ��ġ�� �ƴ� ������Ʈ ��ü�� ǥ���� �� �� �� �ȿ� �κ� ��ǥ�� ���, ���� ������ ���� u v��� ���ڸ� �̿�
};

struct PixelInput
{
    float4 position : SV_Position;
    float4 uv : UV;
};


PixelInput VS(VertexInput input)
{
    PixelInput output;

    // �Էµ� �����͸� �̿��� WVP ��ȯ ����
    output.position = mul(input.pos, world); // mul : hlsl���� �����ϴ� ��� ���� �Լ� : ���� x ��� ���� �Լ�
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    // output.position = projection x view x world x input.pos
    output.uv = input.uv;
	
    return output;
}
