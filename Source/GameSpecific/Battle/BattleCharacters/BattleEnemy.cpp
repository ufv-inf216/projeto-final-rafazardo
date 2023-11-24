// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// ----------------------------------------------------------------

#include "BattleEnemy.h"
#include "../Battle.h"

BattleEnemy::BattleEnemy(class MyGame *game, Battle *battle, Enemy *enemy, const std::string &texturePath):
    BattleCharacter(game, battle),
    mEnemy(enemy) {

    mSheet = enemy->GetCharacterSheet();
    mSpriteComponent = new SpriteComponent(this, texturePath, 32, 32, 200);
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
    return new Attack("ataque", mBattle->GetPlayer(), -1);
}