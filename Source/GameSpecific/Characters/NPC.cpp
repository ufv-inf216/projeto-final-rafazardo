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

void NPC::OnProcessInput(const Uint8 *state)  {
    if((mGame->GetPlayer()->GetPosition() - mPosition).Length() > 48) return;


    if(!mQuest->IsDone())
        if(state[SDL_SCANCODE_X] && mPressCounter > .5f) {
            if(!mIsHUDOpen) { mQuest->Open(); mIsHUDOpen = true; }
            else mQuest->Close();
            mPressCounter = .0f;
        }
    else
        if(state[SDL_SCANCODE_X] && mPressCounter > .5f) {
            mPressCounter = .0f;
            mGame->Quit();
        }
}