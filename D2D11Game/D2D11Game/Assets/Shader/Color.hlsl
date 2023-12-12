
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


PixelInput VS(VertexInput input) // VS �ܰ� : IA���� ���� ������ �������ִ� �ܰ�
{
	PixelInput output;
	
	// ���� �����ǿ� SV_ ���λ縦 �ٿ� ���� �ܰ�� �Ѱ��ش� -> RS �ܰ迡�� ����� ������ ��ǥ�� ��������
	// ����� ���� ���� Ư�� �������� ��ȯ�����ش�.
	// ���� -> �� -> �������� ������ ���־�� �Ѵ�.
	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	
	output.color = input.color;
	
	return output; // ��ȯ�� ���� RS�ܰ踦 ��ģ��.
}
 
float4 PS(PixelInput input) : SV_Target // ���� ���õ� ���� ���� Ÿ���� ����϶�
{
	return input.color;
}