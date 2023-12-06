

#pragma once
#include "../../../../Components/AIComponents/FSMState.h"

class BatState : public FSMState {
    public:
        BatState(class FSMComponent *fsm, const std::string &name);

    protected:
        class Bat* mBat;
};