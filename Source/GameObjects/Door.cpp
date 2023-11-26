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
    mSpriteComponent = new SpriteComponent(this, texturePath, 32, 32);
    mTrigger = new Trigger<std::function<void()>>(game, 32, 32, ColliderLayer::Player);

    this->SetPosition(position);
    mTrigger->SetPosition(position);

    std::function<void()> teste = []() { std::cout << "Saulo te amo" << std::endl; };

    mTrigger->SetFunction(teste);
}
