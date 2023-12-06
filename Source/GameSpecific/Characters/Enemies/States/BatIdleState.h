// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#pragma once
#include "BatState.h"

class BatIdleState : public BatState {
    public:
        BatIdleState(class FSMComponent *fsm);
        void Start() override;
        void HandleStateTransition(float stateTime) override;
    private:
};
