#include "Plane.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "BoxComponent.h"
Plane::Plane(Game* game)
	:Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this, 200);
	sc->SetTexture(game->GetTexture("Assets/Plane.png"));

	mBoxComponent = new BoxComponent(this);
	mBoxComponent->SetSize(Vector2(120.0f, 24.0f));
	mBoxComponent->SetPosition(Vector2(0.f, -100.0f));
	SetBoxComponent(mBoxComponent);

}

void Plane::UpdateActor(float deltaTime)
{
	mBoxComponent->Update(deltaTime);
}

void Plane::ActorInput(const uint8_t* keyState)
{
	
}

Plane::~Plane()
{
	GetGame()->RemoveActor(this);
}