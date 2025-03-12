#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include <functional>
// �̱��� �� ���� ����
class Button : public Actor
{
public:
    Button(class Game* game);
    void SetTexture(class Texture* texture);
    void SetOnClick(std::function<void()> onClick);
    void ActorInput(const Uint8* keyState) override;
    void UpdateActor(float deltaTime) override;

private:
    class SpriteComponent* mSprite;
    std::function<void()> mOnClick;
};