

#pragma once
#include "BatState.h"

class BatIdleState : public BatState {
    public:
        BatIdleState(class FSMComponent *fsm);
        void Start() override;
        void HandleStateTransition(float stateTime) override;
    private:
};
