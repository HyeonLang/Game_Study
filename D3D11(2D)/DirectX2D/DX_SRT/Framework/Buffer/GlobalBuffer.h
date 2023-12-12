#pragma once

class MatrixBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Matrix matrix;
	} data;
	// 셰이더를 이용할 때, 정점 등의 데이터를 MatrixBuffer를 이용해서 넣는다.
	// 셰이더 쪽에 들어가는 버퍼의 크기는 16의 배수여야 한다.
	// 아닐경우 경고가 발생, 오류가 있을 수 있다.(컴파일, 예외처리 등은 발생하지 않음.)
	// Matrix = XMMATRIX 자료형, 이를 16의 배수에 맞는 사이즈의 자료형이 아님.
public:
	MatrixBuffer() : ConstBuffer(&data, sizeof(data))
	{
		data.matrix = XMMatrixIdentity();
		// XMMatrixIdentity = 단위행렬을 반환하는 함수
		// == 처음 이 MatrixBuffer가 만들어졌을 때 초기값으로는 4x4 단위행렬을 가지도록 한다

		// 단위행렬 = 주대각선(왼쪽 위에서부터 오른쪽 아래로 향하는 대각선)의 값이 모두 1이고
		// 나머지 값은 모두 0인 행렬

		/* 실제로 가져오게 되는 행렬은 다음과 같음
		( 1 0 0 0 )
		( 0 1 0 0 )
		( 0 0 1 0 )
		( 0 0 0 1 )

		왜 하필 4x4냐면 3D 전반에서 사용되는 기본적인 행렬 사이즈가 4x4이기 때문
		WVP 변환 등에서 상세하게 설명하진 않았지만, 변환 행렬을 구해가지고 이를 실제 위치 벡터 등에 사용할 떄
		기본적으로 원소가 4개인 벡터를 사용하기 떄문에, 이에 사이즈를 맞추기 위해 4*4 행렬을 사용하는 것
		*/

	}
	~MatrixBuffer() {};

	void Set(Matrix value)
	{
		data.matrix = XMMatrixTranspose(value);
		// 행렬 전용 복사함수
	}
};

class ColourBuffer : public ConstBuffer	// 색상을 팩셀 셰이더에 등록하기 위한 버퍼
{
	// 색상을 픽셀 셰이더에 등록하기 위한 버퍼
	// colout : 영국식 영어에서 쓰이는 스펠링
public:
	struct Data
	{
		Float4 colour;
	} data;

	ColourBuffer() : ConstBuffer(&data, sizeof(data))
	{
		data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f); // 초기값 흰색
	}

};