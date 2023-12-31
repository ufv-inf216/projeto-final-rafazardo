// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Door methods implementation
// ----------------------------------------------------------------


#include "Door.h"
#define DOOR_WIDTH 24
#define DOOR_HEIGHT 48
#define TRIGGER_WIDTH 30
#define TRIGGER_HEIGHT 60


Door::Door(MyGame *game, const std::string &texturePath, Vector2 position, Vector2 player_pos):
    GameObject(game),
    mNextPosition(player_pos) {

    if(texturePath != "")
        mSpriteComponent = new SpriteComponent(this, texturePath, DOOR_WIDTH, DOOR_HEIGHT, 1);

    mFade = new Fade(mGame, 0.5f);
    mTrigger = new Trigger<std::function<void()>>(game, TRIGGER_WIDTH, TRIGGER_HEIGHT, ColliderLayer::Player);
    mTrigger->SetPosition(position - Vector2((TRIGGER_WIDTH-DOOR_WIDTH)/2, (TRIGGER_HEIGHT-DOOR_HEIGHT)/2));
    mIsProcessingInput = true;

    mHUD = new PressSpaceHUD(mGame);
    mHUD->Hide();

    this->SetPosition(position);
}

void Door::OnProcessInput(const uint8_t* state) {
    if(!mTrigger->IsPulled()) { mHUD->Hide(); return; }
    mHUD->MakeVisible();

    if(!mIsProcessingInput) return;
    if(state[SDL_SCANCODE_SPACE]) {
        std::vector<GameObject*> me{this};
        mFade->In(&me);
        mIsProcessingInput = false;
    }
}

void Door::OnUpdate(float deltaTime) {
    if(mIsProcessingInput) return;

    if(!mFade->IsFadding()) {
        mHUD->Hide();

        mGame->GetCurrentMap()->Disable();
        mNextMap->Enable();
        mGame->SetCurrentMap(mNextMap);
        
        mGame->GetPlayer()->SetState(GameObjectState::Active);
        mGame->GetPlayer()->SetPosition(mNextPosition);

        mGame->GetCamera()->SetState(GameObjectState::Active);
        mGame->GetCamera()->SetTarget(mGame->GetPlayer());

        mFade->Out(false);
        mIsProcessingInput = true;
    }
}