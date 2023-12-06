//
// Created by pfb20 on 05/12/2023.
//

#include "BatIdleState.h"
#include "../../../../Components/AIComponents/FSMComponent.h"

BatIdleState::BatIdleState(FSMComponent *fsm) : BatState(fsm, "idle") { }

void BatIdleState::HandleStateTransition(float stateTime) {
    if(stateTime > 3.0f)
        mFSM->SetState("moving");
}
