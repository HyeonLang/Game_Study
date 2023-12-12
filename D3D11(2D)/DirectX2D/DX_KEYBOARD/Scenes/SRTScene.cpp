#include "pch.h"
#include "SRTScene.h"

SRTScene::SRTScene()
{
	world = new MatrixBuffer();
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
	// �޼� ��ǥ������� ����ڰ� ���� ������ ������ �̿��� ���� ���� ����� ������ ���
	// "���� �Ʒ�"�� �������� �ؼ� �ű⼭���� �츮�� ǥ���� ������ ������ �����ϰ�
	// �� ������ ��ķμ� ������ ������ ���

	// Y��ǥ ������ ���� �������� WIN_HEIGHT�� �������� 0�� �� Ȯ���� �� ����
	// �̴� ��ǥ�� �Է����� �� ���� ���� ���� ������ ��(=�Ʒ���), ���� ���� ���� ��(����)�� �� ��������ٴ� �ǹ�

	// ��, �̷��� WIN_HEIGHT�� ���ʿ� �ִ´ٸ� �츮�� API���� ��ǥ�� �Է��� �� ���� ���� �������� �ߴ� �Ͱ�
	// �����ϰ� �̿��� �� ����
	// �ݴ�� ������ ��� �� ����ߴ� ��ó�� ���� �Ʒ��� 0,0���� ���ڴٸ� �� �Լ����� WIN_HEIGHT�� 0.0f�� ��ġ�� �ٲٸ� ��

	// �߾��� 0,0���� �ϰ� �ʹٸ� ȭ�� ��ü�� ������ ���̸� ������ ����� �ִ� ������ ó���ϴ� �͵� ����
	// ���⼱ API�� �����ϱ� ���� ���� ���� �ۼ�

	// -1.0~1.0������ ���� �̿��ذ����� ������ ��ġ�� ǥ���ϴ� ����
	// �츮�� API���� �� ��ǥ�� ���� �����ϴ� ������ �ٲٴ� ��

	projection->Set(orthographic);

	world_matrix._11 = 1; // ����� 1�� ���� 1�� ���� �ִ� �����͸� 1�� �����Ѵ�
	world_matrix._22 = 1; // ����� 2�� ���� 2�� ���� �ִ� �����͸� 1�� �����Ѵ�
	world_matrix._33 = 1; // ����� 3�� ���� 3�� ���� �ִ� �����͸� 1�� �����Ѵ�
	world_matrix._44 = 1; // ����� 4�� ���� 4�� ���� �ִ� �����͸� 1�� �����Ѵ�

	srt_box = new Box(Float2(640.0f, 480.0f), Float2(1.0f, 2.2f), 0);

	worldBuffer = new MatrixBuffer();


	star = new Vortex(
		Float2((float)WIN_CENTER_X / 2, (float)WIN_CENTER_Y),	// ��ġ
		Float2(2.0f, 0.5f),		// x,y ������
		0.0f,					// �ʱ� ����
		100.0f,					// ũ��
		240,					// ǥ�� ���� ���� 
		-0.3f					// ȸ�� ���� �� �ӵ�
	);
	star->SetColor(Float4(0.8f, 0.8f, 0.1f, 1.0f));

	star_stub = new Vortex(Float2((float)WIN_CENTER_X / 2, (float)WIN_CENTER_Y), Float2(1.0f, 1.0f), 0.0f, 0.0f, 0, 0.3f);

	satelite = new Vortex(Float2(100.0f, 0.0f), Float2(1.0f, 1.0f), M_PI_4,
		25.0f, 5, 3.0f);
	satelite->SetColor(Float4(0.4f, 0.4f, 0.4f, 1.0f));
}

SRTScene::~SRTScene()
{
	delete world;
	delete view;
	delete projection;
	delete srt_box;
	delete worldBuffer;
	delete star;
	delete satelite;
}

void SRTScene::Update()
{
	srt_box->Update();
	star->Update();

	star_stub->Update();
	satelite->Update(star_stub->GetWorld());
	// satelite�� star��ġ�� ����Ѵ�.
	// star�� ����� scale, rotate ���� �����.

}

void SRTScene::Render()
{
	Device::Get()->Clear();
	// ȭ���� �ʱ�ȭ

	world->SetVS(0);
	view->SetVS(1);
	projection->SetVS(2);
	// ����ϱ� �� WVP ��ȯ�� ���� ��ĵ��� ���� ���̴��� ���
	// �� �̷� ��ȣ�� �־�� �ϴ����� VertexShader.hlsl�� ����

	// W, V, P��� �� 3���� ���۵��� ��� ����
	// ��� ���� = ���� ���̴��� �ȼ� ���̴����� ���Ǵ� ���� ������� ��Ƴ��� ����
	// �� ���ۿ��ٰ� �׷��� ǥ���� ���� ���� ������� �����ߴٰ�
	// �̸� ���̴��� �ѱ�� ����

	// ���̴� �ʿ� "��� ��� ���۰� ��� ������ �� ��"���� �̹� ���ǰ� �Ǿ������Ƿ�
	// �׷��� ���ص� ���Կ� �°� �� ���۵��� �Է��Ѵ�

	srt_box->Render();

	worldBuffer->Set(*star->GetWorld());
	worldBuffer->SetVS(0);
	star->Render();

	worldBuffer->Set(*satelite->GetWorld());
	worldBuffer->SetVS(0);
	satelite->Render();
	
}
