#include "pch.h"

SolarScene::SolarScene()
{
	world = new MatrixBuffer();	// �� ������Ʈ�� ����� �� ���� ������Ʈ�� ���带 �޾� ����
	view = new MatrixBuffer();
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH
	(
		0.0f, (float)WIN_WIDTH,
		// ��ǥ���� X��ǥ ������ 0 ~ (WIN_WIDTH)������ ������ ����
		(float)WIN_HEIGHT, 0.0f,
		// ��ǥ���� Y��ǥ ������ (WIN_HEIGHT) ~ 0������ ������ ����
		-1.0f, 1.0f
	);

	projection->Set(orthographic);

	//world_matrix._11 = 1; // ����� 1�� ���� 1�� ���� �ִ� �����͸� 1�� �����Ѵ�
	//world_matrix._22 = 1; // ����� 2�� ���� 2�� ���� �ִ� �����͸� 1�� �����Ѵ�
	//world_matrix._33 = 1; // ����� 3�� ���� 3�� ���� �ִ� �����͸� 1�� �����Ѵ�
	//world_matrix._44 = 1; // ����� 4�� ���� 4�� ���� �ִ� �����͸� 1�� �����Ѵ�

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

	// �������� ������ ������ �ʿ��ϴٸ� �ڵ带 ��ġ�⺸�� 
	// �����͵��� �ڵ� �ܺ� ���Ϸμ� ������ �о���� ����� �ʼ���.

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
	// ȭ�� ��ü�� ��������
	mercury->Update(sun->GetWorld());
	// sun ��ġ�� ���߾��� �������� sun�� ���߾��� (0,0) �Ѵ�

	sun_stub->Update();
	venus->Update(sun_stub->GetWorld());

	earth->Update(sun_stub->GetWorld());
	earth_stub->Update(sun_stub->GetWorld());
	moon->Update(earth_stub->GetWorld());

	DWORD current_time = timeGetTime();	// ���� �ð��� ���
	// #include <mmsystem.h>	#pragma comment(lib, "winmm.lib") �ʿ�

	if (key_map != 0)	// ����Ű�� ������ ���
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
	player->Update(object_pos);	// Ű���� ó�� �� ��ü ���� �� ������Ʈ
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

