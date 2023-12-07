

#pragma once
#include "BatState.h"

class BatMovingState : public BatState {
public:
    BatMovingState(class FSMComponent *fsm, float duration);
    void Start() override;
    void HandleStateTransition(float stateTime) override;

private:
    int mHorizontal;
    int mVertical;
    float mStateDuration;
};
