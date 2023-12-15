// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// ----------------------------------------------------------------

#include "BattleEnemy.h"
#include "../Battle.h"
#include "../../../Game/Random.h"

BattleEnemy::BattleEnemy(class MyGame *game, Battle *battle, Enemy *enemy):
    BattleCharacter(game, battle),
    mEnemy(enemy) {

    mSheet = enemy->GetCharacterSheet();
    mImgDims = enemy->GetImgDims();
    mSpriteComponent = new SpriteComponent(this, enemy->GetImg(),
                                           mImgDims.x, mImgDims.y, 200);

    mMaxHP = 20;
    mHP    = 20;
}

Action* BattleEnemy::GetAction() {
    if(mRemoveHeal != -1) {
        for(int i = 0; i < mHeals.size(); i++) {
            if(mHeals[i]->GetPotionId() == mRemoveHeal) {
                delete mHeals[i]; mHeals[i] = nullptr;
                mHeals.erase(mHeals.begin() + i);
                mRemoveHeal = -1;
                break;
            }
        }
    }

    auto aux = EnemyAttacks[EnemyAttackOptions[mEnemy->GetId()][Random::GetIntRange(0,
                                                                EnemyAttackOptions[mEnemy->GetId()].size()-1)]];
    auto attack = new Attack();
    *attack = *aux;
    attack->SetTarget(mBattle->GetPlayer());

    return attack;
}