

#include "BatMovingState.h"
#include "../../../../Components/AIComponents/FSMComponent.h"
#include "../../../../Game/Random.h"
#include "../Bat.h"

BatMovingState::BatMovingState(FSMComponent *fsm) :
    BatState(fsm, "moving") { }

void BatMovingState::Start() {
    mVertical = mHorizontal = 0;

    if(Random::GetIntRange(0, 1))
        mHorizontal = 1 - (Random::GetIntRange(0, 1) * 2);
    else mVertical = 1 - (Random::GetIntRange(0, 1) * 2);

    mBat->SetRotation(Math::Pi * (mHorizontal == 1));
    mBat->GetComponent<RigidBodyComponent>()->SetVelocity(70.0f * Vector2(mHorizontal, mVertical));
}

void BatMovingState::HandleStateTransition(float stateTime) {
    if(stateTime > 2.0f)
        mFSM->SetState("idle");
}
