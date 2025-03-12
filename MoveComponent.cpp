#include "MoveComponent.h"
#include "Actor.h"
MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mForwardSpeed(0.0f)
	, mJumpPower(0.0f)
{
}

void MoveComponent::Update(float deltaTime)
{

	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();
		pos.x += mForwardSpeed * deltaTime;

		if (pos.x < -630.0f) { pos.x = -630.0f; } // �� ��
		else if (pos.x > 630.0f) { pos.x = 630.0f; } // �� ��
		mOwner->SetPosition(pos);
	}

	if (!Math::NearZero(mJumpPower) && !mIsJumping)
	{
		SetJumpPower(mJumpPower);
		float mVerticalSpeed = GetJumpPower();
		Vector2 pos = mOwner->GetPosition();
		//mVerticalSpeed += deltaTime; ��ü �߷�
		pos.y += mVerticalSpeed * deltaTime;
		mOwner->SetPosition(pos);
	}
}