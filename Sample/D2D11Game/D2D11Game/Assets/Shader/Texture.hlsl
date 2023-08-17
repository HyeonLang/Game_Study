
struct VertexInput
{
	float4 position : POSITIONT0;
	float2 uv : TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float2 uv : TEXCOORD0;
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

PixelInput VS(VertexInput input) 
{
	PixelInput output;
	
	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	
	output.uv = input.uv;
	
	return output; 
}

Texture2D source_texture1 : register(t0); // 0 ~ 127
Texture2D source_texture2 : register(t1); 
SamplerState samp : register(s0); // 0 ~ 15

float4 PS(PixelInput input) : SV_Target 
{
	// Sampling : 임의의 데이터를 추출하는 것
	// Sample() : 텍스쳐에서 일정 부분의 데이터(색)을 추출해오는 함수
	float4 color = source_texture1.Sample(samp, input.uv);
	
	//float4 color;
	//if (input.uv.x < 1.0f)
	//	color = source_texture1.Sample(samp, input.uv);
	//else
	//	color = source_texture2.Sample(samp, float2(input.uv.x - 1.0f, input.uv.y));
		
	
	// 받은 인자값이 0보다 작다면 해당 픽셀을 폐기
	//clip(color.a - 0.2f);
	
	//if (color.a < 0.1f)
	//	discard; // discard : 호출되는 순간 해당 데이터를 폐기한다.
	
	return color;

}