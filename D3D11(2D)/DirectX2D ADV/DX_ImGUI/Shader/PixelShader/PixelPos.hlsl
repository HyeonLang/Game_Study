cbuffer Color : register(b0)
{
    float4 color;
}
// ���� ������Ʈ �ʿ��� �Է� ���� ���� ����

struct PixelInput
{
    float4 position : SV_Position;
};

float4 PS(PixelInput input) : SV_TARGET
{
    return color;
}