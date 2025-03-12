#include "PhysicsComponent.h"
#include "Actor.h"
#include "SDL.h"

PhysicsComponent::PhysicsComponent(class Actor* owner, int updateOrder)
    :Component(owner, updateOrder)
    , sumOfForce(0.0f, 0.0f)
    , velocity(0.0f, 0.0f)
    , acceleration(0.0f, 0.0f)
{
    mass = 1.0f;
    gravity.x = 0.0f;
    gravity.y = -98.f; // 9.8m/s^2 을 픽셀 단위로 조정

    useGravity = true;
}

void PhysicsComponent::SetMass(float mass)
{
    this->mass = mass;
}

void PhysicsComponent::AddForce(Vector2 force)
{
    sumOfForce += force;
}

void PhysicsComponent::SetVelocity(const Vector2& vel)
{
    velocity = vel;
}

const Vector2& PhysicsComponent::GetVelocity() const
{
    return velocity;
}



void PhysicsComponent::Update(float deltaTime)
{
    // 중력이 작용되도록 한다면 매번 중력을 더해준다.
    if (useGravity)
    {
        AddForce(gravity * mass);
    }
    // 힘이 추가되었으면 가속도를 다시 계산한다.
    acceleration.x = sumOfForce.x / mass;
    acceleration.y = sumOfForce.y / mass;

    // 외부 힘을 초기화한다.
    sumOfForce = Vector2::Zero;

    // 속도와 위치를 업데이트한다.
    velocity += acceleration * deltaTime;
    Vector2 pos = mOwner->GetPosition();
    pos += velocity * deltaTime;

    // 가장 밑바닥 충돌 처리
    if (pos.y < -410.0f)
    {
        pos.y = -410.0f;
        velocity.y = 0.0f; // 바닥에 닿으면 속도를 0으로 설정
    }

    mOwner->SetPosition(pos);
}
