// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Lucas N. Ferreira, Pedro Fiorio and Rafael
// Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "BoxColliderComponent.h"
#include "../../GameObjects/GameObject.h"
#include "../../GameSpecific/MyGame.h"
#include <cmath>
#include <algorithm>
#include "CollisionMatrixComponent.h"

BoxColliderComponent::BoxColliderComponent(class GameObject* owner, int dx, int dy, int w, int h, ColliderLayer layer, int updateOrder)
        :Component(owner, updateOrder)
        ,mOffset(Vector2((float)dx, (float)dy))
        ,mWidth(w)
        ,mHeight(h)
        ,mLayer(layer) {

    this->mOwner->GetGame()->AddCollider(this);
}

BoxColliderComponent::~BoxColliderComponent() {
    this->mOwner->GetGame()->RemoveCollider(this);
}

Vector2 BoxColliderComponent::GetMin() const {
    return this->mOwner->GetPosition() + this->mOffset;
}

Vector2 BoxColliderComponent::GetMax() const {
    return this->GetMin() + Vector2(this->mWidth, this->mHeight);
}

Vector2 BoxColliderComponent::GetCenter() const {
    return this->GetMin() + Vector2(this->mWidth/2, this->mHeight/2);
}

bool BoxColliderComponent::Intersect(const BoxColliderComponent& b) const {
    Vector2 min_a = this->GetMin(), max_a = this->GetMax();
    Vector2 min_b = b.GetMin(), max_b = b.GetMax();

    return !(min_a.x > max_b.x || min_b.x > max_a.x
            || max_a.y < min_b.y || max_b.y < min_a.y);
}

BoxColliderComponent::Overlap BoxColliderComponent::GetMinOverlap(BoxColliderComponent* b) const {
    Vector2 min_a = this->GetMin(), max_a = this->GetMax();
    Vector2 min_b = b->GetMin(), max_b = b->GetMax();
    std::unordered_map<int, Overlap> overlaps;
    int min_overlap, min;

    overlaps[1] = {max_b.y-min_a.y, CollisionSide::Top, b};
    min = abs(overlaps[1].amount); min_overlap = 1;

    overlaps[2] = {min_b.y-max_a.y, CollisionSide::Down, b};
    if(min > abs(overlaps[2].amount)) { min = abs(overlaps[2].amount); min_overlap = 2; }

    overlaps[3] = {min_b.x-max_a.x, CollisionSide::Right, b};
    if(min > abs(overlaps[3].amount)) { min = abs(overlaps[3].amount); min_overlap = 3; }

    overlaps[4] = {max_b.x-min_a.x, CollisionSide::Left, b};
    if(min > abs(overlaps[4].amount)) { min_overlap = 4; }

    return overlaps[min_overlap];
}

void BoxColliderComponent::ResolveCollisions(RigidBodyComponent *rigidBody, const Overlap& minOverlap) {
    // Resolves vertical collisions.
    if(minOverlap.side == CollisionSide::Top && rigidBody->GetVelocity().y < 0 ||
            minOverlap.side == CollisionSide::Down && rigidBody->GetVelocity().y > 0) {
        this->mOwner->SetPosition(this->mOwner->GetPosition() + Vector2(0, minOverlap.amount));
        rigidBody->SetVelocity(Vector2(rigidBody->GetVelocity().x, 0));
    }

    // Resolve horizontal collisions.
    if(minOverlap.side == CollisionSide::Right && rigidBody->GetVelocity().x > 0 ||
       minOverlap.side == CollisionSide::Left && rigidBody->GetVelocity().x < 0) {
        this->mOwner->SetPosition(this->mOwner->GetPosition() + Vector2(minOverlap.amount, 0));
        rigidBody->SetVelocity(Vector2(0, rigidBody->GetVelocity().y));
    }
}

void BoxColliderComponent::DetectCollision(RigidBodyComponent *rigidBody) {
    auto colliders = mOwner->GetGame()->GetColliders();

    // Sorts all BoxColliderComponents by distance from this one.
    std::sort(colliders.begin(), colliders.end(),
              [this](const BoxColliderComponent *col1, const BoxColliderComponent *col2) -> bool {
                  return (col1->GetCenter() - this->GetCenter()).LengthSq() < (col2->GetCenter() - this->GetCenter()).LengthSq();
              });

    std::unordered_map<CollisionSide, Overlap> responses;
    bool hovrlp = false, vovrlp = false;

    // Detects and resolves each collision.
    for (auto coll: colliders) {
        if(coll == this) continue;
        if(!coll->IsEnabled()) continue;

        // If the collider is colliding with this component, then resolve it.
        if(this->Intersect(*coll) && coll->GetLayer() != this->mLayer) {
            auto min_ovrlp = this->GetMinOverlap(coll);
            responses[min_ovrlp.side] = min_ovrlp;

            this->ResolveCollisions(rigidBody, min_ovrlp);
            if (min_ovrlp.side == CollisionSide::Down || min_ovrlp.side == CollisionSide::Top) vovrlp = true;
            if (min_ovrlp.side == CollisionSide::Right || min_ovrlp.side == CollisionSide::Left) hovrlp = true;
        }

        // If were detected a vertical and horizontal collisions, then we can stop.
        if(vovrlp && hovrlp) break;
    }

    // Callback only for closest (first) collision
    mOwner->OnCollision(responses);

    auto collisionMatrix = mOwner->GetGame()->GetCurrentMap()->GetCollisionMatrix();
    if(collisionMatrix != nullptr)
        ResolveMatrixCollision(collisionMatrix);
}

void BoxColliderComponent::ResolveMatrixCollision(CollisionMatrixComponent *collisionMatrix) {
    Vector2 min = GetMin(), max = GetMax();
    std::vector<Vector2> vertices {min, Vector2(max.x, min.y), Vector2(min.x, max.y), max};

    Vector2 moves = collisionMatrix->ResolveCollision(vertices);
    if(moves.x || moves.y) {
        Vector2 vel = mOwner->GetComponent<RigidBodyComponent>()->GetVelocity();
        Vector2 pos = mOwner->GetPosition();
        bool x = vel.x != 0, y = vel.y != 0;
        mOwner->SetPosition(Vector2(pos.x - moves.x*x, pos.y - moves.y*y));
    }
}