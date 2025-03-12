#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	// Lower update order to update first
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetJumpPower() const { return mJumpPower; }

	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void SetJumpPower(float speed) { mJumpPower = speed; }
	
private:
	float mForwardSpeed;
	float mJumpPower;
	bool mIsJumping;
};