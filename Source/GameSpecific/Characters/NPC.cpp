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
#include "../Quests/Quest.h"

NPC::NPC(class MyGame *game, const std::string &texturePath, const std::string &spriteSheetData, int *attrs):
    Character(game, texturePath, spriteSheetData, attrs, ColliderLayer::NPC) {

    mAnimatedSpriteComponent->AddAnimation("idle", {0});
    mAnimatedSpriteComponent->SetAnimation("idle");
    mAnimatedSpriteComponent->SetAnimFPS(6.f);
}

void NPC::Interact() {
    return;
}

void NPC::SetQuest(Quest *quest) {
    mQuest = quest;
    mQuest->SetNPC(this);
};