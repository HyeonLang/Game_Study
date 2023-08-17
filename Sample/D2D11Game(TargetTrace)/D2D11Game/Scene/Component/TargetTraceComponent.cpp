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

	// A - B == B에서 A로 향하는 백터
	auto dir = target_position - my_position;

	// 피타고라스의 정리를 이용한 길이 구하기
	// 길이(빗변)^2 = 밑변^2 + 높이^2 
	// -> √빗변^2 = -> √(밑변^2 + 높이^2)
	// -> 빗변 = √(밑변^2 + 높이^2)
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);

	if (length >= 500) cur_trace_state = Trace;
	else if (length <= 300 && length >= 200) cur_trace_state = Stop;
	else if (length <= 150) cur_trace_state = Avoid;

	// 현재 dir이 target 향하는 백터이지만 크기가 포함되어 있어 순수한 방향값으로 바꿔야 한다.
	// -> 단위 백터로 만들어 순수한 방향을 가리키는 백터로 만들 수 있다.
	D3DXVec3Normalize(&dir, &dir);

	auto next_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (cur_trace_state)
	{
	case Trace:
		// 자신의 위치 + (방향 * (속도 * 프레임간격시간))으로 계산하면
		// 업데이트 횟수가 아닌 시간 비율에 맞게 움직일 수 있다.
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

	// 과제 : 스무스 델타 타임, 델타 타임 조사

	timer.Start();
}

void TargetTraceComponent::Initialize()
{
	timer.Start();
}

void TargetTraceComponent::Destroy()
{
}
