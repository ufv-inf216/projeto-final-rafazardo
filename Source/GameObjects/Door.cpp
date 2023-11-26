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

    mFade = new Fade(mGame, .8f);
    mSpriteComponent = new SpriteComponent(this, texturePath, 32, 32);
    mTrigger = new Trigger<std::function<void()>>(game, 32, 32, ColliderLayer::Player);

    this->SetPosition(position);
    mTrigger->SetPosition(position);
}

void Door::OnProcessInput(const uint8_t* state) {
    if(!mColliding) return;
    if(state[SDL_SCANCODE_Q]) {
        mFade->In();
        mFade->SetState(GameObjectState::Active);
    }
}