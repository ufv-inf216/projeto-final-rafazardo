

#pragma once
#include "BatState.h"

class BatMovingState : public BatState {
public:
    BatMovingState(class FSMComponent *fsm);
    void Start() override;
    void HandleStateTransition(float stateTime) override;

private:
    int mHorizontal;
    int mVertical;
};