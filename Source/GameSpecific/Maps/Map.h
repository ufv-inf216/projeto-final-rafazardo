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

        // All game objects in the map.
        std::vector<GameObject *> mGameObjects;

    public:
        // Constructor
        // @param game The current game
        // @params texturePath and collisionPath The map texture and colision directories
        // @params width and height The map dimensions
        Map(class MyGame *game, const std::string &texturePath, const std::string &collisionPath, int width, int height);

        Map(class MyGame *game);

        // Getter for Collision Matrix Component
        // @return A pointer for its collision matrix component
        CollisionMatrixComponent* GetCollisionMatrix() { return mCollisionMatrixComponent; }

        // Add a new game object to the map.
        void AddGameObject(GameObject *obj) { mGameObjects.push_back(obj); }

        // Stops Genearting Outputs and Updating its GameObjects.
        void Disable() override {
            SetState(GameObjectState::Paused);
            mSpriteComponent->SetEnabled(false);
            mCollisionMatrixComponent->SetEnabled(false);
            for(auto obj : mGameObjects)
                if(obj) obj->Disable();
        }

        // Enable Outputs and GameObjects.
        void Enable(bool draw_only = false) override {
            if(!draw_only)
                SetState(GameObjectState::Active);

            mSpriteComponent->SetEnabled(true);
            mCollisionMatrixComponent->SetEnabled(true);
            for(auto obj : mGameObjects)
                if(obj) obj->Enable();
        }

        Vector2 GetDimension() { return Vector2(mWidth, mHeight); }

        virtual void Initialize(bool enable=false) { return; }

        void Remove(GameObject *game_obj) {
            game_obj->SetState(GameObjectState::Destroy);
            auto it = std::find(mGameObjects.begin(), mGameObjects.end(), game_obj);
            if(it != mGameObjects.end())
                mGameObjects.erase(it);
        }
};
