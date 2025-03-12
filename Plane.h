#pragma once
#include "Component.h"
#include "Actor.h"
#include "BoxComponent.h"
class Plane : public Actor {
public:
	Plane(class Game* game);
	~Plane();
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
	
	class BoxComponent* GetBoxComponent() const { return mBoxComponent; }
	void SetBoxComponent(class BoxComponent* box) { mBoxComponent = box; }
private:
	class BoxComponent* mBoxComponent;
};