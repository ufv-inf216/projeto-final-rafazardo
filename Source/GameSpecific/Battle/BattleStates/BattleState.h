//
// Created by andre on 07/12/2023.
//

#pragma once
#include "../../../Components/AIComponents/FSMState.h"

class BattleState : public FSMState {
    public:
        BattleState(class FSMComponent *fsm, const std::string &name);

    protected:
        class Battle* mBattle;
};
