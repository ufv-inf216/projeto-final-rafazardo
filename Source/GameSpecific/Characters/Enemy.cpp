// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// ----------------------------------------------------------------

#include "Enemy.h"
#include "../../Game/Game.h"
#include "../MyGame.h"
#include "../Battle/Battle.h"

Enemy::Enemy(class MyGame *game, const std::string &texturePath, const std::string &spriteSheetData, int *attrs):
        Character(game, texturePath, spriteSheetData, attrs, ColliderLayer::Enemy) {

}

void Enemy::OnCollision(std::unordered_map<CollisionSide, BoxColliderComponent::Overlap>& responses) {
    for(auto resp : responses)
        if(resp.second.target->GetLayer() == ColliderLayer::Player) {
            SDL_Log("bora pro fight");
            auto battle = new Battle(mGame, mGame->GetPlayer(), this,
                                     "../Assets/Sprites/Test/test_battle.png");;
            battle->Start();
        }
}