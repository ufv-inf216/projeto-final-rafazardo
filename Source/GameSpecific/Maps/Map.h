// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Map definition module for storing each map data, such as its
// sprite and collision matrix components.
// ----------------------------------------------------------------

#pragma once

#include "../../GameObjects/GameObject.h"
#include "../../Components/DrawComponents/SpriteComponent.h"
#include "../../Components/ColliderComponents/CollisionMatrixComponent.h"

class Map : public GameObject {
    protected:
        // Map dimensions: width, height and tile size.
        int mWidth,
            mHeight,
            mTileSize;

        // Map components.
        SpriteComponent *mSpriteComponent;
        CollisionMatrixComponent *mCollisionMatrixComponent;

    public:
        // Constructor
        // @param game The current game
        // @params texturePath and collisionPath The map texture and colision directories
        // @params width and height The map dimensions
        Map(class MyGame *game, const std::string &texturePath, const std::string &collisionPath, int width, int height);

        // Getter for Collision Matrix Component
        // @return A pointer for its collision matrix component
        CollisionMatrixComponent* GetCollisionMatrix() { return mCollisionMatrixComponent; }

        // Stops Genearting Outputs and Updating its GameObjects.
        void DisableMap() {
            SetState(GameObjectState::Paused);
            mSpriteComponent->SetIsVisible(false);
            mCollisionMatrixComponent->SetEnabled(false);
        }

        // Enable Outputs and GameObjects.
        void EnableMap() {
            SetState(GameObjectState::Active);
            mSpriteComponent->SetIsVisible(true);
            mCollisionMatrixComponent->SetEnabled(true);
        }
};
