//
// Created by andre on 14/12/2023.
//

#include "EnemySelectorBattleHUD.h"
#include "../../../GameSpecific/Battle/Battle.h"

void EnemySelectorBattleHUD::OnProcessInput(const Uint8 *state) {
    if(state[SDL_SCANCODE_0] && mTarget > 0) {
        mTarget--;

        mBattle->GetPlayer()->SetTarget(mTarget);
    }
    else if(state[SDL_SCANCODE_1] && mTarget < (mBattle->GetNumEnemies() - 1)) {
        mTarget++;

        mBattle->GetPlayer()->SetTarget(mTarget);
    }
}