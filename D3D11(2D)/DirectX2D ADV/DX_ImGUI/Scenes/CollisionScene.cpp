#include "pch.h"

CollisionScene::CollisionScene()
{
	collider = new RectCollider(Vector2(100, 100));
	collider->pos = { WIN_CENTER_X, WIN_CENTER_Y };
	collider->SetActive(true);

	target = new RectCollider(Vector2(50, 50));
	target->pos = { WIN_CENTER_X / 2.0f, WIN_CENTER_Y / 2.0f };
	target->SetActive(true);
}

CollisionScene::~CollisionScene()
{
	delete collider;
	delete target;
}

void CollisionScene::Update(DWORD* deltatime)
{
	DWORD current_time = timeGetTime();	// 현재 시간을 기록
	// #include <mmsystem.h>	#pragma comment(lib, "winmm.lib") 필요

	*deltatime += current_time - time_stamp;

	if (*deltatime > 17)	// 눌린키가 존재할 경우
	{
		*deltatime -= 17;
		
		if (key_map != 0)
		{

			if ((key_map & 1) == 1)
			{
				target->pos.x -= 4.0f;
			}
			if ((key_map & 2) == 2)
			{
				target->pos.x += 4.0f;
			}
			if ((key_map & 4) == 4)
			{
				target->pos.y -= 4.0f;
			}
			if ((key_map & 8) == 8)
			{
				target->pos.y += 4.0f;
			}
		}
		
	}
	time_stamp = current_time;

	if (collider->IsCollision(target))
	{
		collider->SetColor(0, 0, 1);
	} 
	else
	{
		collider->SetColor(0, 1, 0);
	}

	if (target->IsCollision(collider))
	{
		target->SetColor(0, 0, 1);
	}
	else
	{
		target->SetColor(0, 1, 0);
	}

	collider->WorldUpdate();
	target->WorldUpdate();

}

void CollisionScene::Render()
{
	Device::Get()->Clear();

	collider->Render();
	target->Render();
}

void CollisionScene::PostRender()
{
	ImGui::Text("Coliider's Transform");
	ImGui::SliderFloat2("Collider Pos", (float*)&collider->pos, 0, WIN_WIDTH);

	ImGui::Text("Target's Transform");
	ImGui::SliderFloat2("Target Pos", (float*)&target->pos, 0, WIN_WIDTH);
}
