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
// 위 3개의 constbuffer는 WVP 변환을 위해 입력받아야 하는 버퍼
// world 행렬 -> b0, view 행렬 -> b1, projection 행렬 -> b2 슬롯을 통해 입력 받음
// 메인 프로젝트에서 데이터를 보낸 슬롯을 명시하면 셰이더에서 알아서 처리

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

    // 입력된 데이터를 이용해 WVP 변환 수행
    output.position = mul(input.pos, world);    // mul : hlsl에서 지원하는 행렬 곱셈 함수 : 벡터 x 행렬 곱셈 함수
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    // output.position = projection x view x world x input.pos
    output.color = input.color;
	
    return output;
}
