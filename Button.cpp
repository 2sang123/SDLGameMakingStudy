#include "Game.h"
#include "Button.h"
// ¹Ì±¸Çö
Button::Button(Game* game)
    : Actor(game)
    , mOnClick(nullptr)
{
    mSprite = new SpriteComponent(this);
}

void Button::SetTexture(Texture* texture)
{
    mSprite->SetTexture(texture);
}

void Button::SetOnClick(std::function<void()> onClick)
{
    mOnClick = onClick;
}

void Button::ActorInput(const Uint8* keyState)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    // Check if mouse is over the button
    Vector2 pos = GetPosition();
    if (x >= pos.x - mSprite->GetTexWidth() / 2 && x <= pos.x + mSprite->GetTexWidth() / 2 &&
        y >= pos.y - mSprite->GetTexHeight() / 2 && y <= pos.y + mSprite->GetTexHeight() / 2)
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if (mOnClick)
            {
                mOnClick();
            }
        }
    }
}

void Button::UpdateActor(float deltaTime)
{
}
