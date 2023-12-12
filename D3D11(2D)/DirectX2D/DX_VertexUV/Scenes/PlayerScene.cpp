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
		missiles[i] = new Enemy(Float2(WIN_CENTER_X, WIN_CENTER_Y / 2), Float2(10.0f, 50.0f), Float2(1.0f, 1.0f), 0.0f, 4);
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

	if (*deltatime > 17)	// 눌린키가 존재할 경우
	{
		for (auto e : missiles)
			e->Update(*deltatime);
		*deltatime -= 17;
		
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
	}
	player->Update(object_pos, Float2(mouse_pos.x, mouse_pos.y));	
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
