#include "pch.h"

SolarScene::SolarScene()
{
	world = new MatrixBuffer();	// 각 오브젝트를 출력할 때 마다 오브젝트의 월드를 받아 세팅
	view = new MatrixBuffer();
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH
	(
		0.0f, (float)WIN_WIDTH,
		// 좌표계의 X좌표 기준을 0 ~ (WIN_WIDTH)까지의 범위로 설정
		(float)WIN_HEIGHT, 0.0f,
		// 좌표계의 Y좌표 기준을 (WIN_HEIGHT) ~ 0까지의 범위로 설정
		-1.0f, 1.0f
	);

	projection->Set(orthographic);

	//world_matrix._11 = 1; // 행렬의 1번 행의 1번 열에 있는 데이터를 1로 설정한다
	//world_matrix._22 = 1; // 행렬의 2번 행의 2번 열에 있는 데이터를 1로 설정한다
	//world_matrix._33 = 1; // 행렬의 3번 행의 3번 열에 있는 데이터를 1로 설정한다
	//world_matrix._44 = 1; // 행렬의 4번 행의 4번 열에 있는 데이터를 1로 설정한다

	sun = new Vortex(Float2(float(WIN_CENTER_X), float(WIN_HEIGHT)), Float2(1.0f, 1.0f), 0.0f,
		250.0f, 200, -0.2f);
	sun->SetColor(Float4(0.9f, 0.4f, 0.1f, 1.0f));

	mercury = new Vortex(Float2(0.0f, float(WIN_CENTER_Y) - 30.0f), Float2(1.0f, 1.0f), 0.0f, 20.0f, 20, -0.2f);
	mercury->SetColor(Float4(0.8f, 0.8f, 0.8f, 1.0f));

	sun_stub = new Vortex(Float2(float(WIN_CENTER_X), float(WIN_HEIGHT)), Float2(1.0f, 1.0f), 0.0f,
		0.0f, 0, -0.15f);

	venus = new Vortex(Float2(0.0f, float(WIN_CENTER_Y) + 30.0f), Float2(1.0f, 1.0f), 0.0f, 20.0f, 20, 0.2f);
	venus->SetColor(Float4(0.9f, 0.8f, 0.6f, 1.0f));

	earth = new Vortex(Float2(0.0f, float(WIN_CENTER_Y) + 150.0f),
		Float2(1.0f, 1.0f), 0.0f, 50.0f, 20, 0.1f);
	earth->SetColor(Float4(0.2f, 1.0f, 0.3f, 1.0f));

	earth_stub = new Vortex(Float2(0.0f, float(WIN_CENTER_Y) + 150.0f),
		Float2(1.0f, 1.0f), 0.0f, 0.0f, 0, 0.5f);

	moon = new Vortex(Float2(0.0f, 70.0f),
		Float2(1.0f, 1.0f), 0.0f, 10.0f, 3, 0.0f);
	moon->SetColor(Float4(0.6f, 0.6f, 0.6f, 1.0f));

	// 세부적인 데이터 조정이 필요하다면 코드를 고치기보다 
	// 데이터들을 코드 외부 파일로서 저장해 읽어오는 방식이 필수다.

	object_pos = Float2(WIN_CENTER_X, WIN_CENTER_Y);
	player = new Box(object_pos, Float2(1.0f, 1.0f), 0.0f);
	player->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));

	target = new Box(Float2(mouse_pos.x, mouse_pos.y), Float2(0.3f, 0.3f), M_PI / 4);
	target->SetColor(Float4(0.3f, 0.1f, 0.6f, 1.0f));
}


SolarScene::~SolarScene()
{
	delete world;
	delete view;
	delete projection;

	delete sun;
	delete mercury;
	delete venus;
	delete earth;
	delete earth_stub;
	delete moon;

	delete player;
	delete target;
}

void SolarScene::Update(DWORD* deltatime)
{
	sun->Update();
	// 화면 전체를 기준으로
	mercury->Update(sun->GetWorld());
	// sun 위치의 정중앙을 기준으로 sun의 정중앙을 (0,0) 한다

	sun_stub->Update();
	venus->Update(sun_stub->GetWorld());

	earth->Update(sun_stub->GetWorld());
	earth_stub->Update(sun_stub->GetWorld());
	moon->Update(earth_stub->GetWorld());

	DWORD current_time = timeGetTime();	// 현재 시간을 기록
	// #include <mmsystem.h>	#pragma comment(lib, "winmm.lib") 필요

	if (key_map != 0)	// 눌린키가 존재할 경우
	{
		*deltatime += current_time - time_stamp;
		if (*deltatime > 17)
		{
			*deltatime -= 17;
			if ((key_map & 1) == 1)
			{
				object_pos.x -= 4.0f;
			}
			if ((key_map & 2) == 2)
			{
				object_pos.x += 4.0f;
			}
			if ((key_map & 4) == 4)
			{
				object_pos.y -= 4.0f;
			}
			if ((key_map & 8) == 8)
			{
				object_pos.y += 4.0f;
			}
		}
	}
	player->Update(object_pos);	// 키보드 처리 후 객체 조정 후 업데이트
	time_stamp = current_time;

	target->Update(Float2(mouse_pos.x, mouse_pos.y));
}

void SolarScene::Render()
{
	Device::Get()->Clear();
	view->SetVS(1);
	projection->SetVS(2);

	world->Set(*sun->GetWorld());
	world->SetVS(0);
	sun->Render();

	world->Set(*mercury->GetWorld());
	world->SetVS(0);
	mercury->Render();

	world->Set(*venus->GetWorld());
	world->SetVS(0);
	venus->Render();

	world->Set(*earth->GetWorld());
	world->SetVS(0);
	earth->Render();

	world->Set(*moon->GetWorld());
	world->SetVS(0);
	moon->Render();

	world->Set(*player->GetWorld());
	world->SetVS(0);
	player->Render();

	world->Set(*target->GetWorld());
	world->SetVS(0);
	target->Render();
}

