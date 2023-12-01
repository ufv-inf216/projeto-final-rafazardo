// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Door methods implementation
// ----------------------------------------------------------------


#include "Door.h"

void MinhaFuncao() {
    std::cout << "PORTA" << std::endl;
}

Door::Door(MyGame *game, const std::string &texturePath, Vector2 position, Vector2 player_pos):
    GameObject(game),
    mNextPosition(player_pos) {

    mFade = new Fade(mGame, 0.8f);
    mSpriteComponent = new SpriteComponent(this, texturePath, 32, 32);
    mTrigger = new Trigger<std::function<void()>>(game, 32, 32, ColliderLayer::Player);
    mIsProcessingInput = true;

    std::function<void()> function = []() { std::cout << "saulo te amo\n"; };

    this->SetPosition(position);
    mTrigger->SetPosition(position);
    mTrigger->SetFunction(function);
}

void Door::OnProcessInput(const uint8_t* state) {
    if(!mIsProcessingInput) return;
    if(state[SDL_SCANCODE_Q]) {
        std::vector<GameObject*> me{this};
        mFade->In(&me);
        mIsProcessingInput = false;
    }
}

void Door::OnUpdate(float deltaTime) {
    if(mIsProcessingInput) return;
    if(!mFade->IsFadding()) {
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