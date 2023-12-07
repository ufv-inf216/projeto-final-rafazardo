#pragma once

#pragma once
#include "BattleState.h"

class BattleMessageState : public BattleState {
    public:
        BattleMessageState(class FSMComponent *fsm, float duration);
        void Start() override;
        void HandleStateTransition(float stateTime) override;

    private:
        float mStateDuration;
};