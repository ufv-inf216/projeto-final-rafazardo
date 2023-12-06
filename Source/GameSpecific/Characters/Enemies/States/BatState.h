// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#pragma once
#include "../../../../Components/AIComponents/FSMState.h"

class BatState : public FSMState {
    public:
        BatState(class FSMComponent *fsm, const std::string &name);

    protected:
        class Bat* mBat;
};