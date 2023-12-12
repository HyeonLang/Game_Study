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

	// ���� TragetTraceComponent �ۼ�
	// - �ش� ������Ʈ�� Ÿ���� ���õǸ� ������Ʈ�� ������ ���Ͱ� Ÿ�ٹ������� �̵��ϵ��� �ۼ��ϱ�
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
