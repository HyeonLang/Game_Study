cbuffer Color : register(b0)
{
    float4 color;
}
// ���� ������Ʈ �ʿ��� �Է� ���� ���� ����

struct PixelInput
{
    float4 position : SV_Position;
    float4 uv : UV;
};

SamplerState samp : register(s0);
Texture2D map : register(t0);
// samp = �����Ϳ��� Ư���� ������ ������ �ӽ÷� �����ϴ� ����
// map = samp�� ����� �� �ȼ����� ���α׷����� ����� ��ġ�� �°� �����ϴ� ����
// �׷��� ���� ����
float4 PS(PixelInput input) : SV_TARGET
{
    return map.Sample(samp, input.uv) * color;
    // map.Sample�Լ��� �̹��� ���Ͽ��� samp�� ����� �����͸� uv���� �ش��ϴ� ��ǥ�� �����ϰ�,
    // ���� �ȼ����̴��� �������� �����Ѵٸ� �̸� �ݿ�
}
