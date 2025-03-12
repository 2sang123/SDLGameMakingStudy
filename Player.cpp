#include "Player.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "BoxComponent.h"
#include "Game.h"
#include "Plane.h"
#include "Star.h"

Player::Player(Game* game)
	:Actor(game)
{
	mSprite = new SpriteComponent(this, 150);
	mSprite->SetTexture(game->GetTexture("Assets/2DPlayerAiMake.png"));
	
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_D);
	ic->SetBackKey(SDL_SCANCODE_A);
	ic->SetJumpKey(SDL_SCANCODE_W);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxJump(200.0f);


	mBoxComponent = new BoxComponent(this);
	mBoxComponent->SetSize(Vector2(64.0f, 64.0f));
	mBoxComponent->SetPosition(Vector2(0.0f, 0.0f));
	SetBoxComponent(mBoxComponent);


	mPhysicsComponent = new PhysicsComponent(this);

	bPlayerRight = true;
}

void Player::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	bool onGround = false;

	for (auto plane : GetGame()->GetPlanes())
	{
		if (plane)
		{
			if (BoxComponent::Intersect(*mBoxComponent, *plane->GetBoxComponent()))
			{
				onGround = true;
				break;
			}
		}
	}
	
	for (auto star : GetGame()->GetStar())
	{
		if (star)
		{
			if (BoxComponent::Intersect(*mBoxComponent, *star->GetBoxComponent()))
			{
				SDL_Log("Star touched! Game Over.");
				break;
			}
		}
	}


	if (onGround)
	{
		//mPhysicsComponent->SetUseGravity(false);
		Vector2 pos = GetPosition();
		pos.y = mBoxComponent->GetPosition().y;
		SetPosition(pos);
		mPhysicsComponent->SetVelocity(Vector2(mPhysicsComponent->GetVelocity().x, 0.0f));
		mPhysicsComponent->SetUseGravity(false);
	}

	if (!onGround)
	{
		mPhysicsComponent->SetUseGravity(true);
	}

	mPhysicsComponent->Update(deltaTime);
	mBoxComponent->Update(deltaTime);
}

void Player::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_D]) {
		mSprite->SetTexture(GetGame()->GetTexture("Assets/2DPlayerAiMake1.png"));
		bPlayerRight = true;
	}
	else if(bPlayerRight)
	{
		mSprite->SetTexture(GetGame()->GetTexture("Assets/2DPlayerAiMake.png"));
	}
	
	if (keyState[SDL_SCANCODE_A]) {
		bPlayerRight = false;
		mSprite->SetTexture(GetGame()->GetTexture("Assets/2DPlayerAiMake3.png"));
	}
	else if(!bPlayerRight) {
		mSprite->SetTexture(GetGame()->GetTexture("Assets/2DPlayerAiMake4.png"));
	}
}

// --- 안쓰는 코드
//

//BoxComponent* box = new BoxComponent(this);
	//box->SetPosition(Vector2(0.0f, 0.0f)); 
	//box->SetSize(Vector2(64.0f, 64.0f));  
	//SetBoxComponent(box);

	/*SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/2DPlayerAiMake.png"));*/

	/*PhysicsComponent* pc = new PhysicsComponent(this);
	pc->SetUseGravity(true);
	pc->SetMass(10.0f);*/