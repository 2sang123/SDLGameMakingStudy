#include "Star.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "BoxComponent.h"
Star::Star(Game* game)
	:Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this, 250);
	sc->SetTexture(game->GetTexture("Assets/myStar.png"));

	mBoxComponent = new BoxComponent(this);
	mBoxComponent->SetSize(Vector2(64.0f, 64.0f));
	mBoxComponent->SetPosition(Vector2(0.f, -100.0f));
	SetBoxComponent(mBoxComponent);

}

void Star::UpdateActor(float deltaTime)
{
	mBoxComponent->Update(deltaTime);
}

void Star::ActorInput(const uint8_t* keyState)
{

}

Star::~Star()
{
	GetGame()->RemoveActor(this);
}