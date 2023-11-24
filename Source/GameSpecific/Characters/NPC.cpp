// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Sheet module for storing each character data, such as attributes,
// health points etc.
// ----------------------------------------------------------------

#include "NPC.h"
#include "../../Game/Game.h"

NPC::NPC(class MyGame *game, const std::string &texturePath, int *attrs):
    Character(game, texturePath, attrs, ColliderLayer::NPC) { }

void NPC::Interact() {
    return;
}