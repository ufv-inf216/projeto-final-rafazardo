// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Saver module designed to determine a place to save the game
// ----------------------------------------------------------------

#pragma once
#include "../GameObjects/GameObject.h"
#include "../Components/DrawComponents/SpriteComponent.h"
#include "../Components/ColliderComponents/BoxColliderComponent.h"
#include "../GameObjects/Trigger.h"

class Saver : public GameObject{
    private:
        SpriteComponent *mSpriteComponent;
        BoxColliderComponent *mBoxColliderComponent;

        Trigger *mTrigger;

    public:
        Saver(class MyGame *game, const std::string &texturePath, int tWidth, int tHeight, ColliderLayer layer);
};