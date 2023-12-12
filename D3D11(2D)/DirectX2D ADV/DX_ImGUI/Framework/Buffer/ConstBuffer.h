#pragma once
class ConstBuffer
{
private:
	ID3D11Buffer* buffer;

	void* data;	// 버퍼 객체에 저장될 데이터 멤버 변수
	UINT data_size;	// void 포인트형 data의 정보를 모르니 data 총 크기 저장 변수

public:
	ConstBuffer(void* data, UINT data_szie);
	virtual ~ConstBuffer();
	// 소멸자가 가상함수인 이유 : 상수 버퍼는 다른 버퍼에 상속시켜 사용할 내용
	// 부모클래스의 소멸자만 호출될 가능성이 높음
	// 따라서 상속받은 버퍼 클래스의 소멸자가 확실히 호출될 수 있도록 가상함수로 생성

	void SetVS(UINT slot);
	void SetPS(UINT slot);
	// 각 셰이더 슬롯에 넘길 데이터 설정
};

