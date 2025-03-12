#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
	, mForwardKey(0)
	, mBackKey(0)
	, mJumpKey(0)
{

}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	
	float forwardSpeed = 0.0f;
	if (keyState[mForwardKey])
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	if (keyState[mBackKey])
	{
		forwardSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	// 점프 키가 눌렸을 때 점프 파워 설정
	if (keyState[mJumpKey])
	{
		SetJumpPower(mMaxJumpPower);
	}
	else 
	{
		SetJumpPower(1.0f);
	}
}