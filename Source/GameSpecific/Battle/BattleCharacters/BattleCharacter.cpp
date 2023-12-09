// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// ----------------------------------------------------------------

#pragma once

#include "BattleCharacter.h"
#include "../../../Game/Random.h"

BattleCharacter::BattleCharacter(class MyGame *game, class Battle *battle):
    GameObject(game),
    mHasAttacked(false),
    mCurrentAction(nullptr),
    mBattle(battle) {

    mHP = 30;
    mMaxHP = 30;
}

int BattleCharacter::RollInitiative() {
    mInitiative = -(Random::GetIntRange(1, 20) + mSheet->dexMod);
    return mInitiative;
}
