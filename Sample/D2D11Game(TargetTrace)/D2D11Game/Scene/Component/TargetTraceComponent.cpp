#include "stdafx.h"
#include "../Actor.h"
#include "TargetTraceComponent.h"
#include "TransformComponent.h"

void TargetTraceComponent::Update()
{
	if (target.expired() == true)
		return;

	auto current_target = target.lock();
	auto target_transform = current_target->GetComponent<TransformComponent>();

	auto my_position = transform->GetPosition();
	auto target_position = target_transform->GetPosition();

	// A - B == B���� A�� ���ϴ� ����
	auto dir = target_position - my_position;

	// ��Ÿ����� ������ �̿��� ���� ���ϱ�
	// ����(����)^2 = �غ�^2 + ����^2 
	// -> �����^2 = -> ��(�غ�^2 + ����^2)
	// -> ���� = ��(�غ�^2 + ����^2)
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);

	if (length >= 500) cur_trace_state = Trace;
	else if (length <= 300 && length >= 200) cur_trace_state = Stop;
	else if (length <= 150) cur_trace_state = Avoid;

	// ���� dir�� target ���ϴ� ���������� ũ�Ⱑ ���ԵǾ� �־� ������ ���Ⱚ���� �ٲ�� �Ѵ�.
	// -> ���� ���ͷ� ����� ������ ������ ����Ű�� ���ͷ� ���� �� �ִ�.
	D3DXVec3Normalize(&dir, &dir);

	auto next_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (cur_trace_state)
	{
	case Trace:
		// �ڽ��� ��ġ + (���� * (�ӵ� * �����Ӱ��ݽð�))���� ����ϸ�
		// ������Ʈ Ƚ���� �ƴ� �ð� ������ �°� ������ �� �ִ�.
		next_position = my_position + (dir * (speed * timer.GetElapsedTimeSec()));
		break;
	case Stop:
		next_position = my_position; 
		break;
		
	case Avoid:
		next_position = my_position - (dir * (speed * timer.GetElapsedTimeSec()));
		break;
	}

	transform->SetPosition(next_position);

	// ���� : ������ ��Ÿ Ÿ��, ��Ÿ Ÿ�� ����

	timer.Start();
}

void TargetTraceComponent::Initialize()
{
	timer.Start();
}

void TargetTraceComponent::Destroy()
{
}
