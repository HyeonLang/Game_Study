#include "stdafx.h"
#include "Scene.h"
#include "Scene/Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"
#include "Scene/Component/AIScriptComponent.h"
#include "Scene/Component/AnimatorComponent.h"


Scene::Scene(class Context* const context)
	: context(context)
{
	renderer = context->GetSubsystem<Renderer>();

	//=========================================================================================
	// [Actors]
	//=========================================================================================
	std::shared_ptr<Actor> camera = CreateActor();
	camera->AddComponent<CameraComponent>();
	camera->SetName("MainCamera");

	std::shared_ptr<Actor> player = CreateActor();
	player->AddComponent<MeshRendererComponent>();
	player->AddComponent<MoveScriptComponent>();
	//player->AddComponent<AIScriptComponent>();

	auto animator = player->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/Idle.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Idle");

	player->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(100.0f, 100.0f, 1.0f));
	player->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(100.0f, 0.0f, 1.0f));
	player->SetName("Player");

	std::shared_ptr<Actor> monster = CreateActor();
	monster->AddComponent<MeshRendererComponent>();
	//monster->AddComponent<MoveScriptComponent>();
	monster->AddComponent<AIScriptComponent>();
	monster->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(100.0f, 100.0f, 1.0f));
	monster->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-100.0f, 0.0f, 1.0f));
	monster->SetName("Monster");

	// 과제 TragetTraceComponent 작성
	// - 해당 컴포넌트에 타겟이 세팅되면 컴포너트를 소유한 액터가 타겟방향으로 이동하도록 작성하기
	//monster->AddComponent<class TargetTraceComponent>();
	//monster->GetComponent<TargetTraceComponent>()->SetTarget(player);
}

Scene::~Scene()
{	
}

void Scene::Update()
{
	for (const auto& actor : actors)
		actor->Update();

	if (is_update != true)
	{
		renderer->UpdateRenderables(this);
		is_update = true;
	}
}	

const std::shared_ptr<class Actor> Scene::CreateActor(const bool& is_active)
{
	std::shared_ptr<class Actor> actor = std::make_shared<Actor>(context);
	actor->SetActive(is_active);
	AddActor(actor);
	return actor;
}

void Scene::AddActor(const std::shared_ptr<class Actor>& actor)
{
	is_update = false;
	actors.emplace_back(actor);
}
