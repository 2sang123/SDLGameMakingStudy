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
    gravity.y = -98.f; // 9.8m/s^2 �� �ȼ� ������ ����

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
    // �߷��� �ۿ�ǵ��� �Ѵٸ� �Ź� �߷��� �����ش�.
    if (useGravity)
    {
        AddForce(gravity * mass);
    }
    // ���� �߰��Ǿ����� ���ӵ��� �ٽ� ����Ѵ�.
    acceleration.x = sumOfForce.x / mass;
    acceleration.y = sumOfForce.y / mass;

    // �ܺ� ���� �ʱ�ȭ�Ѵ�.
    sumOfForce = Vector2::Zero;

    // �ӵ��� ��ġ�� ������Ʈ�Ѵ�.
    velocity += acceleration * deltaTime;
    Vector2 pos = mOwner->GetPosition();
    pos += velocity * deltaTime;

    // ���� �عٴ� �浹 ó��
    if (pos.y < -410.0f)
    {
        pos.y = -410.0f;
        velocity.y = 0.0f; // �ٴڿ� ������ �ӵ��� 0���� ����
    }

    mOwner->SetPosition(pos);
}
