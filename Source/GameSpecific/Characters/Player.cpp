// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "Player.h"
#include "../../Game/Game.h"

Player::Player(class MyGame *game, const std::string &texturePath, int *attrs, Inventory *inventory):
    Character(game, texturePath, attrs, ColliderLayer::Player) {
    mInventory = inventory;
}

void Player::OnProcessInput(const uint8_t* state) {
    // === PLAYER MOVEMENT ===
    int horizontal = state[SDL_SCANCODE_D]-state[SDL_SCANCODE_A],
        vertical = state[SDL_SCANCODE_S]-state[SDL_SCANCODE_W];
    if(horizontal) vertical = false;

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
    mRotation = Math::Pi*(state[SDL_SCANCODE_A]);
}