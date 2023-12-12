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
};

struct PixelInput
{
    float4 position : SV_Position;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;

    // 입력된 데이터를 이용해 WVP 변환 수행
    output.position = mul(input.pos, world); // mul : hlsl에서 지원하는 행렬 곱셈 함수 : 벡터 x 행렬 곱셈 함수
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
	
    return output;
}
