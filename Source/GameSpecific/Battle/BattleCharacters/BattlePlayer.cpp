// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// ----------------------------------------------------------------

#include "BattlePlayer.h"
#include "../Battle.h"

BattlePlayer::BattlePlayer(class MyGame *game, Battle *battle, Player *player):
    BattleCharacter(game, battle),
    mPlayer(player) {
    mSheet = player->GetCharacterSheet();

    int aux[] = {0,0,0};

    for(int i = 0; i < WEAPONS.size(); i++)
        if(player->GetInventory()->GetItemAmount("weapon", i) > 0)
//            mAttacks.push_back(new Attack(WEAPONS[i].name, nullptr, -WEAPONS[i].dam));
            mAttacks.push_back(new Attack(WEAPONS[i].name, nullptr, aux));

    for(int i = 0; i < POTIONS.size(); i++)
        if(player->GetInventory()->GetItemAmount("potion", i) > 0)
            // mHeals.push_back(new Heal(POTIONS[i].name, this, POTIONS[i].heal, i));
            mHeals.push_back(new Heal(POTIONS[i].name, this, aux, i));

    mMaxHP = player->GetMaxHP();
    mHP = player->GetCurrentHP();
}

void BattlePlayer::OnProcessInput(const uint8_t* state) {
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
}

Action* BattlePlayer::GetAction() {
    Action *action = mCurrentAction;
    mCurrentAction = nullptr;
    return action;
}

void BattlePlayer::SetTarget(int enemy_idx) {
    mTarget = mBattle->GetEnemy(enemy_idx);
}