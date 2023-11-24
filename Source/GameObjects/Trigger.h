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
        std::function<void()> mFunction = []() { std::cout << "trigger acionado" << std::endl; };

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
        Trigger(MyGame* game, int widht, int height, ColliderLayer layer);

        // Setter to the function which will be called on collision.
        // @param function The function that will be called on collision
        // @param ReturnType and Args The return type and arguments for the function
        template<typename ReturnType, typename Args>
        void SetFunction(std::function<ReturnType(Args)> &function) {
            mFunction = function;
        }
};