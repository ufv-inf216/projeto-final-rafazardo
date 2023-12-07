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
#include "../../../Game/Random.h"

Bat::Bat(class MyGame *game, const std::string &img_path, Vector2 img_dims, int atributes[]):
    Enemy(game, "../Assets/Sprites/Enemies/Bat/bat_sprite.png",
          "../Assets/Sprites/Enemies/Bat/sprite_sheet_data.json", img_path, img_dims, atributes, 1) {

    mAnimatedSpriteComponent->AddAnimation("flying", { 0, 1 });
    mAnimatedSpriteComponent->SetAnimation("flying");
    mAnimatedSpriteComponent->SetAnimFPS(8.0f);

    mFSMComponent = new FSMComponent(this);
    new BatIdleState(mFSMComponent, Random::GetFloatRange(2.0, 4.5));
    new BatMovingState(mFSMComponent, Random::GetFloatRange(2.0, 4.5));
    mFSMComponent->Start("idle");
}