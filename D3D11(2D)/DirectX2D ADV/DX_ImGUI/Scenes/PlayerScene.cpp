#include "pch.h"

PlayerScene::PlayerScene()
{
	object_pos = Float2(WIN_CENTER_X, WIN_CENTER_Y);

	player = new Player(object_pos, Float2(100.0f, 100.0f), Float2(1.0f, 1.0f), 0.0f);

	world_buffer = new MatrixBuffer();

	sun = new Vortex(Float2(float(WIN_CENTER_X), float(WIN_HEIGHT)), Float2(1.0f, 1.0f), 0.0f,
		250.0f, 200, -0.2f);
	sun->SetColor(Float4(0.9f, 0.4f, 0.1f, 1.0f));

	cursor = new Vortex(Float2(mouse_pos.x, mouse_pos.y), Float2(1.0f, 1.0f), 0.0f,
		10.0f, 4, 0.05f);
	cursor->SetColor(Float4(0.8f, 0.8f, 0.1f, 1.0f));

	for (int i = 0; i < 4; i++)	// 동적할당시엔 auto 사용을 피할 것 
	{
		missiles[i] = new Enemy(Float2(WIN_CENTER_X, WIN_CENTER_Y / 4), Float2(10.0f, 50.0f), Float2(1.0f, 1.0f), 0.0f, 4, 
			(i == 3) ? ENEMY_STATE::CHASE : ENEMY_STATE::RANDOM);
	}
}

PlayerScene::~PlayerScene()
{
	delete player;
	delete world_buffer;
	delete sun;
	for (auto e : missiles)
		delete e;
}

void PlayerScene::Update(DWORD* deltatime)
{

	DWORD current_time = timeGetTime();	// 현재 시간을 기록
	// #include <mmsystem.h>	#pragma comment(lib, "winmm.lib") 필요

	*deltatime += current_time - time_stamp;

	player->Update(deltatime, Float2(mouse_pos.x, mouse_pos.y));

	if (*deltatime > 17)	// 눌린키가 존재할 경우
	{
		for (auto e : missiles)
			e->Update(*deltatime, &(player->pos));
		*deltatime -= 17;
		/*
		if (key_map != 0)
		{
			
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
		*/
	}
	time_stamp = current_time;

	sun->Update();

	cursor->SetPos(Float2(mouse_pos.x, mouse_pos.y));
	cursor->Update();

}

void PlayerScene::Render()
{
	Device::Get()->Clear();
	
	world_buffer->Set(*sun->GetWorld());
	world_buffer->SetVS(0);
	sun->Render();

	player->Render();

	for (auto e : missiles)
		e->Render();

	world_buffer->Set(*cursor->GetWorld());
	world_buffer->SetVS(0);
	cursor->Render();
}

void PlayerScene::PostRender()
{
	ImGui::Text("Player Object's Transform");
	ImGui::SliderFloat2("PlayerPos", (float*)&player->pos, 0, WIN_WIDTH);
	ImGui::SliderFloat3("PlayerRot", (float*)&player->rot, -M_PI_2, XM_2PI - XM_PIDIV2);
	// XM_2PI : DirectX 관련 라이브러리에 있는 2pi
	ImGui::SliderFloat2("PlayerScale", (float*)&player->scale, -10, 10);
	// SliderFloatN : 한줄에 N개의 슬라이더바를 만들고 입력받은 float* 집합을 할당한다. 
	// 각 바는 매개변수 뒤쪽 2개를 범위로하고 바를 움직이는 것으로 가능.

	ImGui::Text("Enemy Object's Transform");
	ImGui::SliderFloat2("EnemyPos", (float*)&missiles[0]->pos, 0, WIN_WIDTH);
	ImGui::SliderFloat3("EnemyRot", (float*)&missiles[0]->rot, 0.0f,2 * M_PI);
	ImGui::SliderFloat2("EnemyScale", (float*)&missiles[0]->scale, -10, 10);
	// ImGui에서 직접 다루는 데이터는
	// 클릭한 칸이 가지고 있는 이름을 이용해 데이터를 판별하므로
	// 둘 이상의 데이터가 같은 이름을 쓰고 있을 경우엔 한 쪽을 조절할 경우 다른 쪽도 조절되어버리므로
	// 그럴 필요가 없다면 이름은 가급적 다른 것을 이용할 것을 권장
}
