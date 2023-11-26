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

class Door : public GameObject{
private:
    SpriteComponent *mSpriteComponent;
    Trigger<std::function<void()>> *mTrigger;

public:
    Door(MyGame *game, const std::string &texturePath, Vector2 position);
};