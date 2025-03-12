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
    // Actor�� ��ġ�� ���� BoxComponent�� ��ġ�� ������Ʈ
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
        // �浹�� �߻��� ��� �α� ���
       // SDL_Log("box connect");
        return true;
    }
    return false;
}