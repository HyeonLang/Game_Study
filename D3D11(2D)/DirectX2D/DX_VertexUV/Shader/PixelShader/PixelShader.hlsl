cbuffer Color : register(b0)
{
    float4 color;
}
// 메인 프로젝트 쪽에서 입력 버퍼 슬롯 설정

struct PixelInput
{
    float4 position : SV_Position;
    float4 color : COLOR;
};


float4 PS(PixelInput input) : SV_TARGET
{
    return input.color * color;
    // input.color만 이용하는 것이 아닌 입력받은 색 버퍼값 까지 고려하여 색상 출력
}
