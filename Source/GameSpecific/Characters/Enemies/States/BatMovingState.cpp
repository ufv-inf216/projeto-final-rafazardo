

#include "BatMovingState.h"
#include "../../../../Components/AIComponents/FSMComponent.h"
#include "../../../../Game/Random.h"
#include "../Bat.h"

BatMovingState::BatMovingState(FSMComponent *fsm) : BatState(fsm, "moving") { }

void BatMovingState::Start() {

    mVertical = 0;

    mHorizontal = Random::GetIntRange(-1, 1);
    if(!mHorizontal)
        mVertical = 1 - (Random::GetIntRange(0, 1) * 2);

    SDL_Log("Entrei no luger certin %d %d", mHorizontal, mVertical);
}

void BatMovingState::Update(float deltaTime) {
    SDL_Log("Entrei no update");
    mBat->GetComponent<RigidBodyComponent>()->SetVelocity(96.0f * Vector2(mHorizontal, mVertical));
}

void BatMovingState::HandleStateTransition(float stateTime) {
    if(stateTime > 3.0f)
        mFSM->SetState("idle");
}
