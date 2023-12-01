// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Door module for implementing the map switching
// ----------------------------------------------------------------

#pragma once

#include "../GameSpecific/MyGame.h"
#include "../GameObjects/GameObject.h"
#include "../Components/DrawComponents/SpriteComponent.h"
#include "Trigger.h"
#include <string>
#include <functional>
#include "../Interfaces/Fade.h"

class Door : public GameObject{
    private:
        bool mIsProcessingInput = false;
        Fade *mFade;

        class Map *mNextMap;
        Vector2 mNextPosition;

        SpriteComponent *mSpriteComponent;
        Trigger<std::function<void()>> *mTrigger;

    public:
        Door(MyGame *game, const std::string &texturePath, Vector2 position, Vector2 player_pos);

        void OnProcessInput(const uint8_t* state) override;
        void OnUpdate(float deltaTime) override;

        void SetNextMap(class Map *next) { mNextMap = next; }
        Vector2 GetNextPosition() { return mNextPosition; }

        // Disale this game pbject.
        virtual void Disable() override {
            SetState(GameObjectState::Paused);
            for(auto c : mComponents)
                c->SetEnabled(false);
            mTrigger->Disable();
        }

        // Enable this game object.
        virtual void Enable() override {
            SetState(GameObjectState::Active);
            for(auto c : mComponents)
                c->SetEnabled(true);
            mTrigger->Enable();
        }
};