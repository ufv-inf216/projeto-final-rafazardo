// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Trigger module for implementing colliding areas in which a
// function is called every time a collision with the player happens
// ----------------------------------------------------------------

#pragma once

#include <iostream>
#include <functional>
#include "../GameSpecific/MyGame.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"
#include "../GameObjects/GameObject.h"
#include "../Components/ColliderComponents/BoxColliderComponent.h"

template<typename FunctionType>
class Trigger : public GameObject {
    private:
        // Trigger width and height.
        int mWidth,
            mHeight;


        ColliderLayer mTargetLayer; //pode virar um vector

        // Assistant private variable
        bool mIsPulled = false;

        DrawPolygonComponent *mDrawPolygonComponent; // temporário

        // Function to be called
        FunctionType mFunction = [](){};

        //std::function<void()> mFunction = []() { std::cout << "trigger acionado" << std::endl; };

        // Functions to detect the collision
        Vector2 GetMin() const;
        Vector2 GetMax() const;
        Vector2 GetCenter() const;
        bool Intersect(const BoxColliderComponent& b) const;
        void Update(float deltaTime) override;

    public:
        // Trigger constructor method
        // @param game
        // @param width
        // @param height
        // @param layer The target layer to pull the trigger
        Trigger(MyGame* game, int width, int height, ColliderLayer layer, bool draw=false);

        // Setter to the function which will be called on collision.
        // @param function The function that will be called on collision
        // @param ReturnType and Args The return type and arguments for the function
        void SetFunction(FunctionType &function) {
            mFunction = function;
        }

        bool IsPulled();
};

template<typename FunctionType>
Trigger<FunctionType>::Trigger(MyGame *game, int width, int height, ColliderLayer layer, bool draw):
        GameObject(game){
    mWidth = width;
    mHeight = height;
    mTargetLayer = layer;
    std::vector<Vector2> vertices;
    vertices.push_back(Vector2(0.0, 0.0));
    vertices.push_back(Vector2(width, 0.0));
    vertices.push_back(Vector2(width, height));
    vertices.push_back(Vector2(0.0, height));

    if(draw) mDrawPolygonComponent = new DrawPolygonComponent(this, vertices);
}

template<typename FunctionType>
Vector2 Trigger<FunctionType>::GetMin() const {
    return GetPosition();
}

template<typename FunctionType>
Vector2 Trigger<FunctionType>::GetMax() const {
    return this->GetMin() + Vector2(this->mWidth, this->mHeight);
}

template<typename FunctionType>
Vector2 Trigger<FunctionType>::GetCenter() const {
    return this->GetMin() + Vector2(this->mWidth/2, this->mHeight/2);
}

template<typename FunctionType>
bool Trigger<FunctionType>::Intersect(const BoxColliderComponent& b) const {
    Vector2 min_a = this->GetMin(), max_a = this->GetMax();
    Vector2 min_b = b.GetMin(), max_b = b.GetMax();

    return !(min_a.x > max_b.x || min_b.x > max_a.x
             || max_a.y < min_b.y || max_b.y < min_a.y);
}

template<typename FunctionType>
void Trigger<FunctionType>::Update(float deltaTime) {
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

template<typename FunctionType>
bool Trigger<FunctionType>::IsPulled() {
    return mIsPulled;
};