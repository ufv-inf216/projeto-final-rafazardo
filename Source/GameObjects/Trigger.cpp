// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Trigger methods implementation
// ----------------------------------------------------------------

#include "Trigger.h"
#include <vector>

Trigger::Trigger(MyGame *game, int width, int height, ColliderLayer layer):
        GameObject(game){
    mWidth = width;
    mHeight = height;
    mTargetLayer = layer;
    std::vector<Vector2> vertices;
    vertices.push_back(Vector2(0.0, 0.0));
    vertices.push_back(Vector2(width, 0.0));
    vertices.push_back(Vector2(width, height));
    vertices.push_back(Vector2(0.0, height));
    mDrawPolygonComponent = new DrawPolygonComponent(this, vertices);
}

Vector2 Trigger::GetMin() const {
    return GetPosition();
}

Vector2 Trigger::GetMax() const {
    return this->GetMin() + Vector2(this->mWidth, this->mHeight);
}

Vector2 Trigger::GetCenter() const {
    return this->GetMin() + Vector2(this->mWidth/2, this->mHeight/2);
}

bool Trigger::Intersect(const BoxColliderComponent& b) const {
    Vector2 min_a = this->GetMin(), max_a = this->GetMax();
    Vector2 min_b = b.GetMin(), max_b = b.GetMax();

    return !(min_a.x > max_b.x || min_b.x > max_a.x
             || max_a.y < min_b.y || max_b.y < min_a.y);
}

void Trigger::Update(float deltaTime) {
    auto colliders = GetGame()->GetColliders();

    // Sorts all BoxColliderComponents by distance from this one.
    std::sort(colliders.begin(), colliders.end(),
              [this](const BoxColliderComponent *col1, const BoxColliderComponent *col2) -> bool {
                  return (col1->GetCenter() - this->GetCenter()).LengthSq() < (col2->GetCenter() - this->GetCenter()).LengthSq();
              });

    bool isEmpty = true;

    // Detects a collision.
    for (auto coll: colliders) {
        if(!coll->IsEnabled()) continue;

        if(this->Intersect(*coll) && coll->GetLayer() == mTargetLayer) {
            isEmpty = false;
            // Only will call mFunction once when a target layer gets into the trigger zone
            if(!mIsPulled) {
                mIsPulled = true;
                mFunction();
            }
        }
    }
    // If no collision was detected, it means that the trigger can be pulled again next time
    if(isEmpty) mIsPulled = false;
}