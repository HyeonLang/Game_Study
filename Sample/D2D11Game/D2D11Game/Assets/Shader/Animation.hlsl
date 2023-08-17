
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

cbuffer AnimationBuffer : register(b2)
{
	float2 sprite_offset;
	float2 sprite_size;
	float2 texture_size;
	float is_animated;
}
	
PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	
	output.uv = input.uv;
	
	// 텍스처와 프레임 사이즈를 사용해 알맞는 uv 비율을 계산한다.
	output.uv *= sprite_size / texture_size;
	output.uv += sprite_offset / texture_size;
	
	return output; 
}

Texture2D source_texture1 : register(t0);
Texture2D source_texture2 : register(t1); 
SamplerState samp : register(s0); 

float4 PS(PixelInput input) : SV_Target 
{
	if (is_animated == 1.0f)
		return source_texture1.Sample(samp, input.uv);
	else
		return float4(1, 0, 0, 1);
	
}