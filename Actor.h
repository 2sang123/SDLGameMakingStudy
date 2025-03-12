#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>
#include <string>

class Actor
{
public:
	//Actor의 상태 활성, 정지, 제거
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// 계속 실행되어야 하는 요소들
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);
	
	// Actor에 키입력
	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);

	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale;  mRecomputeWorldTransform = true; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation;  mRecomputeWorldTransform = true; }

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }


	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }
	
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	


private:
	State mState;

	Matrix4 mWorldTransform;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	bool mRecomputeWorldTransform;


	std::vector<class Component*> mComponents;
	class Game* mGame;

	
};

// --- 이제 안 쓰는 거 

// BoxComponent를 추가하고 가져오는 함수 추가
	// Actor에서 만들기 보다 필요한 애들한테 각각 제작
	/*void SetBoxComponent(class BoxComponent* box) { mBox = box; }
	BoxComponent* GetBoxComponent() const { return mBox; }*/
	//BoxComponent* mBox;
	//Vector2 GetJump() const { return Vector2(0.0f, 1.0f); }