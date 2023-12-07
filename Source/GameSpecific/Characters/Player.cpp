// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "Player.h"
#include "../../Game/Game.h"

Player::Player(class MyGame *game, const std::string &texturePath, const std::string &spriteSheetData, int *attrs, Inventory *inventory):
    Character(game, texturePath, spriteSheetData, attrs, ColliderLayer::Player) {
    mInventory = inventory;

    mAnimatedSpriteComponent->AddAnimation("idle", {1});
    mAnimatedSpriteComponent->AddAnimation("walkr", {7, 6, 7, 8});
    mAnimatedSpriteComponent->AddAnimation("walkb", {0, 1, 2, 1});
    mAnimatedSpriteComponent->AddAnimation("walku", {10, 9, 10, 11});
    mAnimatedSpriteComponent->SetAnimation("idle");
    mAnimatedSpriteComponent->SetAnimFPS(6.f);
}

void Player::OnProcessInput(const uint8_t* state) {
    // === PLAYER MOVEMENT ===

    int horizontal;
    int vertical;

    if(state[SDL_SCANCODE_S]) {
        mAnimatedSpriteComponent->SetAnimFPS(5.f);
        horizontal = 0;
        vertical = 1;
        mAnimatedSpriteComponent->SetAnimation("walkb");
    }
    else if(state[SDL_SCANCODE_D]) {
        mAnimatedSpriteComponent->SetAnimFPS(6.f);
        horizontal = 1;
        vertical = 0;
        mAnimatedSpriteComponent->SetAnimation("walkr");
    }
    else if(state[SDL_SCANCODE_W]) {
        mAnimatedSpriteComponent->SetAnimFPS(5.f);
        horizontal = 0;
        vertical = -1;
        mAnimatedSpriteComponent->SetAnimation("walku");
    }
    else if(state[SDL_SCANCODE_A]) {
        mAnimatedSpriteComponent->SetAnimFPS(6.f);
        horizontal = -1;
        vertical = 0;
        mAnimatedSpriteComponent->SetAnimation("walkr");
    }
    else {
        horizontal = 0;
        vertical = 0;
        mAnimatedSpriteComponent->SetAnimation("idle");
    }

    mRigidBodyComponent->SetVelocity(mSpeed*Vector2(horizontal, vertical));

    // === END OF PLAYER MOVEMENT ===

    // === CRAFTER INTERACTION ===
    if(state[SDL_SCANCODE_C]) {
        std::cout << "==> Before crafting\n";
        mInventory->PrintInventory();
        GetGame()->GetCrafter()->Craft("weapon", 0, mInventory);
        std::cout << "==> After crafting\n";
        mInventory->PrintInventory();
    }
    // === END OF CRAFTER INTERACTION ===

    // === CHEST INTERACTION ===
//    if(state[SDL_SCANCODE_B]) {
//        std::cout << "==> Before opening chest\n";
//        mInventory->PrintInventory();
//        GetGame()->GetChest()->Interact(mInventory);
//        std::cout << "==> After opening chest\n";
//        mInventory->PrintInventory();
//    }
    // === END OF CHEST INTERACTION ===

    // Sets some variables for further animations proposes.
    mIsWalkingHorizontal = horizontal;
    mIsWalkingUp = vertical > 0;
    mIsWalkingDown = vertical < 0;
    mRotation = Math::Pi*(state[SDL_SCANCODE_A] & !state[SDL_SCANCODE_D]);
}