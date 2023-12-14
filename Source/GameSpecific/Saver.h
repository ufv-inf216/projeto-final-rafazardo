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
#include "../GameSpecific/Characters/Player.h"
#include <functional>

class Saver : public GameObject{
    private:
        SpriteComponent *mSpriteComponent;
        BoxColliderComponent *mBoxColliderComponent;

        Trigger<std::function<void()>> *mTrigger;

    public:
        Saver(class MyGame *game, const std::string &texturePath, int tWidth, int tHeight, ColliderLayer layer);

        // Disale this game pbject.
        virtual void Disable() override {
            SetState(GameObjectState::Paused);
            for(auto c : mComponents)
                c->SetEnabled(false);
            mTrigger->SetState(GameObjectState::Paused);
        }

        // Enable this game object.
        virtual void Enable(bool draw_only=false) override {
            SetState(GameObjectState::Active);
            for(auto c : mComponents)
                c->SetEnabled(true);
            mTrigger->SetState(GameObjectState::Active);
        }
};