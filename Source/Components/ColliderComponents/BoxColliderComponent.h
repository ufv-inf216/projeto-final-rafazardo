// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Lucas N. Ferreira Pedro Fiorio and Rafael
// Crevelari.
//
// Created: October, 2023.
// Box Collider COmponent module defining a collision square for
// GameObjects.
// ----------------------------------------------------------------

#pragma once
#include "../Component.h"
#include "../../Game/Math.h"
#include "../PhysicsComponents/RigidBodyComponent.h"
#include <vector>
#include <set>
#include "CollisionUtils.h"
#include "CollisionMatrixComponent.h"

class BoxColliderComponent : public Component {
    public:
        struct Overlap {
            float amount;
            CollisionSide side;
            BoxColliderComponent *target;
        };

        BoxColliderComponent(class GameObject* owner, int dx, int dy, int w, int h,
                             ColliderLayer layer, int updateOrder = 10);
        ~BoxColliderComponent() override;

        bool Intersect(const BoxColliderComponent& b) const;
        void DetectCollision(RigidBodyComponent *rigidBody);

        Vector2 GetMin() const;
        Vector2 GetMax() const;
        Vector2 GetCenter() const;
        ColliderLayer GetLayer() const { return mLayer; }
        void SetLayer(ColliderLayer type) { mLayer = type; }

    private:
        Overlap GetMinOverlap(BoxColliderComponent* b) const;
        void ResolveCollisions(RigidBodyComponent *rigidBody, const Overlap& minOverlap);
        void ResolveMatrixCollision(CollisionMatrixComponent *collisionMatrix);

        Vector2 mOffset;
        int mWidth;
        int mHeight;

        ColliderLayer mLayer;
};