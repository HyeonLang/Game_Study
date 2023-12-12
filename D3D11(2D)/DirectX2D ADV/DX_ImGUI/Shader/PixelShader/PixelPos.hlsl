cbuffer Color : register(b0)
{
    float4 color;
}
// 메인 프로젝트 쪽에서 입력 버퍼 슬롯 설정

struct PixelInput
{
    float4 position : SV_Position;
};

float4 PS(PixelInput input) : SV_TARGET
{
    return color;
}
