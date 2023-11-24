// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Saver methods implementation
// ----------------------------------------------------------------

#include "Saver.h"
Saver::Saver(class MyGame *game, const std::string &texturePath, int tWidth, int tHeight, ColliderLayer layer):
        GameObject(game) {
    mSpriteComponent = new SpriteComponent(this, texturePath, 32, 32);
    mBoxColliderComponent = new BoxColliderComponent(this, 0, 0, 32, 32, ColliderLayer::Saver);

    mTrigger = new Trigger(game, tWidth, tHeight, layer);
    mTrigger->SetPosition(mPosition + Vector2(32, 32));
}