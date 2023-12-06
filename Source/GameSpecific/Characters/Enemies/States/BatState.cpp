// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "BatState.h"
#include "../../../../Components/AIComponents/FSMComponent.h"
#include "../Bat.h"

BatState::BatState(class FSMComponent *fsm, const std::string &name) : FSMState(fsm, name) {
    mBat = dynamic_cast<Bat*>(mFSM->GetOwner());
}