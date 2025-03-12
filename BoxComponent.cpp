#include "BoxComponent.h"
#include "Actor.h"
#include "SDL.h"

BoxComponent::BoxComponent(Actor* owner)
    : Component(owner)
    , mPosition(Vector2::Zero)
    , mSize(Vector2::Zero)
{
}

void BoxComponent::Update(float deltaTime)
{
    // Actor의 위치에 맞춰 BoxComponent의 위치를 업데이트
    mPosition = mOwner->GetPosition();
}

bool BoxComponent::Intersect(const BoxComponent& a, const BoxComponent& b)
{
    Vector2 diff = a.GetPosition() - b.GetPosition();
    float dx = fabs(diff.x);
    float dy = fabs(diff.y);
    float combinedHalfWidths = (a.GetSize().x + b.GetSize().x) / 2.f;
    float combinedHalfHeights = (a.GetSize().y + b.GetSize().y) / 2.f;

    if (dx <= combinedHalfWidths && dy <= combinedHalfHeights)
    {
        // 충돌이 발생한 경우 로그 출력
       // SDL_Log("box connect");
        return true;
    }
    return false;
}