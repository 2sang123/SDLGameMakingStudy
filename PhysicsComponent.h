# include "Component.h"
# include "Math.h"

class PhysicsComponent : Component
{
public:
	PhysicsComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;
	void AddForce(Vector2 force);

	void SetUseGravity(bool use) { useGravity = use; }
	void SetMass(float mass);

	void SetVelocity(const Vector2& vel);
	const Vector2& GetVelocity() const;
	

private:
	float mass;
	Vector2 sumOfForce;
	Vector2 acceleration;
	Vector2 velocity;
	Vector2 gravity; // 중력, 매프레임마다 작용히도록
	bool useGravity;

};
