#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxForward() const { return mMaxForwardSpeed; }
	float GetMaxJump() const { return mMaxJumpPower; }

	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetJumpKey() const {return mJumpKey;}


	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxJump(float speed) { mMaxJumpPower = speed; }

	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetJumpKey(int key) { mJumpKey = key; }
	
private:
	
	float mMaxForwardSpeed;
	float mMaxJumpPower;

	int mForwardKey;
	int mBackKey;
	int mJumpKey;
};