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

	for (int i = 0; i < 4; i++)	// �����Ҵ�ÿ� auto ����� ���� �� 
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

	DWORD current_time = timeGetTime();	// ���� �ð��� ���
	// #include <mmsystem.h>	#pragma comment(lib, "winmm.lib") �ʿ�

	*deltatime += current_time - time_stamp;

	player->Update(deltatime, Float2(mouse_pos.x, mouse_pos.y));

	if (*deltatime > 17)	// ����Ű�� ������ ���
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
	// XM_2PI : DirectX ���� ���̺귯���� �ִ� 2pi
	ImGui::SliderFloat2("PlayerScale", (float*)&player->scale, -10, 10);
	// SliderFloatN : ���ٿ� N���� �����̴��ٸ� ����� �Է¹��� float* ������ �Ҵ��Ѵ�. 
	// �� �ٴ� �Ű����� ���� 2���� �������ϰ� �ٸ� �����̴� ������ ����.

	ImGui::Text("Enemy Object's Transform");
	ImGui::SliderFloat2("EnemyPos", (float*)&missiles[0]->pos, 0, WIN_WIDTH);
	ImGui::SliderFloat3("EnemyRot", (float*)&missiles[0]->rot, 0.0f,2 * M_PI);
	ImGui::SliderFloat2("EnemyScale", (float*)&missiles[0]->scale, -10, 10);
	// ImGui���� ���� �ٷ�� �����ʹ�
	// Ŭ���� ĭ�� ������ �ִ� �̸��� �̿��� �����͸� �Ǻ��ϹǷ�
	// �� �̻��� �����Ͱ� ���� �̸��� ���� ���� ��쿣 �� ���� ������ ��� �ٸ� �ʵ� �����Ǿ�����Ƿ�
	// �׷� �ʿ䰡 ���ٸ� �̸��� ������ �ٸ� ���� �̿��� ���� ����
}
