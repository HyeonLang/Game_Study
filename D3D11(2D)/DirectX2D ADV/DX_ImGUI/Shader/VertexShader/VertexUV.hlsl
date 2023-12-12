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
    float4 uv : UV; // 두 번째로 사용하는 좌표
    // 정점의 위치가 아닌 오브젝트 전체를 표시할 때 그 중 안에 부분 좌표를 기록, 아직 쓰이지 않은 u v라는 문자를 이용
};

struct PixelInput
{
    float4 position : SV_Position;
    float4 uv : UV;
};


PixelInput VS(VertexInput input)
{
    PixelInput output;

    // 입력된 데이터를 이용해 WVP 변환 수행
    output.position = mul(input.pos, world); // mul : hlsl에서 지원하는 행렬 곱셈 함수 : 벡터 x 행렬 곱셈 함수
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    // output.position = projection x view x world x input.pos
    output.uv = input.uv;
	
    return output;
}
