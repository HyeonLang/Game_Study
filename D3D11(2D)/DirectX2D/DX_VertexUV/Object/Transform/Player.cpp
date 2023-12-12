#include "pch.h"

Player::Player(Float2 pos, Float2 size, Float2 s, float a, Matrix* parent)
	: Transform(pos, s, a, parent)
{
	rect = new RectUV(pos, size);

	ScratchImage image;	// 실제 이미지 파일 로딩 역할 객체

	LoadFromWICFile(L"Textures/images/missile.jpg", WIC_FLAGS_NONE, nullptr, image);
	// 실존 파일 로드 함수
	CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &srv);
	// 멤버 번션 srv에 DEVICE와 image를 이용해서 셰이더 리소스 뷰 생성

	D3D11_SAMPLER_DESC sd = {};	// 입력받은 이미지를 어떤식으로 출력할 것인지 설정하는 구조체

	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;	// 입력받은 이미지에 어떤 필터를 적용할 것인가, 크로마키가 존재할 경우 잘라내는 방식 설정

	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;	// 텍스쳐의 U, V, W 방향으로 범위를 어떻게 채울지 결정하는 변수, 큰 이미지를 다룰때 사용

	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;	// 이미지를 2개이상 출력시 sd가 다루는 사진의 우선순위를 결정한다. (위로 올라가는 것)

	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;	// 밉맵의 범위를 설저, 3D에서 빠른 렌더링을 위해 텍스처를 간략화 한 집합의 범위

	// 우리가 불러온 이미지를 디바이스에 등록하기 위해
	// 각종 설정값들을 설정하는 부분
	DEVICE->CreateSamplerState(&sd, &sampler_state);

}

Player::~Player()
{
	delete rect;
	srv->Release();
	sampler_state->Release();
}


void Player::Update(Float2 pos, Float2 target)
{
	SetPos(pos);
	
	float angle = -atan2(double(pos.y) - double(target.y), double(target.x) - double(pos.x)) + M_PI_2;
	// 두 점 사이의 각도를 구하는 공식
	// Transform에서 각도를 0이라 하면 오른쪽을 바라보도록 설정, 따라서 보정값 pi/2를 더해준다.

	SetAngle(angle);

	WorldUpdate();
}

void Player::Render()
{
	WB->Set(world);
	WB->SetVS(0);

	DVC->PSSetShaderResources(0, 1, &srv);
	// 그림을 출력하기 위해 디바이스에 이미지 전담 객체를 등록하는 과정
	 
	DVC->PSSetSamplers(0, 1, &sampler_state);
	// 이번에 그릴 그림은 이 샘플러를 사용


	rect->Render();
}
