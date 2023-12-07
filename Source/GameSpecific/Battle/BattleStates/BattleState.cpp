//
// Created by andre on 07/12/2023.
//

#include "BattleState.h"
#include "../../../Components/AIComponents/FSMComponent.h"
#include "../Battle.h"

BattleState::BattleState(class FSMComponent *fsm, const std::string &name):
    FSMState(fsm, name) {
    mBattle = dynamic_cast<Battle*>(mFSM->GetOwner());
}