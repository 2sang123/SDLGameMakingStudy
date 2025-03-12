#pragma once
#include "Component.h"
#include "Math.h"
#include <algorithm>
class BoxComponent : public Component {

public:
    BoxComponent(class Actor* owner);

    void Update(float deltaTime);

    void SetPosition(const Vector2& position) { mPosition = position; }
    void SetSize(const Vector2& size) { mSize = size; }

    const Vector2& GetSize() const { return mSize; }
    const Vector2& GetPosition() const { return mPosition; }

    static bool Intersect(const BoxComponent& a, const BoxComponent& b);

private:
    Vector2 mPosition; 
    Vector2 mSize;     
};
