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

Door::Door(MyGame *game, const std::string &texturePath, Vector2 position):
    GameObject(game){

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
//        mGame->Pause(false);
//        SetState(GameObjectState::Active);
//        mFade->SetState(GameObjectState::Active);

        // Desenhar novo mapa.


        mIsProcessingInput = true;
        mFade->Out(false);

        mGame->GetCurrentMap()->DisableMap();
        mNextMap->EnableMap();
        mGame->GetPlayer()->SetState(GameObjectState::Active);
    }
}