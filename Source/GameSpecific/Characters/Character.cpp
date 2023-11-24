// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "Character.h"

Character::Character(class MyGame *game, const std::string &texturePath, int *attrs, ColliderLayer coll_layer):
        GameObject(game),
        mIsWalkingDown(0), mIsWalkingUp(0), mIsWalkingHorizontal(0),
        mSpeed(96.0f) {

    mRigidBodyComponent = new RigidBodyComponent(this, 1.0f, .0f);
    mSpriteComponent = new SpriteComponent(this, texturePath, 32, 32);
    mBoxColliderComponent = new BoxColliderComponent(this, 0, 0, 32, 32, coll_layer);

    mSheet = new CharacterSheet(attrs);
}