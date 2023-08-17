
struct VertexInput
{
	float4 position : POSITIONT0;
	float4 color : COLOR0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float4 color : COLOR0;
};


cbuffer CameraBuffer : register(b0)
{
	matrix view;
	matrix projection;
}

cbuffer TransformBuffer : register(b1)
{
	matrix world;
}

cbuffer ColorBuffer : register(b2)
{
	float4 color;
}


PixelInput VS(VertexInput input) // VS 단계 : IA에서 받은 정점을 가공해주는 단계
{
	PixelInput output;
	
	// 받은 포지션에 SV_ 접두사를 붙여 다음 단계로 넘겨준다 -> RS 단계에서 사용할 정점의 좌표를 지정해줌
	// 행렬의 곱을 통해 특정 공간으로 변환시켜준다.
	// 월드 -> 뷰 -> 프로젝션 순서로 해주어야 한다.
	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	
	output.color = input.color;
	
	return output; // 반환된 값은 RS단계를 거친다.
}
 
float4 PS(PixelInput input) : SV_Target // 현재 세팅된 메인 렌더 타겟을 사용하라
{
	return input.color;
}