cbuffer Color : register(b0)
{
    float4 color;
}
// 메인 프로젝트 쪽에서 입력 버퍼 슬롯 설정

struct PixelInput
{
    float4 position : SV_Position;
    float4 uv : UV;
};

SamplerState samp : register(s0);
Texture2D map : register(t0);
// samp = 데이터에서 특성한 한점의 정보를 임시로 저장하는 버퍼
// map = samp에 저장된 각 픽셀값을 프로그렘에서 출력할 위치에 맞게 저장하는 버퍼
// 그래픽 결정 버퍼
float4 PS(PixelInput input) : SV_TARGET
{
    return map.Sample(samp, input.uv) * color;
    // map.Sample함수로 이미지 파일에서 samp에 저장된 데이터를 uv값에 해당하는 좌표에 저장하고,
    // 만약 픽셀셰이더에 색상보정이 존재한다면 이를 반영
}
