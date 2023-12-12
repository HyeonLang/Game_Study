#include "stdafx.h"
#include "AnimatorComponent.h"

AnimatorComponent::AnimatorComponent(Context* const context, Actor* actor, TransformComponent* transform)
    : IComponent(context, actor, transform)
{
}

AnimatorComponent::~AnimatorComponent()
{
    Destroy();
}

void AnimatorComponent::Initialize()
{

}

void AnimatorComponent::Update()
{
    if (current_animation.expired() || IsPlaying() != true)
        return;

    frame_counter += context->GetSubsystem<Timer>()->GetDeltaTimeMS();

    if (frame_counter > GetCurrentKeyframe()->time)
    {
        current_frame_number++;

        switch (current_animation.lock()->GetRepeatType())
        {
        case RepeatType::Once:
            if (current_frame_number >= current_animation.lock()->GetKeyframeCount())
            {
                current_frame_number = current_animation.lock()->GetKeyframeCount() - 1;
                Pause();
            }
            break;
        case RepeatType::Loop:
            current_frame_number %= current_animation.lock()->GetKeyframeCount();
            break;
        }

        frame_counter = 0.0f;
    }

}

void AnimatorComponent::Destroy()
{
    animations.clear();
}

const std::shared_ptr<class Animation> AnimatorComponent::GetCurrentAnimation() const
{
    return current_animation.expired() ? nullptr : current_animation.lock();
}

void AnimatorComponent::SetCurrentAnimation(const std::string& animation_name)
{
    assert(animations.find(animation_name) != animations.end());

    current_animation = animations[animation_name];

    current_frame_number = 0;
    frame_counter = 0.0f;

}

const Keyframe* const AnimatorComponent::GetCurrentKeyframe() const
{
    assert(current_animation.expired() != true);
    return current_animation.lock()->GetKeyframeFromIndex(current_frame_number);
}

void AnimatorComponent::AddAnimation(const std::string& animation_name, const std::shared_ptr<class Animation>& animation)
{
    assert(animations.find(animation_name) == animations.end());
    animations[animation_name] = animation;
}

void AnimatorComponent::AddAnimation(const std::string& path)
{
    auto resource_manager = context->GetSubsystem<ResourceManager>();

    auto animation = resource_manager->Load<Animation>(path);

    if (animation == nullptr)
    {
        assert(false);
        return;
    }

    AddAnimation(animation->GetResourceName(), animation);
}

void AnimatorComponent::Play()
{
    animation_mode = AnimationMode::Play;
}

void AnimatorComponent::Stop()
{
    animation_mode = AnimationMode::Stop;
    current_frame_number = 0;
    frame_counter = 0.0f;
}

void AnimatorComponent::Pause()
{
    animation_mode = AnimationMode::Pause;
}
