// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// ----------------------------------------------------------------

#include "Bat.h"
#include "States/BatIdleState.h"
#include "States/BatMovingState.h"

Bat::Bat(class MyGame *game, int atributes[]) : Enemy(game, "../Assets/Sprites/Enemies/Bat/bat_sprite.png", "../Assets/Sprites/Enemies/Bat/sprite_sheet_data.json", atributes) {

    mAnimatedSpriteComponent->AddAnimation("flying", { 0, 1 });
    mAnimatedSpriteComponent->SetAnimation("flying");
    mAnimatedSpriteComponent->SetAnimFPS(8.0f);

    mFSMComponent = new FSMComponent(this);
    new BatIdleState(mFSMComponent);
    new BatMovingState(mFSMComponent);
    mFSMComponent->Start("idle");
}