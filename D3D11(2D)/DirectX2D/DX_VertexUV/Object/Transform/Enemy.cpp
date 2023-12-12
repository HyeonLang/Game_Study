#include "pch.h"

Enemy::Enemy(Float2 pos, Float2 size, Float2 s, float a, float v, Matrix* parent)
	: Transform(pos, s, a, parent), velocity(v), init_pos(pos)
{
	rotate_timer = 0;

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
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;	// 텍스쳐의 U, V, W 방향으로 1이상의 범위를 어떻게 채울지 결정하는 변수, 큰 이미지를 다룰때 사용

	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;	// 이미지를 2개이상 출력시 sd가 다루는 사진의 우선순위를 결정한다. (위로 올라가는 것)

	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;	// 밉맵의 범위를 설정, 3D에서 빠른 렌더링을 위해 텍스처를 간략화 한 집합의 범위

	// 우리가 불러온 이미지를 디바이스에 등록하기 위해
	// 각종 설정값들을 설정하는 부분
	DEVICE->CreateSamplerState(&sd, &sampler_state);
}

Enemy::~Enemy()
{
	delete rect;
	srv->Release();
	sampler_state->Release();
}

void Enemy::Update(DWORD time)
{
	
	rotate_timer += time;
	if (rotate_timer >= 1000)	// 1초가 지나면
	{
		rotate_timer -= 1000;

		std::random_device rd;
		std::mt19937_64 rng(rd());
		std::uniform_real_distribution<double> rand_dir(0.0, 2 * M_PI);
		// 0~360도 까지의 범위를 랜덤하게 지정

		angle = rand_dir(rng);	// 무작위 각도

		
	}
	Float2 cur_pos = { this->pos.x + velocity * sin(angle), this->pos.y + velocity * -cos(angle) };	
	// 다음 위치를 위와 같이 계산
    // 어째서인지는 모르겠으나, 본래라면 cos이 x좌표, sin이 y좌표를 계산하는 데 이용되어야 하나
    // 실제로는 반대로 작용되고 있음
    // Transform의 기본 회전 등이 오른쪽을 보고 있다 상정할 때를 기준으로 계산해뒀는데
    // 이게 아니어서 식이 다르게 작용하고 있는 것 같다

	if (cur_pos.x < 0
		|| cur_pos.x > WIN_WIDTH
		|| cur_pos.y < 0
		|| cur_pos.y > WIN_HEIGHT) // 계산된 위치가 전체 화면을 벗어나는 위치인 경우
	{
		SetPos(init_pos);
	}
	else
	{
		SetPos(cur_pos);
	}

	WorldUpdate();
}

void Enemy::Render()
{
	WB->Set(world);
	WB->SetVS(0);

	DVC->PSSetShaderResources(0, 1, &srv);
	// 그림을 출력하기 위해 디바이스에 이미지를 전담하는 객체를 등록하는 과정
	// "지금 출력할 때는 이 그림을 사용하라"

	DVC->PSSetSamplers(0, 1, &sampler_state);
	// 이번에 그릴 그림은 이 샘플러를 사용하라고 등록

	rect->Render();
}
