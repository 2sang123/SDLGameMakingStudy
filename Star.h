#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "BoxComponent.h"

class Star : public Actor
{
public:
	Star(class Game* game);
	~Star();
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	class BoxComponent* GetBoxComponent() const { return mBoxComponent; }
	void SetBoxComponent(class BoxComponent* box) { mBoxComponent = box; }

private:

	class BoxComponent* mBoxComponent;
};