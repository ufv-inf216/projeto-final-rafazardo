
#include "BatState.h"
#include "../../../../Components/AIComponents/FSMComponent.h"
#include "../Bat.h"

BatState::BatState(class FSMComponent *fsm, const std::string &name) : FSMState(fsm, name) {
    mBat = dynamic_cast<Bat*>(mFSM->GetOwner());
}