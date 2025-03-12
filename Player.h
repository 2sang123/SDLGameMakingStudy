#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "BoxComponent.h"

class Player : public Actor
{
public:
	Player(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	class BoxComponent* GetBoxComponent() const { return mBoxComponent; }
	void SetBoxComponent(class BoxComponent* box) { mBoxComponent = box; }
private:

	SpriteComponent* mSprite;
	class PhysicsComponent* mPhysicsComponent;
	class BoxComponent* mBoxComponent;

	bool bPlayerRight;
};