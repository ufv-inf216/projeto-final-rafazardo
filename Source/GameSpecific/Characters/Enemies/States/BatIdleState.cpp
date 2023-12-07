//
// Created by pfb20 on 05/12/2023.
//

#include "BatIdleState.h"
#include "../../../../Components/AIComponents/FSMComponent.h"
#include "../Bat.h"

BatIdleState::BatIdleState(FSMComponent *fsm, float duration) :
    BatState(fsm, "idle"),
    mStateDuration(duration) { }

void BatIdleState::Start() {
    mBat->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2::Zero);
}

void BatIdleState::HandleStateTransition(float stateTime) {
    if(stateTime > mStateDuration)
        mFSM->SetState("moving");
}
